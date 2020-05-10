/*
 * Terminal Emulator State Actions
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include "tty-state.h"

int tty_state_reset (struct tty_state *o)
{
	o->x     = 0;
	o->y     = 0;
	o->fg    = TTY_COLOR_FG;
	o->bg    = TTY_COLOR_BG;
	o->flags = 0;

	memset (o->charset, 0, sizeof (o->charset));

	tty_state_save (o);
	return tty_state_clear_all (o);
}

int tty_state_save (struct tty_state *o)
{
	o->sx     = o->x;
	o->sy     = o->y;
	o->sfg    = o->fg;
	o->sbg    = o->bg;
	o->sflags = o->flags;

	memcpy (o->scharset, o->charset, sizeof (o->charset));
	return 1;
}

int tty_state_restore (struct tty_state *o)
{
	o->x     = o->sx;
	o->y     = o->sy;
	o->fg    = o->sfg;
	o->bg    = o->sbg;
	o->flags = o->sflags;

	memcpy (o->charset, o->scharset, sizeof (o->charset));
	return 1;
}

int tty_state_set_x (struct tty_state *o, int x)
{
	o->x = x < 0 ? 0 : x >= o->width ? o->width : x;
	return 1;
}

int tty_state_set_y (struct tty_state *o, int y)
{
	o->y = y < 0 ? 0 : y >= o->height ? o->height : y;
	return 1;
}

int tty_state_move_y (struct tty_state *o, int count)
{
	return tty_state_set_y (o, o->y + count);
}

int tty_state_move_x (struct tty_state *o, int count)
{
	return tty_state_set_x (o, o->x + count);
}

int tty_state_tabulate (struct tty_state *o)
{
	return tty_state_set_x (o, (o->x + 8) & ~7);
}

int tty_state_index (struct tty_state *o, int count)
{
	int y = o->y + count;

	tty_state_move_y (o, count);

	if (y < 0)
		return tty_state_scroll_down (o, -y);

	if (y >= o->height)
		return tty_state_scroll_up (o, y - (o->height - 1));

	return 1;
}

int tty_state_forward (struct tty_state *o)
{
	if (++o->x < o->width)
		return 1;

	tty_state_set_x (o, 0);
	return tty_state_index (o, 1);
}
