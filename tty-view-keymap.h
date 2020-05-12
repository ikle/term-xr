/*
 * Terminal Emulator X11 PC Keyboard Mapping
 *
 * Copyright (c) 2004-2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TTY_VIEW_KEYMAP_H
#define TTY_VIEW_KEYMAP_H  1

#include <X11/keysym.h>

#include "tty-keys.h"

#define X(x11, tty)	case XK_##x11:  return TTY_##tty;

static int tty_view_x11_to_tty (unsigned long symbol)
{
	switch (symbol) {
		/* Main Array */

		X (Break,	BREAK)
		X (Tab,		TAB)
		X (Return,	RETURN)
		X (Pause,	PAUSE)
		X (Escape,	ESCAPE)
		X (BackSpace,	DELETE)

		/* Editing Keys */

		X (Find,	FIND)
		X (Insert,	INSERT)
		X (Delete,	REMOVE)
		X (Select,	SELECT)
		X (Prior,	PREV)
		X (Next,	NEXT)

		X (Home,	FIND)
		X (End,		SELECT)

		X (KP_Insert,	INSERT)
		X (KP_Delete,	REMOVE)
		X (KP_Prior,	PREV)
		X (KP_Next,	NEXT)

		X (KP_Home,	FIND)
		X (KP_End,	SELECT)

		/* Cursor Keys */

		X (Up,		UP)
		X (Down,	DOWN)
		X (Right,	RIGHT)
		X (Left,	LEFT)

		X (KP_Up,	UP)
		X (KP_Down,	DOWN)
		X (KP_Right,	RIGHT)
		X (KP_Left,	LEFT)

		/* Auxiliary Keypad Keys */

		X (KP_F1,	KP_F1)
		X (KP_F2,	KP_F2)
		X (KP_F3,	KP_F3)
		X (KP_F4,	KP_F4)

		X (KP_Enter,	KP_ENTER)

		X (KP_Multiply,		KP_STAR)
		X (KP_Add,		KP_PLUS)
		X (KP_Separator,	KP_COMMA)
		X (KP_Subtract,		KP_MINUS)
		X (KP_Decimal,		KP_PERIOD)
		X (KP_Divide,		KP_SLASH)

		X (KP_0,	KP_0)
		X (KP_1,	KP_1)
		X (KP_2,	KP_2)
		X (KP_3,	KP_3)
		X (KP_4,	KP_4)
		X (KP_5,	KP_5)
		X (KP_6,	KP_6)
		X (KP_7,	KP_7)
		X (KP_8,	KP_8)
		X (KP_9,	KP_9)

		/* Functional Keys */

		X (F1,		KP_F1)
		X (F2,		KP_F2)
		X (F3,		KP_F3)
		X (F4,		KP_F4)
		X (F5,		F5)
		X (F6,		F6)
		X (F7,		F7)
		X (F8,		F8)
		X (F9,		F9)
		X (F10,		F10)

		X (F11,		F11)
		X (F12,		F12)
		X (F13,		F13)
		X (F14,		F14)
		X (F15,		F15)
		X (F16,		F16)
		X (F17,		F17)
		X (F18,		F18)
		X (F19,		F19)
		X (F20,		F20)
	}

	return 0;
}

#undef X

#endif  /* TTY_VIEW_KEYMAP_H */
