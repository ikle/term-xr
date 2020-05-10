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
