/*
 * Terminal Emulator Slot
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TTY_SLOT_H
#define TTY_SLOT_H  1

#include <wchar.h>

#define TTY_COLOR_BG		0
#define TTY_COLOR_FG		7
#define TTY_COLOR_BOLD		172
#define TTY_COLOR_ITALIC	142

#define TTY_FLAGS_BOLD		0x01
#define TTY_FLAGS_ITALIC	0x02
#define TTY_FLAGS_REVERSE	0x04
#define TTY_FLAGS_ATTR_MASK	0x07
#define TTY_FLAGS_DIRTY		0x80

struct tty_slot {
	wchar_t	symbol;
	unsigned char fg, bg;
	unsigned short flags;
};

void tty_slot_set (struct tty_slot *o, wchar_t symbol, unsigned flags,
		   int fg, int bg);

void tty_slot_copy (const struct tty_slot *from, struct tty_slot *to);

#endif  /* TTY_SLOT_H */
