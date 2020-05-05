/*
 * X11 Library Interface, Graphics Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef IKLE_X11_PICT_H
#define IKLE_X11_PICT_H  1

#include "x11-gc.h"
#include "x11-window.h"

int x11_fill_rect (struct x11_window *o, struct x11_gc *gc,
		   int x, int y, unsigned width, unsigned height);

int x11_draw_char (struct x11_window *o, struct x11_gc *gc,
		   int x, int y, unsigned c);

int x11_draw_string (struct x11_window *o, struct x11_gc *gc,
		     int x, int y, const char *text);

#endif  /* IKLE_X11_PICT_H */
