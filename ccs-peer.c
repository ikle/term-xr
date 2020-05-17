/*
 * Coded Character Set Peer
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "ccs-peer.h"

struct ccs_peer {
	void *cookie;
	ccs_read_fn *read;
	ccs_write_fn *write;

	char line[256];
	unsigned avail;

	mbstate_t in, out;
};

struct ccs_peer *ccs_peer_alloc (ccs_read_fn *read, ccs_write_fn *write,
				 void *cookie)
{
	struct ccs_peer *o;

	if (read == NULL || write == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->cookie = cookie;
	o->read   = read;
	o->write  = write;

	o->avail = 0;

	memset (&o->in,  0, sizeof (o->in));
	memset (&o->out, 0, sizeof (o->out));
	return o;
}

void ccs_peer_free (struct ccs_peer *o)
{
	free (o);
}

int ccs_peer_put (struct ccs_peer *o, wchar_t c)
{
	char buf[MB_LEN_MAX];
	int count;;

	if ((count = wcrtomb (buf, c, &o->out)) < 0)
		return 0;

	return o->write (buf, count, o->cookie) == count;
}

int ccs_peer_puts (struct ccs_peer *o, const char *buf, unsigned count)
{
	if (count == 0)
		count = strlen (buf);

	return o->write (buf, count, o->cookie) == count;
}

int ccs_peer_input (struct ccs_peer *o, ccs_peer_cb *cb, void *cookie)
{
	int count;
	const char *p;
	wchar_t c;

	for (;;) {
		count = sizeof (o->line) - o->avail;
		count = o->read (o->line + o->avail, count, o->cookie);
		if (count <= 0)
			break;

		o->avail += count;

		for (p = o->line; o->avail > 0; p += count, o->avail -= count) {
			if ((count = mbrtowc (&c, p, o->avail, &o->in)) > 0) {
				cb (c, cookie);
				continue;
			}

			if (count == -2)  /* incomplete sequence */
				break;

			/* reset state and ignore byte */
			memset (&o->in, 0, sizeof (o->in));
			count = 1;
		}

		if (o->avail == sizeof (o->line))  /* too long sequence? */
			++p, --o->avail;           /* drop one byte      */

		memmove (o->line, p, o->avail);
	}

	return count >= 0;
}
