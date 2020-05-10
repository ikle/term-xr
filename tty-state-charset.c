/*
 * TTY Character Set Mapping
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-state.h"

/* NOTE: assume wchar_t stores unicode character/codepoint */

static const wchar_t dec_graphics[32] = {
	0x00a0,
	0x25c6, 0x2592, 0x2409, 0x240c,  0x240d, 0x240a, 0x00b0, 0x00b1,
	0x2424, 0x240b, 0x2518, 0x2510,  0x250c, 0x2514, 0x253c, 0x23Ba,
	0x23Bb, 0x2500, 0x23Bc, 0x23Bd,  0x251c, 0x2524, 0x2534, 0x252c,
	0x2502, 0x2264, 0x2265, 0x03c0,  0x2260, 0x00a3, 0x00b7
};

static wchar_t tty_charset_map (unsigned set, wchar_t c)
{
	if (set == 0x30 && c >= 0x5f && c < 0x7f)
		return dec_graphics [c - 0x5f];

	return c;
}

wchar_t tty_state_map (struct tty_state *o, wchar_t c)
{
	unsigned char set = o->charset[(o->flags & TTY_FLAGS_SHIFT) != 0];

	return tty_charset_map (set, c);
}
