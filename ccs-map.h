/*
 * Coded Character Set Mapping
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_MAP_H
#define CCS_MAP_H  1

#include <stddef.h>
#include <wchar.h>

struct ccs_charset {
	unsigned char shift, count;	/* first character index, count */
	wchar_t map[];
};

struct ccs_charset ccs_map_dec;
struct ccs_charset ccs_map_irv;
struct ccs_charset ccs_map_uk;

struct ccs_map {
	struct ccs_charset *g[4];	/* designated charsets	*/
	unsigned char gl, gr;		/* invoked charsets	*/
};

void ccs_map_init (struct ccs_map *o);
void ccs_map_fini (struct ccs_map *o);

wchar_t ccs_map_char (struct ccs_map *o, wchar_t c);

/* NOTE: i MUST be in range from 0 to 3 */
wchar_t ccs_map_shifted (struct ccs_map *o, wchar_t c, unsigned i);

#endif  /* CCS_MAP_H */
