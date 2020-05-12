/*
 * Terminal Emulator X11 Render View Output
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-view.h"

static
int tty_view_render_cb (const struct tty_slot *slot, unsigned x, unsigned y,
			void *cookie)
{
	struct tty_view *o = cookie;

	x11_gc_set_color_index (&o->gc, slot->bg);

	x *= o->width;
	y *= o->height;

	x11_fill_rect (&o->w, &o->gc, x, y, o->width, o->height);

	if (slot->symbol == 0)
		return 1;

	x11_gc_set_color_index (&o->gc, slot->fg);

	x11_draw_char (&o->w, &o->gc, x, y + o->gc.font->ascent, slot->symbol);
	return 1;
}

int tty_view_render (struct tty_view *o)
{
	tty_state_flush (o->state, tty_view_render_cb, o);
	return 1;
}
