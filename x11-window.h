/*
 * X11 Library Interface, Window Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef IKLE_X11_WINDOW_H
#define IKLE_X11_WINDOW_H  1

#include "x11-display.h"
#include "x11-gc.h"

struct x11_window {
	struct x11_display *parent;
	Window w;
	Picture dst;
	XIC ic;
	char *text;
	unsigned avail;
};

int x11_window_init (struct x11_window *o, struct x11_display *parent,
		     const char *title, XSizeHints *sh);
void x11_window_fini (struct x11_window *o);

const char *x11_window_input  (struct x11_window *o, XKeyEvent *e);
const char *x11_window_hotkey (struct x11_window *o, XKeyEvent *e);

#endif  /* IKLE_X11_WINDOW_H */
