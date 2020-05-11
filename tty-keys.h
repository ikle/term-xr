/*
 * Terminal Emulator Keys
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TTY_KEYS_H
#define TTY_KEYS_H  1

#define TTY_MODE_SHIFT		1
#define TTY_MODE_ALT		2
#define TTY_MODE_CONTROL	4

#define TTY_CLASS_MAIN    0	/* ASCII (i)				*/
#define TTY_CLASS_EDIT    1	/* CSI (i, ~)				*/
#define TTY_CLASS_CURSOR  2	/* app mode ? SS3 (i) : CSI (i) */
#define TTY_CLASS_AUX     3	/* j = app mode ? i | 0x40 : i		*/
				/* j | 0x40 ? SS3 (j) : ASCII (j)	*/

/* Main Array */

#define TTY_BREAK	0x0003
#define TTY_TAB		0x0009
#define TTY_RETURN	0x000d
#define TTY_PAUSE	0x0013	/* XOFF (DC3) */
#define TTY_ESCAPE	0x001b
#define TTY_SPACE	0x0020
#define TTY_DELETE	0x007f

/* Editing Keys */

#define TTY_FIND	0x0101	/* CSI (i, ~) */
#define TTY_INSERT	0x0102
#define TTY_REMOVE	0x0103
#define TTY_SELECT	0x0104
#define TTY_PREV	0x0105
#define TTY_NEXT	0x0106

/* Cursor Keys */

#define TTY_UP		0x0241
#define TTY_DOWN	0x0242
#define TTY_RIGHT	0x0243
#define TTY_LEFT	0x0244

/* Auxiliary Keypad Keys */

#define TTY_KP_F1	0x0350	/* SS3 (i) always */
#define TTY_KP_F2	0x0351
#define TTY_KP_F3	0x0352
#define TTY_KP_F4	0x0353

#define TTY_KP_ENTER	0x030d

#define TTY_KP_STAR	0x032a	/* in app mode SS3 (i | 0x40) */
#define TTY_KP_PLUS	0x032b  /* ASCII (i) otherwise */
#define TTY_KP_COMMA	0x032c
#define TTY_KP_MINUS	0x032d
#define TTY_KP_PERIOD	0x032e
#define TTY_KP_SLASH	0x032f

#define TTY_KP_0	0x0330
#define TTY_KP_1	0x0331
#define TTY_KP_2	0x0332
#define TTY_KP_3	0x0333
#define TTY_KP_4	0x0334
#define TTY_KP_5	0x0335
#define TTY_KP_6	0x0336
#define TTY_KP_7	0x0337
#define TTY_KP_8	0x0338
#define TTY_KP_9	0x0339

/* Functional Keys */

#define TTY_F1		0x010b
#define TTY_F2		0x010c
#define TTY_F3		0x010d
#define TTY_F4		0x010e
#define TTY_F5		0x010f
#define TTY_F6		0x0111
#define TTY_F7		0x0112
#define TTY_F8		0x0113
#define TTY_F9		0x0114
#define TTY_F10		0x0115
#define TTY_F11		0x0117
#define TTY_F12		0x0118
#define TTY_F13		0x0119
#define TTY_F14		0x011a
#define TTY_F15		0x011c
#define TTY_F16		0x011d
#define TTY_F17		0x011f
#define TTY_F18		0x0120
#define TTY_F19		0x0121
#define TTY_F20		0x0122

#endif  /* TTY_KEYS_H */
