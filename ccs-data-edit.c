/*
 * Coded Character Set Data Editor helpers
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ccs-data-edit.h"

/* Erasing helpers */

int ccs_data_clear_left (struct ccs_data *o, unsigned y, unsigned x)
{
	unsigned i;

	for (i = 0; i < x; ++i)
		ccs_data_clear (o, y, i);

	return 1;
}

int ccs_data_clear_right (struct ccs_data *o, unsigned y, unsigned x)
{
	unsigned i;

	for (i = x; i < o->width; ++i)
		ccs_data_clear (o, y, i);

	return 1;
}

int ccs_data_clear_line (struct ccs_data *o, unsigned y)
{
	return ccs_data_clear_right (o, y, 0);
}

int ccs_data_clear_up (struct ccs_data *o, unsigned y)
{
	unsigned j;

	for (j = 0; j < y; ++j)
		ccs_data_clear_line (o, j);

	return 1;
}

int ccs_data_clear_down (struct ccs_data *o, unsigned y)
{
	unsigned j;

	for (j = y; j < o->height; ++j)
		ccs_data_clear_line (o, j);

	return 1;
}

int ccs_data_clear_all (struct ccs_data *o)
{
	return ccs_data_clear_down (o, 0);
}

/* 8.2.6 Editor functions */

int ccs_data_dch (struct ccs_data *o, int count)
{
	unsigned i, limit;

	if (count <= 0)
		count = 1;
	else if (count > (o->width - o->x))
		count = o->width - o->x;

	for (i = o->x, limit = o->width - count; i < limit; ++i)
		ccs_data_copy_slot (o, o->y, i + count, o->y, i);

	return ccs_data_clear_right (o, o->y, i);
}

int ccs_data_dl (struct ccs_data *o, int count)
{
	unsigned j, limit;

	if (count <= 0)
		count = 1;
	else if (count > (o->height - o->y))
		count = o->height - o->y;

	for (j = o->y, limit = o->height - count; j < limit; ++j)
		ccs_data_copy_line (o, j + count, j);

	return ccs_data_clear_down (o, j);
}

int ccs_data_ich (struct ccs_data *o, int count)
{
	unsigned i, limit;

	if (count <= 0)
		count = 1;
	else if (count > (o->width - o->x))
		count = o->width - o->x;

	for (i = o->width - 1, limit = o->x + count; i <= limit; --i)
		ccs_data_copy_slot (o, o->y, i - count, o->y, i);

	for (i = o->x; i < limit; ++i)
		ccs_data_clear (o, o->y, i);

	return 1;
}

int ccs_data_il (struct ccs_data *o, int count)
{
	unsigned j, limit;

	if (count <= 0)
		count = 1;
	else if (count > (o->height - o->y))
		count = o->height - o->y;

	for (j = o->height - 1, limit = o->y + count; j <= limit; --j)
		ccs_data_copy_line (o, j - count, j);

	for (j = o->y; j < limit; ++j)
		ccs_data_clear_line (o, j);

	return 1;
}

int ccs_data_ech (struct ccs_data *o, int count)
{
	unsigned i;

	for (i = o->x; count > 0; ++i, --count)
		ccs_data_clear (o, o->y, i);

	return 1;
}

int ccs_data_el (struct ccs_data *o, int mode)
{
	switch (mode) {
	case 0:		return ccs_data_clear_right (o, o->y, o->x);
	case 1:		return ccs_data_clear_left  (o, o->y, o->x + 1);
	case 2:		return ccs_data_clear_line  (o, o->y);
	}

	return 1;
}

int ccs_data_ed (struct ccs_data *o, int mode)
{
	switch (mode) {
	case 0:		return ccs_data_clear_down (o, o->y);
	case 1:		return ccs_data_clear_up   (o, o->y + 1);
	case 2:		return ccs_data_clear_all  (o);
	}

	return 1;
}

/* 8.2.8 Display control functions */

int ccs_data_sd (struct ccs_data *o, int count)
{
	if (count <= 0)
		count = 1;
	else if (count > o->height)
		count = o->height;

	o->origin = (o->origin + (o->total - count)) % o->total;

	return ccs_data_clear_up (o, count);
}

int ccs_data_su (struct ccs_data *o, int count)
{
	if (count <= 0)
		count = 1;
	else if (count > o->height)
		count = o->height;

	o->origin = (o->origin + count) % o->total;

	return ccs_data_clear_down (o, o->height - count);
}
