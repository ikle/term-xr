/*
 * Terminal Emulator X11 Render View
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-view.h"

int tty_view_init (struct tty_view *o, struct tty_proto *proto,
		   struct tty_state *state)
{
	XSizeHints sh;

	o->proto = proto;
	o->state = state;

	if (!x11_display_init (&o->d))
		return 0;

	if (!x11_gc_init (&o->gc, &o->d))
		goto no_gc;

	if (!x11_gc_set_font (&o->gc, "monospace"))
		goto no_font;

	o->width  = o->gc.font->max_advance_width;
	o->height = o->gc.font->ascent + o->gc.font->descent;

	sh.flags = PSize | PResizeInc;

	sh.width	= state->width  * o->width;
	sh.height	= state->height * o->height;
	sh.width_inc	= o->width;
	sh.height_inc	= o->height;

	if (!x11_window_init (&o->w, &o->d, "Terminal", &sh))
		goto no_window;

	return 1;
no_window:
no_font:
	x11_gc_fini (&o->gc);
no_gc:
	x11_display_fini (&o->d);
	return 0;
}

void tty_view_fini (struct tty_view *o)
{
	x11_window_fini (&o->w);
	x11_gc_fini (&o->gc);
	x11_display_fini (&o->d);
}

static unsigned bound_down (int x, unsigned factor)
{
	return x < 0 ? 0 : x / factor;
}

static unsigned bound_up (int x, unsigned factor)
{
	return x < 0 ? 0 : (x + factor - 1) / factor;
}

static void tty_view_mark_dirty (struct tty_view *o)
{
	XExposeEvent *e = &o->e.xexpose;
	unsigned sx, sy;
	unsigned ex, ey;

	sx = bound_down (e->x, o->width);
	sy = bound_down (e->y, o->height);

	ex = bound_up (e->x + e->width,  o->width);
	ey = bound_up (e->y + e->height, o->height);

	tty_state_mark_dirty (o->state, sx, sy, ex, ey);
}

int tty_view_process (struct tty_view *o)
{
	do {
		while (x11_next_event (&o->d, &o->e, 0)) {
			if (o->e.xany.window != o->w.w)
				continue;

			switch (o->e.type) {
			case Expose:
				tty_view_mark_dirty (o);
				break;

			case KeyPress:
				tty_view_input (o);
				break;
			}
		}

		tty_view_render (o);
	}
	while (x11_pending (&o->d));

	return 1;
}
