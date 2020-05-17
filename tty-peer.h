/*
 * TTY Peer
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TTY_PEER_H
#define TTY_PEER_H  1

#include <wchar.h>

typedef int tty_read_fn (void *buf, unsigned count, void *cookie);
typedef int tty_write_fn (const void *buf, unsigned count, void *cookie);

struct tty_peer *tty_peer_alloc (tty_read_fn *read, tty_write_fn *write,
				 void *cookie);
void tty_peer_free (struct tty_peer *o);

int tty_peer_put  (struct tty_peer *o, wchar_t c);
int tty_peer_puts (struct tty_peer *o, const char *buf, unsigned count);

typedef void tty_peer_cb (wchar_t c, void *cookie);

int tty_peer_input (struct tty_peer *o, tty_peer_cb *cb, void *cookie);

#endif  /* TTY_PEER_H */
