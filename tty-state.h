/*
 * Terminal Emulator State
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TTY_STATE_H
#define TTY_STATE_H  1

#include <stddef.h>

#include "tty-slot.h"

#define TTY_FLAGS_SHIFT		0x0100
#define TTY_FLAGS_APPLICATION 	0x8000

struct tty_state {
	unsigned width, height;	/* viewable size			*/
	unsigned total;		/* total number of lines in buffer	*/
	unsigned origin;	/* index of first line in buffer	*/

	struct tty_slot *slot;	/* width × total slots	*/

	unsigned x, y;
	unsigned char fg, bg;
	unsigned short flags;
	unsigned char charset[4];

	unsigned sx, sy;
	unsigned char sfg, sbg;
	unsigned short sflags;
	unsigned char scharset[4];
};

int tty_state_init (struct tty_state *o,
		    unsigned width, unsigned height, unsigned total);

void tty_state_fini (struct tty_state *o);

int tty_state_reset	(struct tty_state *o);
int tty_state_save	(struct tty_state *o);
int tty_state_restore	(struct tty_state *o);

int tty_state_set_x	(struct tty_state *o, int x);
int tty_state_set_y	(struct tty_state *o, int y);
int tty_state_move_y	(struct tty_state *o, int count);
int tty_state_move_x	(struct tty_state *o, int count);
int tty_state_tabulate	(struct tty_state *o);
int tty_state_index	(struct tty_state *o, int count);
int tty_state_forward	(struct tty_state *o);

int tty_state_clear_left  (struct tty_state *o, unsigned x, unsigned y);
int tty_state_clear_right (struct tty_state *o, unsigned x, unsigned y);
int tty_state_clear_line  (struct tty_state *o, unsigned y);

int tty_state_clear_up    (struct tty_state *o, unsigned y);
int tty_state_clear_down  (struct tty_state *o, unsigned y);
int tty_state_clear_all   (struct tty_state *o);

int tty_state_scroll_up   (struct tty_state *o, unsigned count);
int tty_state_scroll_down (struct tty_state *o, unsigned count);

wchar_t tty_state_map (struct tty_state *o, wchar_t c);

void tty_state_put (struct tty_state *o, wchar_t symbol);

void tty_state_mark_dirty (struct tty_state *o, unsigned sx, unsigned sy,
			   unsigned ex, unsigned ey);

typedef int tty_state_cb (const struct tty_slot *slot, unsigned x, unsigned y,
			  void *cookie);

void tty_state_flush (struct tty_state *o, tty_state_cb *cb, void *cookie);

#endif  /* TTY_STATE_H */
