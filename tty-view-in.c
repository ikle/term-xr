/*
 * Terminal Emulator X11 View Input
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-view.h"
#include "tty-view-keymap.h"

int tty_view_input (struct tty_view *o)
{
	XKeyEvent *e = &o->e.xkey;
	int s, mode = 0;
	const char *text;

	if (o->e.xany.type != KeyPress)
		return 0;

	s = tty_view_x11_to_tty (XLookupKeysym (e, 0));

	if (s > 0) {
		if ((e->state & ShiftMask) != 0)
			mode |= TTY_MODE_SHIFT;

		if ((e->state & Mod1Mask) != 0)
			mode |= TTY_MODE_ALT;

		if ((e->state & ControlMask) != 0)
			mode |= TTY_MODE_CONTROL;

		if (tty_proto_put_key (o->proto, mode, s))
			return 1;
	}

	if ((text = x11_window_input (&o->w, e)) != NULL)
		return tty_proto_puts (o->proto, text, 0);

	return 0;
}
