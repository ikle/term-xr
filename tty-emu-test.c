/*
 * Terminal Emulator
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <locale.h>

#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#include "tty-view.h"

static int sys_read (void *buf, unsigned count, void *cookie)
{
	return read (cookie - NULL, buf, count);
}

static int sys_write (const void *buf, unsigned count, void *cookie)
{
	return write (cookie - NULL, buf, count);
}

int tty_app_run (int fd)
{
	struct tty_peer *peer;
	struct tty_state state;
	struct tty_proto proto;
	struct tty_view view;

	struct pollfd pfd[2];

	if ((peer = tty_peer_alloc (sys_read, sys_write, NULL + fd)) == NULL)
		return 0;

	if (!tty_state_init (&state, 80, 40, 100))
		goto no_state;

	if (!tty_proto_init (&proto, peer, &state))
		goto no_proto;

	if (!tty_view_init (&view, &proto, &state))
		goto no_view;

	for (;;) {
		tty_view_process (&view);

		pfd[0].fd = fd;
		pfd[0].events = POLLIN;

		pfd[1].fd = ConnectionNumber (view.d.d);
		pfd[1].events = POLLIN;

		if (poll (pfd, 2, -1) <= 0)
			continue;

		if ((pfd[0].revents | POLLIN) != 0)
			tty_proto_input (&proto);
	}

	return 1;
no_view:
	tty_proto_fini (&proto);
no_proto:
	tty_state_fini (&state);
no_state:
	tty_peer_free (peer);
	return 0;
}

int main (int argc, char *argv[])
{
	setlocale (LC_ALL, "");

	fcntl (0, F_SETFL, O_NONBLOCK);

	return tty_app_run (0) ? 0 : 1;
}
