/*
 * X11 Library Interface, Graphics Context Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stddef.h>
#include <fontconfig/fontconfig.h>

#include "x11-gc.h"

int x11_gc_init (struct x11_gc *o, struct x11_display *parent)
{
	XRenderPictFormat *fmt;
	Pixmap pix;
	XRenderPictureAttributes pa;

	o->parent = parent;

	/* render */

	fmt = XRenderFindStandardFormat (parent->d, PictStandardARGB32);
	if (fmt == NULL) {
		parent->error = "Cannot find ARGB32 Render format";
		return 0;
	}

	pix = XCreatePixmap (parent->d, x11_root (parent), 1, 1, fmt->depth);
	pa.repeat = True;
	o->src = XRenderCreatePicture (parent->d, pix, fmt, CPRepeat, &pa);
	XFreePixmap (parent->d, pix);

	/* render color */

	x11_gc_set_color_rgba (o, 0, 0, 0, 0xffff);

	/* fontconfig */

	if (!FcInit ()) {
		parent->error = "Cannot initialize font configuration";
		goto no_font;
	}

	o->font = NULL;
	return 1;
no_font:
	XRenderFreePicture (parent->d, o->src);
	return 0;
}

void x11_gc_fini (struct x11_gc *o)
{
	if (o->font != NULL)
		XftFontClose (o->parent->d, o->font);

	XRenderFreePicture (o->parent->d, o->src);
}

int x11_gc_set_color_rgba (struct x11_gc *o, int r, int g, int b, int a)
{
	o->c.red   = r;
	o->c.green = g;
	o->c.blue  = b;
	o->c.alpha = a;

	return 1;
}

int x11_gc_set_color (struct x11_gc *o, const char *pattern)
{
	return XRenderParseColor (o->parent->d, (void *) pattern, &o->c);
}

int x11_gc_set_font (struct x11_gc *o, const char *pattern)
{
	FcPattern *p, *match;
	FcResult ret;
	XftFont *font;

	if ((p = FcNameParse ((const void *) pattern)) == NULL) {
		o->parent->error = "Cannot parse font pattern";
		return 0;
	}

	if (!FcConfigSubstitute (NULL, p, FcMatchPattern)) {
		o->parent->error = "Cannot substitute font pattern";
		goto no_match;
	}

	FcDefaultSubstitute (p);

	if ((match = FcFontMatch (NULL, p, &ret)) == NULL) {
		o->parent->error = "Cannot find font";
		goto no_match;
	}

	FcPatternDestroy (p);

	font = XftFontOpenPattern (o->parent->d, match);
	FcPatternDestroy (match);

	if (font == NULL) {
		o->parent->error = "Cannot open font";
		return 0;
	}

	if (o->font != NULL)
		XftFontClose (o->parent->d, o->font);

	o->font = font;
	return 1;
no_match:
	FcPatternDestroy (p);
	return 0;
}
