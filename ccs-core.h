/*
 * Coded Character Set Core
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_CORE_H
#define CCS_CORE_H  1

#include <wchar.h>

#include "ccs-names.h"
#include "ccs-map.h"

#define CCS_C1_CODE(f)	(0x80 | ((f) & 0x1f))

#define CCS_FS_CODE(f)	(0xe000 | ((f) & 0x1f))

#define CCS_FP_CODE(f)	(0xe020 | ((f) & 0x0f))

#define CCS_NF_CODE1(i, f)	\
	(0xe000  | ((i & 15) << 8)  | ((c) & 255))

#define CCS_NF_CODE2(i, j, f) 	\
	(0xf0000 | ((i & 15) << 12) | ((j & 15) << 8) | ((c) & 255))

#define CCS_C0_ESC	CCS_ESC
#define CCS_C0_LS0	CCS_LS0
#define CCS_C0_LS1	CCS_LS1

#define CCS_C1_SS2	CCS_SS2
#define CCS_C1_SS3	CCS_SS3

#define CCS_FS_LS2	CCS_FS_CODE (CCS_LS2)
#define CCS_FS_LS3	CCS_FS_CODE (CCS_LS3)
#define CCS_FS_LS1R	CCS_FS_CODE (CCS_LS1R)
#define CCS_FS_LS2R	CCS_FS_CODE (CCS_LS2R)
#define CCS_FS_LS3R	CCS_FS_CODE (CCS_LS3R)

#define CCS_FP_DECPAM	CCS_FP_CODE (0x2d)
#define CCS_FP_DECPNM	CCS_FP_CODE (0x2e)

#define CCS_NF_CZD(f)	CCS_NF_CODE1 (0x21, (f))
#define CCS_NF_C1D(f)	CCS_NF_CODE1 (0x22, (f))

#define CCS_GD4_BASE1	CCS_NF_CODE1 (0x28, 0)
#define CCS_GD4_MASK1	0x3ff

#define CCS_GD4_BASE2	CCS_NF_CODE2 (0x28, 0, 0)
#define CCS_GD4_MASK2	0x3fff

struct ccs_core {
	struct ccs_map map;
	unsigned char state, index, im[4];
};

void ccs_core_init (struct ccs_core *o);
void ccs_core_fini (struct ccs_core *o);

wchar_t ccs_core_filter (struct ccs_core *o, wchar_t c);

#endif  /* CCS_CORE_H */
