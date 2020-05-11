/*
 * Coded Character Set Slot
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ccs-slot.h"

void ccs_slot_set (struct ccs_slot *o, wchar_t symbol, unsigned flags,
		   unsigned fg, unsigned bg)
{
	if (fg == CCS_COLOR_FG) {
		fg = (flags & CCS_FLAGS_BOLD)   != 0 ? CCS_COLOR_BOLD   :
		     (flags & CCS_FLAGS_ITALIC) != 0 ? CCS_COLOR_ITALIC : fg;
	}
	else if (fg < 8 && flags & CCS_FLAGS_BOLD)
		fg += 8;  /* bright it */

	if ((flags & CCS_FLAGS_REVERSE) != 0) {
		o->fg = bg;
		o->bg = fg;
	}
	else {
		o->fg = fg;
		o->bg = bg;
	}

	o->symbol = symbol;
	o->flags  = flags | CCS_FLAGS_DIRTY;
}

void ccs_slot_copy (const struct ccs_slot *from, struct ccs_slot *to)
{
	*to = *from;

	to->flags |= CCS_FLAGS_DIRTY;
}
