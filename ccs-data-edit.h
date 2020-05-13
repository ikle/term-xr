/*
 * Coded Character Set Data Editor helpers
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_DATA_EDIT_H
#define CCS_DATA_EDIT_H  1

#include "ccs-data.h"

/* Erasing helpers */

int ccs_data_clear_left  (struct ccs_data *o, unsigned y, unsigned x);
int ccs_data_clear_right (struct ccs_data *o, unsigned y, unsigned x);
int ccs_data_clear_line  (struct ccs_data *o, unsigned y);

int ccs_data_clear_up    (struct ccs_data *o, unsigned y);
int ccs_data_clear_down  (struct ccs_data *o, unsigned y);
int ccs_data_clear_all   (struct ccs_data *o);

/* 8.2.6 Editor functions */

int ccs_data_dch  (struct ccs_data *o, int count);
int ccs_data_dl   (struct ccs_data *o, int count);

int ccs_data_ich  (struct ccs_data *o, int count);
int ccs_data_il   (struct ccs_data *o, int count);

int ccs_data_ech  (struct ccs_data *o, int count);
int ccs_data_el   (struct ccs_data *o, int mode);
int ccs_data_ed   (struct ccs_data *o, int mode);

/* 8.2.8 Display control functions */

int ccs_data_su   (struct ccs_data *o, int count);
int ccs_data_sd   (struct ccs_data *o, int count);

#endif  /* CCS_DATA_EDIT_H */
