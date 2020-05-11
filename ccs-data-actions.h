/*
 * Coded Character Set State Actions
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_DATA_ACTIONS_H
#define CCS_DATA_ACTIONS_H  1

#include "ccs-data.h"

/* 8.2.4 Format effectors */

int ccs_data_ind  (struct ccs_data *o);
int ccs_data_ri   (struct ccs_data *o);

int ccs_data_bs   (struct ccs_data *o);
int ccs_data_ht   (struct ccs_data *o);
int ccs_data_cr   (struct ccs_data *o);

#define ccs_data_lf(o)   ccs_data_ind (o)
#define ccs_data_vt(o)   ccs_data_ind (o)
#define ccs_data_ff(o)   ccs_data_ind (o)
#define ccs_data_nel(o)  ccs_data_ind (o)

#define ccs_data_hpa(o, x)      ccs_data_cha ((o), (x))
#define ccs_data_hpr(o, count)  ccs_data_cuf ((o), (count))
#define ccs_data_hpb(o, count)  ccs_data_cub ((o), (count))

int ccs_data_vpa  (struct ccs_data *o, int y);

#define ccs_data_vpr(o, count)  ccs_data_cud ((o), (count))
#define ccs_data_vpb(o, count)  ccs_data_cuu ((o), (count))

/* 8.2.7 Cursor control functions */

int ccs_data_cud  (struct ccs_data *o, int count);
int ccs_data_cuu  (struct ccs_data *o, int count);
int ccs_data_cuf  (struct ccs_data *o, int count);
int ccs_data_cub  (struct ccs_data *o, int count);

int ccs_data_cbt  (struct ccs_data *o, int count);
int ccs_data_cht  (struct ccs_data *o, int count);
int ccs_data_cvt  (struct ccs_data *o, int count);

int ccs_data_cnl  (struct ccs_data *o, int count);
int ccs_data_cpl  (struct ccs_data *o, int count);

int ccs_data_cha  (struct ccs_data *o, int x);
int ccs_data_cup  (struct ccs_data *o, int y, int x);

#endif  /* CCS_DATA_ACTIONS_H */
