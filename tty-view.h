/*
 * Terminal Emulator X11 Render View
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TTY_VIEW_H
#define TTY_VIEW_H  1

#include <stddef.h>

#include "tty-proto.h"
#include "tty-state.h"
#include "x11-pict.h"

struct tty_view {
	struct tty_proto *proto;
	struct tty_state *state;

	struct x11_display d;
	struct x11_gc gc;
	struct x11_window w;

	int width, height;  /* slot size on screen */

	XEvent e;
};

int tty_view_init (struct tty_view *o, struct tty_proto *proto,
		   struct tty_state *state);

void tty_view_fini (struct tty_view *o);

int tty_view_input  (struct tty_view *o);
int tty_view_render (struct tty_view *o);

int tty_view_process (struct tty_view *o);

#endif  /* TTY_VIEW_H */
