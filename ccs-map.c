/*
 * Coded Character Set Mapping
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ccs-map.h"

#define ARRAY_SIZE(a)  (sizeof (a) / sizeof ((a)[0]))

void ccs_map_init (struct ccs_map *o)
{
	size_t i;

	o->gl = 0;
	o->gr = 1;

	for (i = 0; i < ARRAY_SIZE (o->g); ++i)
		o->g[i] = NULL;
}

void ccs_map_fini (struct ccs_map *o)
{
	/* do nothing */
}

static wchar_t map (struct ccs_charset *o, int shift, int i)
{
	if (o == NULL)
		return 0;
	
	if ((i -= shift + o->shift) < 0 || i >= o->count)
		return 0;

	return o->map[i];
}

wchar_t ccs_map_char (struct ccs_map *o, wchar_t in)
{
	wchar_t out;

	if ((out = map (o->g[o->gl], 0x00, in)) != 0 ||
	    (out = map (o->g[o->gr], 0x80, in)) != 0)
		return out;

	return in;
}

/* NOTE: i MUST be in range from 0 to 3 */
wchar_t ccs_map_shifted (struct ccs_map *o, wchar_t c, unsigned i)
{
	unsigned gl = o->gl;
	wchar_t ret;

	o->gl = i;
	ret = ccs_map_char (o, c);
	o->gl = gl;

	return ret;
}
