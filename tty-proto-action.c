/*
 * TTY Protocol Actions
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-proto.h"

static int bound (int x)
{
	return x == 0 ? 1 : x;
}

int tty_proto_do_csi (struct tty_proto *o, int c)
{
	struct tty_state *s = o->state;
	const wchar_t *a = o->arg;

	switch (c) {
	case 0x41:
		return tty_state_move_y (s, -bound (a[0]));
	case 0x42:
		return tty_state_move_y (s,  bound (a[0]));
	case 0x43:
		return tty_state_move_x (s,  bound (a[0]));
	case 0x44:
		return tty_state_move_x (s, -bound (a[0]));
	case 0x45:
		tty_state_move_x (s, 0);
		return tty_state_move_y (s,  bound (a[0]));
	case 0x46:
		tty_state_move_x (s, 0);
		return tty_state_move_y (s, -bound (a[0]));
	case 0x47:
		return tty_state_set_x  (s, bound (a[0]) - 1);
	case 0x48:
	case 0x66:
		tty_state_set_x  (s, bound (a[1]) - 1);
		return tty_state_set_x  (s, bound (a[0]) - 1);
	case 0x4a:
		switch (a[0]) {
		case 0:		return tty_state_clear_down (s, s->y);
		case 1:		return tty_state_clear_up   (s, s->y);
		case 2:
		case 3:		return tty_state_clear_all  (s);
		default:	return 0;
		}
	case 0x4b:
		switch (a[0]) {
		case 0:		return tty_state_clear_right (s, s->x, s->y);
		case 1:		return tty_state_clear_left  (s, s->x, s->y);
		case 2:		return tty_state_clear_line  (s, s->y);
		default:	return 0;
		}
	case 0x53:
		return tty_state_scroll_up   (s, bound (a[0]));
	case 0x54:
		return tty_state_scroll_down (s, bound (a[0]));
	case 0x6e:
		if (a[0] == 6)
			return tty_proto_printf (o, "\033\133%u;%u\122",
						 s->y + 1, s->x + 1);

		return 0;
	}

	return 0;
}
