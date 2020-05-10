/*
 * Terminal Emulator State
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "tty-state.h"

static struct tty_slot *
tty_state_get_slot (struct tty_state *o, unsigned x, unsigned y)
{
	size_t lineno = (o->origin + y) % o->total;

	return o->slot + o->width * lineno + x;
}

static void tty_state_clear (struct tty_state *o, unsigned x, unsigned y);

static void tty_state_copy (struct tty_state *from, struct tty_state *to)
{
	unsigned w, h, i, j;

	w = from->width  < to->width  ? from->width  : to->width;
	h = from->height < to->height ? from->height : to->height;

	for (j = 0; j < h; ++j) {
		for (i = 0; i < w; ++i)
			tty_slot_copy (tty_state_get_slot (from, i, j),
				       tty_state_get_slot (to,   i, j));

		tty_state_clear_right (to, i, j);
	}

	tty_state_clear_down (to, j);
}

static
int tty_state_resize (struct tty_state *o, unsigned width, unsigned height)
{
	struct tty_state s = *o;

	s.width   = width;
	s.height  = height;
	s.total   = o->total > height ? o->total : height;
	s.origin  = 0;

	if ((s.slot = malloc (width * s.total * sizeof (s.slot[0]))) == NULL)
		return 0;

	tty_state_copy (o, &s);
	free (o->slot);

	if (s.x >= width)
		s.x = width - 1;

	if (s.y >= height)
		s.y = height - 1;

	*o = s;
	return 1;
}

int tty_state_init (struct tty_state *o,
		    unsigned width, unsigned height, unsigned total)
{
	o->width  = 0;
	o->height = 0;
	o->total  = total;
	o->slot   = NULL;

	tty_state_reset (o);

	return tty_state_resize (o, width, height);
}

void tty_state_fini (struct tty_state *o)
{
	free (o->slot);
}

static void tty_state_clear (struct tty_state *o, unsigned x, unsigned y)
{
	struct tty_slot *s = tty_state_get_slot (o, x, y);

	tty_slot_set (s, 0, o->flags, o->fg, o->bg);
}

int tty_state_clear_left (struct tty_state *o, unsigned x, unsigned y)
{
	unsigned i;

	for (i = 0; i < x; ++i)
		tty_state_clear (o, i, y);

	return 1;
}

int tty_state_clear_right (struct tty_state *o, unsigned x, unsigned y)
{
	unsigned i;

	for (i = x; i < o->width; ++i)
		tty_state_clear (o, i, y);

	return 1;
}

int tty_state_clear_line (struct tty_state *o, unsigned y)
{
	return tty_state_clear_left (o, 0, y);
}

int tty_state_clear_up (struct tty_state *o, unsigned y)
{
	unsigned j;

	for (j = 0; j < y; ++j)
		tty_state_clear_line (o, j);

	return 1;
}

int tty_state_clear_down (struct tty_state *o, unsigned y)
{
	unsigned j;

	for (j = y; j < o->height; ++j)
		tty_state_clear_line (o, j);

	return 1;
}

int tty_state_clear_all (struct tty_state *o)
{
	return tty_state_clear_down (o, 0);
}

int tty_state_scroll_up (struct tty_state *o, unsigned count)
{
	if (count > o->height)
		count = o->height;

	o->origin = (o->origin + count) % o->total;

	return tty_state_clear_down (o, o->height - count);
}

int tty_state_scroll_down (struct tty_state *o, unsigned count)
{
	if (count > o->height)
		count = o->height;

	o->origin = (o->origin + (o->total - count)) % o->total;

	return tty_state_clear_up (o, count);
}

void tty_state_put (struct tty_state *o, wchar_t c)
{
	struct tty_slot *s = tty_state_get_slot (o, o->x, o->y);

	tty_slot_set (s, tty_state_map (o, c), o->flags, o->fg, o->bg);
}

void tty_state_mark_dirty (struct tty_state *o, unsigned sx, unsigned sy,
			   unsigned ex, unsigned ey)
{
	unsigned i, j;
	struct tty_slot *s;

	if (ex > o->width)
		ex = o->width;

	if (ey > o->height)
		ey = o->height;

	for (j = sy; j < ey; ++j)
		for (i = sx; i < ex; ++i) {
			s = tty_state_get_slot (o, i, j);
			s->flags |= TTY_FLAGS_DIRTY;
		}
}

void tty_state_flush (struct tty_state *o, tty_state_cb *cb, void *cookie)
{
	unsigned i, j;
	struct tty_slot *s;

	for (j = 0; j < o->height; ++j)
		for (i = 0; i < o->width; ++i) {
			s = tty_state_get_slot (o, i, j);

			if ((s->flags & TTY_FLAGS_DIRTY) != 0 &&
			    cb (s, i, j, cookie))
				s->flags &= ~TTY_FLAGS_DIRTY;
		}
}
