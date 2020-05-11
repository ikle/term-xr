/*
 * Terminal Emulator Protocol Output
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdarg.h>
#include <stdio.h>

#include "tty-keys.h"
#include "tty-proto.h"

int tty_proto_printf (struct tty_proto *o, const char *fmt, ...)
{
	char buf[16];
	va_list ap;
	int len;

	va_start (ap, fmt);
	len = vsnprintf (buf, sizeof (buf), fmt, ap);
	va_end (ap);

	if (len >= sizeof (buf))
		return 0;

	return tty_peer_puts (o->peer, buf, len);
}

static int put_main (struct tty_proto *o, int mode, int idx)
{
	if ((mode & TTY_MODE_CONTROL) == 0 && idx > 0x1f)
		return 0;

	switch (idx) {
	case 0x32:	idx = 0;	break;
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:	idx -= 0x20;	break;
	default:	idx &= 0x1f;	break;
	}

	if ((mode & TTY_MODE_SHIFT) != 0) {
		if (!tty_peer_put (o->peer, 0x1b))
			return 0;

		idx |= 0x40;
	}

	return tty_peer_put (o->peer, idx);
}

static int emit_csi (struct tty_proto *o, int mode, int idx, int cmd)
{
	if (mode == 0)
		return tty_proto_printf (o, "\033\133%d%c", idx, cmd);

	return tty_proto_printf (o, "\033\133%u;%u%c", idx, mode + 1, cmd);
}

static int emit_ss3 (struct tty_proto *o, int mode, int cmd)
{
	if (mode == 0)
		return tty_proto_printf (o, "\033\117%c", cmd);

	return emit_csi (o, mode, 1, cmd);
}

static int put_edit (struct tty_proto *o, int mode, int idx)
{
	return emit_csi (o, mode, idx, 0x7e);
}

static int put_cursor (struct tty_proto *o, int mode, int idx)
{
	if ((o->state->flags & TTY_FLAGS_APPLICATION) != 0)
		return emit_ss3 (o, mode, idx);

	return emit_csi (o, mode, 1, idx);
}

static int put_aux (struct tty_proto *o, int mode, int idx)
{
	if ((o->state->flags & TTY_FLAGS_APPLICATION) != 0)
		idx |= 0x40;

	if ((idx & 0x40) != 0)
		return emit_ss3 (o, mode, idx);

	if (mode == 0)
		return tty_peer_put (o->peer, idx);

	return emit_ss3 (o, mode, idx);
}

int tty_proto_put_key (struct tty_proto *o, int mode, int key)
{
	switch (key & 0xff00) {
	case 0x0000:	return put_main   (o, mode, key & 0xff);
	case 0x0100:	return put_edit   (o, mode, key & 0xff);
	case 0x0200:	return put_cursor (o, mode, key & 0xff);
	case 0x0300:	return put_aux    (o, mode, key & 0xff);
	}

	return 0;
}
