/*
 * X11 Library Interface, Picture Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include "x11-pict.h"

int x11_fill_rect (struct x11_window *o, struct x11_gc *gc,
		   int x, int y, unsigned width, unsigned height)
{
	int op = gc->c.alpha == 0xffff ? PictOpSrc : PictOpOver;

	XRenderFillRectangle (o->parent->d, op, o->dst, &gc->c,
			      x, y, width, height);
	return 1;
}

static int x11_draw_prepare (struct x11_gc *o)
{
	if (o->font == NULL && !x11_gc_set_font (o, ""))
		return 0;

	XRenderFillRectangle (o->parent->d, PictOpSrc, o->src, &o->c,
			      0, 0, 1, 1);
	return 1;
}

int x11_draw_char (struct x11_window *o, struct x11_gc *gc,
		   int x, int y, unsigned c)
{
	int op = gc->c.alpha == 0xffff ? PictOpSrc : PictOpOver;
	FcChar32 symbol = c;

	if (!x11_draw_prepare (gc))
		return 0;

	XftTextRender32 (o->parent->d, op, gc->src, gc->font, o->dst, 0, 0,
			 x, y, &symbol, 1);
	return 1;
}

int x11_draw_string (struct x11_window *o, struct x11_gc *gc,
		     int x, int y, const char *text)
{
	int op = gc->c.alpha == 0xffff ? PictOpSrc : PictOpOver;

	if (!x11_draw_prepare (gc))
		return 0;

	XftTextRender8 (o->parent->d, op, gc->src, gc->font, o->dst, 0, 0,
			x, y, (const void *) text, strlen (text));
	return 1;
}
