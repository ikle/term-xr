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

#endif  /* CCS_DATA_EDIT_H */
