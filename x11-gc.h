/*
 * X11 Library Interface, Graphics Context Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef IKLE_X11_GC_H
#define IKLE_X11_GC_H  1

#include <X11/Xft/Xft.h>

#include "x11-display.h"

struct x11_gc {
	struct x11_display *parent;
	XRenderColor c;
	Picture src;
	XftFont *font;
};

int  x11_gc_init (struct x11_gc *o, struct x11_display *parent);
void x11_gc_fini (struct x11_gc *o);

int x11_gc_set_color_rgba (struct x11_gc *o, int r, int g, int b, int a);
int x11_gc_set_color (struct x11_gc *o, const char *pattern);

int x11_gc_set_font (struct x11_gc *o, const char *pattern);

#endif  /* IKLE_X11_GC_H */
