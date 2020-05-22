/*
 * Coded Character Set Core
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ccs-core.h"

#define ARRAY_SIZE(a)  (sizeof (a) / sizeof ((a)[0]))

enum ccs_core_state {
	CCS_CORE_START = 0,
	CCS_CORE_ESCAPE,
	CCS_CORE_SS2,
	CCS_CORE_SS3,
};

void ccs_core_init (struct ccs_core *o)
{
	ccs_map_init (&o->map);
	o->state = CCS_CORE_START;
}

void ccs_core_fini (struct ccs_core *o)
{
	ccs_map_fini (&o->map);
}

static wchar_t ccs_core_escape (struct ccs_core *o, wchar_t c)
{
	if (c < 0x20 || c >= 0x7f) {
		o->state = CCS_CORE_START;
		return 0;
	}

	if (c < 0x30) {
		if (o->index < ARRAY_SIZE (o->im))
			o->im[o->index++] = c;

		return 0;
	}

	o->state = CCS_CORE_START;

	if (o->index > 0)
		switch (o->index) {
		case 1:   return CCS_NF_CODE1 (o->im[0], c);
		case 2:   return CCS_NF_CODE2 (o->im[0], o->im[1], c);
		default:  return 0;
		}

	if (c < 0x40)
		return CCS_FP_CODE (c);

	if (c < 0x60)
		return CCS_C1_CODE (c);

	return CCS_FS_CODE (c);
}

static wchar_t ccs_core_ss (struct ccs_core *o, unsigned i, wchar_t c)
{
	o->state = CCS_CORE_START;
	return ccs_map_shifted (&o->map, c, i);
}

/* Gx-designate 94-set */
static int ccs_core_gd4 (struct ccs_core *o, int c)
{
	if ((c & ~CCS_GD4_MASK1) == CCS_GD4_BASE1) {
		int i = (c >> 8) & 3;

		switch (c & 0xff) {
		case 0x30:	o->map.g[i] = &ccs_map_dec;	break;
		case 0x40:	o->map.g[i] = &ccs_map_irv;	break;
		case 0x41:	o->map.g[i] = &ccs_map_uk;	break;
		default:	o->map.g[i] = NULL;		break;
		}

		return 1;
	}

	if ((c & ~CCS_GD4_MASK2) == CCS_GD4_BASE2)
		return 1;

	return 0;
}

wchar_t ccs_core_filter (struct ccs_core *o, wchar_t c)
{
	switch (o->state) {
	case CCS_CORE_ESCAPE:
		c = ccs_core_escape (o, c);
		break;
	case CCS_CORE_SS2:	return ccs_core_ss (o, 2, c);
	case CCS_CORE_SS3:	return ccs_core_ss (o, 3, c);
	}

	switch (c) {
	case CCS_C0_ESC:
		o->state = CCS_CORE_ESCAPE;
		o->index = 0;
		return 0;

	case CCS_C0_LS0:	o->map.gl = 0; return 0;
	case CCS_C0_LS1:	o->map.gl = 1; return 0;
	case CCS_FS_LS2:	o->map.gl = 2; return 0;
	case CCS_FS_LS3:	o->map.gl = 3; return 0;

	case CCS_FS_LS1R:	o->map.gr = 1; return 0;
	case CCS_FS_LS2R:	o->map.gr = 2; return 0;
	case CCS_FS_LS3R:	o->map.gr = 3; return 0;

	case CCS_C1_SS2:	o->state = CCS_CORE_SS2; return 0;
	case CCS_C1_SS3:	o->state = CCS_CORE_SS3; return 0;
	}

	if (ccs_core_gd4 (o, c))
		return 0;

	return c < 0x100 ? ccs_map_char (&o->map, c) : c;
}
