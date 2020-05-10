/*
 * Coded Character Set Data
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_DATA_H
#define CCS_DATA_H  1

#include <stddef.h>

#include "ccs-slot.h"

#define CCS_FLAGS_APPLICATION	0x8000

struct ccs_data {
	unsigned width, height;	/* viewable size			*/
	unsigned total;		/* total number of lines in buffer	*/
	unsigned origin;	/* index of first line in buffer	*/

	struct ccs_slot *slot;	/* width × total slots	*/

	unsigned x, y;
	unsigned char fg, bg;
	unsigned short flags;
};

int ccs_data_init (struct ccs_data *o,
		   unsigned width, unsigned height, unsigned total);

void ccs_data_fini (struct ccs_data *o);

void ccs_data_reset (struct ccs_data *o);

void ccs_data_put   (struct ccs_data *o, wchar_t symbol);
void ccs_data_clear (struct ccs_data *o, unsigned y, unsigned x);

void ccs_data_copy_slot (struct ccs_data *o, unsigned sy, unsigned sx,
					     unsigned dy, unsigned dx);
void ccs_data_copy_line (struct ccs_data *o, unsigned sy, unsigned dy);

void ccs_data_mark_dirty (struct ccs_data *o, unsigned sx, unsigned sy,
			  unsigned ex, unsigned ey);

typedef int ccs_data_cb (const struct ccs_slot *slot, unsigned x, unsigned y,
			 void *cookie);
void ccs_data_flush (struct ccs_data *o, ccs_data_cb *cb, void *cookie);

#endif  /* CCS_DATA_H */
