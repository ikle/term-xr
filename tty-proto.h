/*
 * Terminal Emulator Protocol
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TTY_PROTO_H
#define TTY_PROTO_H  1

#include <wchar.h>

#include "tty-peer.h"
#include "tty-state.h"

struct tty_proto {
	struct tty_peer  *peer;
	struct tty_state *state;
	unsigned char mode;
};

static inline
int tty_proto_init (struct tty_proto *o, struct tty_peer *peer,
		    struct tty_state *state)
{
	o->peer  = peer;
	o->state = state;
	o->mode  = 0;
	return 1;
}

static inline
void tty_proto_fini (struct tty_proto *o) {}

int tty_proto_input (struct tty_proto *o);
int tty_proto_put_key (struct tty_proto *o, int mode, int key);

static inline
int tty_proto_puts (struct tty_proto *o, const void *buf, unsigned count)
{
	return tty_peer_puts (o->peer, buf, count);
}

int tty_proto_printf (struct tty_proto *o, const char *fmt, ...);

#endif  /* TTY_PROTO_H */
