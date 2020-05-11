/*
 * Terminal Emulator Slot
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-slot.h"

void tty_slot_set (struct tty_slot *o, wchar_t symbol, unsigned flags,
		   int fg, int bg)
{
	if (fg == TTY_COLOR_FG)
		fg = (flags & TTY_FLAGS_BOLD)   != 0 ? TTY_COLOR_BOLD   :
		     (flags & TTY_FLAGS_ITALIC) != 0 ? TTY_COLOR_ITALIC : fg;

	if ((flags & TTY_FLAGS_REVERSE) != 0) {
		o->fg = bg;
		o->bg = fg;
	}
	else {
		o->fg = fg;
		o->bg = bg;
	}

	o->symbol = symbol;
	o->flags  = flags | TTY_FLAGS_DIRTY;
}

void tty_slot_copy (const struct tty_slot *from, struct tty_slot *to)
{
	tty_slot_set (to, from->symbol, from->flags, from->fg, from->bg);
}
