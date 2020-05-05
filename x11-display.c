/*
 * X11 Library Interface, Display Interface
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stddef.h>
#include <X11/extensions/Xrender.h>

#include "x11-display.h"

int x11_display_init (struct x11_display *o)
{
	int major, minor;

	/* display */

	if ((o->d = XOpenDisplay (NULL)) == NULL) {
		o->error = "Cannot open X11 display";
		return 0;
	}

	/* render */

	if (!XRenderQueryVersion (o->d, &major, &minor)) {
		o->error = "X11 Render extension does not supported";
		goto no_render;
	}

	/* X input method */

	if (!XSupportsLocale () || XSetLocaleModifiers ("") == NULL ||
	    (o->im = XOpenIM (o->d, NULL, NULL, NULL)) == NULL) {
		o->error = "XIM unavailable";
		goto no_xim;
	}

	return 1;
no_xim:
no_render:
	XCloseDisplay (o->d);
	return 0;
}

void x11_display_fini (struct x11_display *o)
{
	XCloseIM (o->im);
	XCloseDisplay (o->d);
}

int x11_next_event (struct x11_display *o, XEvent *e, int wait)
{
	for (;;) {
		if (XPending (o->d) <= 0 && !wait)
			return 0;

		XNextEvent (o->d, e);

		if (e->type == MappingNotify) {
			XRefreshKeyboardMapping (&e->xmapping);
			continue;
		}

		if (!XFilterEvent (e, None))
			break;
	}

	return 1;
}
