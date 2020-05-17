/*
 * Coded Character Set Peer
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_PEER_H
#define CCS_PEER_H  1

#include <wchar.h>

typedef int ccs_read_fn (void *buf, unsigned count, void *cookie);
typedef int ccs_write_fn (const void *buf, unsigned count, void *cookie);

struct ccs_peer *ccs_peer_alloc (ccs_read_fn *read, ccs_write_fn *write,
				 void *cookie);
void ccs_peer_free (struct ccs_peer *o);

int ccs_peer_put  (struct ccs_peer *o, wchar_t c);
int ccs_peer_puts (struct ccs_peer *o, const char *buf, unsigned count);

typedef void ccs_peer_cb (wchar_t c, void *cookie);

int ccs_peer_input (struct ccs_peer *o, ccs_peer_cb *cb, void *cookie);

#endif  /* CCS_PEER_H */
