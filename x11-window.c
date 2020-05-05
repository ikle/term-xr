/*
 * X11 Library Interface, Window Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <X11/extensions/Xrender.h>

#include "x11-window.h"

static
void create_window (struct x11_window *o, const char *title, XSizeHints *sh)
{
	int w, h;
	XSetWindowAttributes a;

	if ((sh->flags & PSize) != 0) {
		w = sh->width;
		h = sh->height;
	}
	else if ((sh->flags & PMinSize) != 0) {
		w = sh->min_width;
		h = sh->min_height;
	}
	else {
		w = 200;
		h = 200;
	}

	a.event_mask = KeyPressMask | ExposureMask | StructureNotifyMask;

	o->w = XCreateWindow (o->parent->d, x11_root (o->parent), 0, 0, w, h,
			      0, CopyFromParent, InputOutput, CopyFromParent,
			      CWEventMask, &a);

	XmbSetWMProperties (o->parent->d, o->w, title, NULL, NULL, 0,
			    sh, NULL, NULL);

	XMapWindow (o->parent->d, o->w);
}

int x11_window_init (struct x11_window *o, struct x11_display *parent,
		     const char *title, XSizeHints *sh)
{
	XRenderPictFormat *fmt;
	const unsigned long style = XIMPreeditNothing | XIMStatusNothing;

	o->parent = parent;

	create_window (o, title, sh);

	/* render */

	fmt = XRenderFindVisualFormat (parent->d, x11_visual (parent));
	if (fmt == NULL) {
		parent->error = "Cannot find Render format for X11";
		goto no_render;
	}

	o->dst = XRenderCreatePicture (parent->d, o->w, fmt, 0, NULL);

	/* X input method context */

	o->ic = XCreateIC (parent->im, XNInputStyle, style,
			   XNClientWindow, o->w, NULL);
	if (o->ic == NULL) {
		parent->error = "Cannot create XIM context";
		goto no_ic;
	}

	XSetICFocus (o->ic);
	o->text  = NULL;
	o->avail = 0;
	return 1;
no_ic:
	XRenderFreePicture (parent->d, o->dst);
no_render:
	XDestroyWindow (parent->d, o->w);
	return 0;
}

void x11_window_fini (struct x11_window *o)
{
	free (o->text);
	XDestroyIC (o->ic);
	XRenderFreePicture (o->parent->d, o->dst);
	XDestroyWindow (o->parent->d, o->w);
}

const char *x11_window_input (struct x11_window *o, XKeyEvent *e)
{
	int count;
	Status st;
	char *buf;

	count = XmbLookupString (o->ic, e, o->text, o->avail, NULL, &st);

	if (count >= o->avail) {
		if ((buf = realloc (o->text, count + 1)) == NULL) {
			o->parent->error = "Cannot allocate buffer for text";
			return NULL;
		}

		o->text  = buf;
		o->avail = count + 1;

		count = XmbLookupString (o->ic, e, o->text, o->avail, NULL, &st);
	}

	if (st != XLookupChars && st != XLookupBoth)
		return NULL;

	o->text[count] = '\0';
	return o->text;
}

static unsigned putbuf (struct x11_window *o, unsigned i, int c)
{
	if (i < o->avail)
		o->text[i] = c;

	return i + 1;
}

static unsigned parse_hotkey (struct x11_window *o, XKeyEvent *e)
{
	KeySym s = XLookupKeysym (e, 0);
	size_t i = 0;
	const char *name;

	if (s == NoSymbol)
		return 0;

	if ((e->state & ControlMask) != 0)	i = putbuf (o, i, 'C');
	if ((e->state & ShiftMask  ) != 0)	i = putbuf (o, i, 'S');
	if ((e->state & Mod1Mask   ) != 0)	i = putbuf (o, i, 'M');
	if ((e->state & Mod4Mask   ) != 0)	i = putbuf (o, i, 'H');

	if (i > 0)
		i = putbuf (o, i, '-');

	if ((name = XKeysymToString (s)) == NULL)
		return 0;

	for (; *name != '\0'; ++name)
		i = putbuf (o, i, *name == '_' ? '-' : tolower (*name));

	return putbuf (o, i, '\0');
}

const char *x11_window_hotkey (struct x11_window *o, XKeyEvent *e)
{
	unsigned count;
	char *buf;

	if ((count = parse_hotkey (o, e)) == 0)
		return NULL;

	if (count >= o->avail) {
		if ((buf = realloc (o->text, count + 1)) == NULL) {
			o->parent->error = "Cannot allocate buffer for hotkey";
			return NULL;
		}

		o->text  = buf;
		o->avail = count + 1;

		parse_hotkey (o, e);
	}

	return o->text;
}
