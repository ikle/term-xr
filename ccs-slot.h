/*
 * Coded Character Set Slot
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_SLOT_H
#define CCS_SLOT_H  1

#include <wchar.h>

#define CCS_COLOR_BG		0
#define CCS_COLOR_FG		7
#define CCS_COLOR_BOLD		172
#define CCS_COLOR_ITALIC	142

#define CCS_FLAGS_BOLD		0x01
#define CCS_FLAGS_ITALIC	0x02
#define CCS_FLAGS_REVERSE	0x04

#define CCS_FLAGS_DIRTY		0x8000

struct ccs_slot {
	wchar_t	symbol;
	unsigned char fg, bg;
	unsigned short flags;
};

void ccs_slot_set (struct ccs_slot *o, wchar_t symbol, unsigned flags,
		   unsigned fg, unsigned bg);

void ccs_slot_copy (const struct ccs_slot *from, struct ccs_slot *to);

#endif  /* CCS_SLOT_H */
