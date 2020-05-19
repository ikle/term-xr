/*
 * TTY Protocol Actions
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-proto.h"

#define ARRAY_SIZE(a)  (sizeof (a) / sizeof ((a)[0]))

static int bound (int x)
{
	return x == 0 ? 1 : x;
}

static int tty_proto_do_sgrs (struct tty_proto *o);

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
	case 0x6d:
		return tty_proto_do_sgrs (o);
	case 0x6e:
		if (a[0] == 6)
			return tty_proto_printf (o, "\033\133%u;%u\122",
						 s->y + 1, s->x + 1);

		return 0;
	}

	return 0;
}

static int tty_proto_do_sgr (struct tty_proto *o, unsigned i)
{
	struct tty_state *s = o->state;
	const wchar_t *a = o->arg + i;

	switch (a[0]) {
	case 0:		s->flags &= ~TTY_FLAGS_ATTR_MASK;	return 1;
	case 1:		s->flags |= TTY_FLAGS_BOLD;		return 1;
	case 3:
	case 4:
	case 20:
	case 21:	s->flags |= TTY_FLAGS_ITALIC;		return 1;
	case 7:		s->flags |= TTY_FLAGS_REVERSE;		return 1;
	case 22:	s->flags &= ~TTY_FLAGS_BOLD;		return 1;
	case 23:
	case 24:	s->flags &= ~TTY_FLAGS_ITALIC;		return 1;
	case 27:	s->flags &= ~TTY_FLAGS_REVERSE;		return 1;

	case 30: case 31: case 32: case 33:
	case 34: case 35: case 36: case 37: s->fg = a[0] - 30;	return 1;
	case 38:
		switch (a[1]) {
		case 2:						return 5;
		case 5:		s->fg = a[2];			return 3;
		default:					return 2;
		}
	case 39:	s->fg = TTY_COLOR_FG;			return 1;

	case 40: case 41: case 42: case 43:
	case 44: case 45: case 46: case 47: s->bg = a[0] - 40;	return 1;
	case 48:
		switch (a[1]) {
		case 2:						return 5;
		case 5:		s->bg = a[2];			return 3;
		default:					return 2;
		}
	case 49:	s->bg = TTY_COLOR_BG;			return 1;
	}

	return 1;
}

#define ARG_LIMIT(o)  (ARRAY_SIZE ((o)->arg) - 2)  /* up to 2 SGR argumets */

static int tty_proto_do_sgrs (struct tty_proto *o)
{
	unsigned i = 0;

	if (o->index > ARG_LIMIT (o))
		o->index = ARG_LIMIT (o);

	do {
		i += tty_proto_do_sgr (o, i);
	}
	while (i < o->index);

	return 1;
}
