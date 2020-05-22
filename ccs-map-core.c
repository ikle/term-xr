/*
 * Coded Character Set Core Mappings
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35, ECMA-48, ISO 2375
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ccs-map.h"

/* NOTE: assume wchar_t stores unicode character/codepoint */

struct ccs_charset ccs_map_dec = {
	0x5f, 32,

	{
		0xa0,

	        0x25c6, 0x2592, 0x2409, 0x240c,  0x240d, 0x240a,   0xb0,   0xb1,
	        0x2424, 0x240b, 0x2518, 0x2510,  0x250c, 0x2514, 0x253c, 0x23Ba,

	        0x23Bb, 0x2500, 0x23Bc, 0x23Bd,  0x251c, 0x2524, 0x2534, 0x252c,
	        0x2502, 0x2264, 0x2265, 0x03c0,  0x2260,   0xa3,   0xb7,
	}
};

/* ISO-IR 002, 04/00 - international reference version (IRV) of ISO 646 */

struct ccs_charset ccs_map_irv = {
	0x24, 1, { 0xa4 },
};

/* ISO-IR 004, 04/01 - Unated Kingdom 7-bit data code */

struct ccs_charset ccs_map_uk = {
	0x24, 1, { 0xa3 },
};
