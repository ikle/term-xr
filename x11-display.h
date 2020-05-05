/*
 * X11 Library Interface, Display Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef IKLE_X11_DISPLAY_H
#define IKLE_X11_DISPLAY_H  1

#include <X11/Xlib.h>

struct x11_display {
	const char *error;
	Display *d;
	XIM im;
};

int  x11_display_init (struct x11_display *o);
void x11_display_fini (struct x11_display *o);

static inline int x11_screen (struct x11_display *o)
{
	return DefaultScreen (o->d);
}

static inline Window x11_root (struct x11_display *o)
{
	return RootWindow (o->d, x11_screen (o));
}

static inline Visual *x11_visual (struct x11_display *o)
{
	return DefaultVisual (o->d, x11_screen (o));
}

static inline int x11_pending (struct x11_display *o)
{
	return XPending (o->d);
}

int x11_next_event (struct x11_display *o, XEvent *e, int wait);

#endif  /* IKLE_X11_DISPLAY_H */
