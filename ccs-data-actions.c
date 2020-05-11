/*
 * Coded Character Set Data Actions
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ccs-data-actions.h"
#include "ccs-data-edit.h"

/* Cursor setup helpers */

static int set_x (struct ccs_data *o, int x)
{
	o->x = x < 0 ? 0 : x >= o->width ? o->width - 1 : x;
	return 1;
}

static int set_y (struct ccs_data *o, int y)
{
	o->y = y < 0 ? 0 : y >= o->height ? o->height - 1 : y;
	return 1;
}

static int move_x (struct ccs_data *o, int count)
{
	return set_x (o, o->x + count);
}

static int move_y (struct ccs_data *o, int count)
{
	return set_y (o, o->y + count);
}

static int tab_left (struct ccs_data *o)
{
	return set_x (o, (o->x - 1) & ~7);
}

static int tab_right (struct ccs_data *o)
{
	return set_x (o, (o->x + 8) & ~7);
}

/* 8.2.4 Format effectors */

int ccs_data_ind (struct ccs_data *o)
{
	int y = o->y + 1;

	move_y (o, 1);

	if (y >= o->height)
		return ccs_data_su (o, 1);

	return 1;
}

int ccs_data_ri (struct ccs_data *o)
{
	int y = o->y - 1;

	move_y (o, -1);

	if (y < 0)
		return ccs_data_sd (o, 1);

	return 1;
}

int ccs_data_bs (struct ccs_data *o)
{
	return move_x (o, -1);
}

int ccs_data_ht (struct ccs_data *o)
{
	return tab_right (o);
}

int ccs_data_cr (struct ccs_data *o)
{
	return set_x (o, 0);
}

int ccs_data_vpa (struct ccs_data *o, int y)
{
	return set_y (o, y <= 0 ? 0 : y - 1);
}

/* 8.2.7 Cursor control functions */

int ccs_data_cud (struct ccs_data *o, int count)
{
	return move_y (o, count <= 0 ? 1 : count);
}

int ccs_data_cuu (struct ccs_data *o, int count)
{
	return move_y (o, count <= 0 ? -1 : -count);
}

int ccs_data_cuf (struct ccs_data *o, int count)
{
	return move_x (o, count <= 0 ? 1 : count);
}

int ccs_data_cub (struct ccs_data *o, int count)
{
	return move_x (o, count <= 0 ? -1 : -count);
}

int ccs_data_cbt (struct ccs_data *o, int count)
{
	if (count <= 0)
		count = 1;

	for (; count > 0; --count)
		tab_left (o);

	return 1;
}

int ccs_data_cht (struct ccs_data *o, int count)
{
	if (count <= 0)
		count = 1;

	for (; count > 0; --count)
		tab_right (o);

	return 1;
}

int ccs_data_cvt (struct ccs_data *o, int count)
{
	return ccs_data_cud (o, count);
}

int ccs_data_cnl (struct ccs_data *o, int count)
{
	ccs_data_cud (o, count);

	return set_x (o, 0);
}

int ccs_data_cpl (struct ccs_data *o, int count)
{
	ccs_data_cuu (o, count);

	return set_x (o, 0);
}

int ccs_data_cha (struct ccs_data *o, int x)
{
	return set_x (o, x <= 0 ? 0 : x - 1);
}

int ccs_data_cup (struct ccs_data *o, int y, int x)
{
	set_y (o, y <= 0 ? 0 : y - 1);
	return set_x (o, x <= 0 ? 0 : x - 1);
}
