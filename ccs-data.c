/*
 * Coded Character Set Data
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include "ccs-data.h"
#include "ccs-data-edit.h"

static struct ccs_slot *get_slot (struct ccs_data *o, unsigned x, unsigned y)
{
	size_t lineno = (o->origin + y) % o->total;

	return o->slot + o->width * lineno + x;
}

static void copy (struct ccs_data *from, struct ccs_data *to)
{
	unsigned w, h, i, j;

	w = from->width  < to->width  ? from->width  : to->width;
	h = from->height < to->height ? from->height : to->height;

	for (j = 0; j < h; ++j) {
		for (i = 0; i < w; ++i)
			ccs_slot_copy (get_slot (from, i, j),
				       get_slot (to,   i, j));

		ccs_data_clear_right (to, i, j);
	}

	ccs_data_clear_down (to, j);
}

static int ccs_data_resize (struct ccs_data *o, unsigned width, unsigned height)
{
	struct ccs_data s = *o;

	s.width   = width;
	s.height  = height;
	s.total   = o->total > height ? o->total : height;
	s.origin  = 0;

	if ((s.slot = malloc (width * s.total * sizeof (s.slot[0]))) == NULL)
		return 0;

	copy (o, &s);
	free (o->slot);

	if (s.x >= width)
		s.x = width - 1;

	if (s.y >= height)
		s.y = height - 1;

	*o = s;
	return 1;
}

int ccs_data_init (struct ccs_data *o,
		   unsigned width, unsigned height, unsigned total)
{
	o->width  = 0;
	o->height = 0;
	o->total  = total;
	o->slot   = NULL;

	ccs_data_reset (o);

	return ccs_data_resize (o, width, height);
}

void ccs_data_fini (struct ccs_data *o)
{
	free (o->slot);
}

void ccs_data_reset (struct ccs_data *o)
{
	o->x     = 0;
	o->y     = 0;
	o->fg    = CCS_COLOR_FG;
	o->bg    = CCS_COLOR_BG;
	o->flags = 0;

	ccs_data_clear_all (o);
}

void ccs_data_put (struct ccs_data *o, wchar_t c)
{
	struct ccs_slot *s = get_slot (o, o->x, o->y);

	ccs_slot_set (s, c, o->flags, o->fg, o->bg);
}

void ccs_data_clear (struct ccs_data *o, unsigned x, unsigned y)
{
	struct ccs_slot *s = get_slot (o, x, y);

	ccs_slot_set (s, 0, o->flags, o->fg, o->bg);
}

void ccs_data_copy_slot (struct ccs_data *o, unsigned sy, unsigned sx,
					     unsigned dy, unsigned dx)
{
	struct ccs_slot *from = get_slot (o, sx, sy);
	struct ccs_slot *to   = get_slot (o, dx, dy);

	ccs_slot_copy (from, to);
}

void ccs_data_copy_line (struct ccs_data *o, unsigned sy, unsigned dy)
{
	struct ccs_slot *from = get_slot (o, 0, sy);
	struct ccs_slot *to   = get_slot (o, 0, dy);

	memcpy (to, from, sizeof (*to) * o->width);

	ccs_data_mark_dirty (o, 0, dy, o->width, dy);
}

void ccs_data_mark_dirty (struct ccs_data *o, unsigned sx, unsigned sy,
			  unsigned ex, unsigned ey)
{
	unsigned i, j;
	struct ccs_slot *s;

	if (ex > o->width)
		ex = o->width;

	if (ey > o->height)
		ey = o->height;

	for (j = sy; j < ey; ++j)
		for (i = sx; i < ex; ++i) {
			s = get_slot (o, i, j);
			s->flags |= CCS_FLAGS_DIRTY;
		}
}

void ccs_data_flush (struct ccs_data *o, ccs_data_cb *cb, void *cookie)
{
	unsigned i, j;
	struct ccs_slot *s;

	for (j = 0; j < o->height; ++j)
		for (i = 0; i < o->width; ++i) {
			s = get_slot (o, i, j);

			if ((s->flags & CCS_FLAGS_DIRTY) != 0 &&
			    cb (s, i, j, cookie))
				s->flags &= ~CCS_FLAGS_DIRTY;
		}
}
