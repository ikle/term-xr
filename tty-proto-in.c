/*
 * Terminal Emulator Protocol Input
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "tty-proto.h"

enum tty_proto_mode {
	TTY_STATE_START = 0,
	TTY_STATE_ESCAPE,
	TTY_STATE_DCS,
	TTY_STATE_SOS,
	TTY_STATE_CSI,
	TTY_STATE_OSC,
	TTY_STATE_PM,
	TTY_STATE_APC,
};

static int tty_proto_next (struct tty_proto *o, unsigned mode)
{
	o->mode = mode;
	return 1;
}

static int tty_proto_commit (struct tty_proto *o)
{
	/* Todo: parse DCS, OSC, SOS, PM and APC here */

	return tty_proto_next (o, TTY_STATE_START);
}

static int tty_proto_c0 (struct tty_proto *o, wchar_t c)
{
	struct tty_state *s = o->state;

	switch (c) {
	case 0x08:	return tty_state_move_x (s, -1);
	case 0x09:	return tty_state_tabulate (s);
	case 0x0a:
	case 0x0b:
	case 0x0c:	return tty_state_index (s, 1);
	case 0x0d:	return tty_state_set_x (s, 0);
	case 0x0e:	s->flags |=  TTY_FLAGS_SHIFT;	return 1;
	case 0x0f:	s->flags &= ~TTY_FLAGS_SHIFT;	return 1;
	case 0x18:
	case 0x1a:	return tty_proto_next (o, TTY_STATE_START);
	case 0x1b:	return tty_proto_next (o, TTY_STATE_ESCAPE);
	}

	return 1;
}

static int tty_proto_c1 (struct tty_proto *o, wchar_t c)
{
	struct tty_state *s = o->state;

	switch (c) {
	case 0x84:	return tty_state_index (s, 1);
	case 0x85:	return tty_state_index (s, 1) && tty_state_set_x (s, 0);
	case 0x88:	return tty_state_index (s, -1);
	case 0x90:	return tty_proto_next (o, TTY_STATE_DCS);
	case 0x98:	return tty_proto_next (o, TTY_STATE_SOS);
	case 0x9b:	return tty_proto_next (o, TTY_STATE_CSI);
	case 0x9c:	return tty_proto_commit (o);
	case 0x9d:	return tty_proto_next (o, TTY_STATE_OSC);
	case 0x9e:	return tty_proto_next (o, TTY_STATE_PM);
	case 0x9f:	return tty_proto_next (o, TTY_STATE_APC);
	}

	return 1;
}

static int tty_proto_escape (struct tty_proto *o, wchar_t c)
{
	struct tty_state *s = o->state;

	if (c >= 0x40 && c < 0x50)
		return tty_proto_c1 (o, c + 0x40);

	switch (c) {
	case 0x37:	tty_state_save    (o->state);		break;
	case 0x38:	tty_state_restore (o->state);		break;
	case 0x3d:	s->flags |=  TTY_FLAGS_APPLICATION;	break;
	case 0x3e:	s->flags &= ~TTY_FLAGS_APPLICATION;	break;
	case 0x63:	tty_state_reset   (o->state);		break;
	}

	return tty_proto_next (o, TTY_STATE_START);
}

static int tty_proto_wait_st (struct tty_proto *o, wchar_t c)
{
	/* Todo: accumulate parameter string here */
	return 1;
}

static int tty_proto_csi (struct tty_proto *o, wchar_t c)
{
	if (c >= 0x40 && c < 0x7f) {
		/* Todo: parse command here */

		return tty_proto_next (o, TTY_STATE_START);
	}

	/* Todo: accumulate parameter string here */
	return 1;
}

static int tty_proto_action (struct tty_proto *o, wchar_t c)
{
	if (c < 0x20)
		return tty_proto_c0 (o, c);

	if (c >= 0x80 && c < 0xa0)
		return tty_proto_c1 (o, c);

	switch (o->mode) {
	case TTY_STATE_ESCAPE:	return tty_proto_escape (o, c);
	case TTY_STATE_CSI:	return tty_proto_csi    (o, c);
	case TTY_STATE_DCS:
	case TTY_STATE_SOS:
	case TTY_STATE_OSC:
	case TTY_STATE_PM:
	case TTY_STATE_APC:	return tty_proto_wait_st (o, c);
	}

	tty_state_put (o->state, c);
	tty_state_forward (o->state);
	return 1;
}

static void cb (wchar_t c, void *cookie)
{
	struct tty_proto *o = cookie;

	tty_proto_action (o, c);
}

int tty_proto_input (struct tty_proto *o)
{
	return tty_peer_input (o->peer, cb, o);
}
