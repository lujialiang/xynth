/***************************************************************************
    begin                : Sat Jul 2 2005
    copyright            : (C) 2005 - 2008 by Alper Akcan
    email                : alper.akcan@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "xynthpy.h"

extern PyTypeObject p_event_type;
extern PyTypeObject p_window_type;

PyMethodDef xynth_methods[] = {
	{"window", wrap_window, 1},
//	{"event", wrap_event, 1},
	{NULL, NULL}
};

void initxynth (void)
{
	PyObject *m;

	if (PyType_Ready(&p_window_type) < 0) {
		return;
	}
	p_window_type.ob_type = &PyType_Type;
	m = Py_InitModule3("xynth", xynth_methods, "Xynth Windowing System");
	
	PyModule_AddIntConstant(m, "WINDOW_TYPE_NOFORM", WINDOW_TYPE_NOFORM);
	PyModule_AddIntConstant(m, "WINDOW_TYPE_MAIN", WINDOW_TYPE_MAIN);
	PyModule_AddIntConstant(m, "WINDOW_TYPE_TEMP", WINDOW_TYPE_TEMP);
	PyModule_AddIntConstant(m, "WINDOW_TYPE_CHILD", WINDOW_TYPE_CHILD);
	PyModule_AddIntConstant(m, "WINDOW_TYPE_DESKTOP", WINDOW_TYPE_DESKTOP);
	PyModule_AddIntConstant(m, "WINDOW_TYPE_INPUT", WINDOW_TYPE_INPUT);
	PyModule_AddIntConstant(m, "WINDOW_TYPES", WINDOW_TYPES);

	PyModule_AddIntConstant(m, "CURSOR_TYPE_WAIT", CURSOR_TYPE_WAIT);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_CROSS", CURSOR_TYPE_CROSS);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_IBEAM", CURSOR_TYPE_IBEAM);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_SIZEV", CURSOR_TYPE_SIZEV);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_SIZEH", CURSOR_TYPE_SIZEH);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_SIZES", CURSOR_TYPE_SIZES);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_SIZEB", CURSOR_TYPE_SIZEB);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_SIZEA", CURSOR_TYPE_SIZEA);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_ARROW", CURSOR_TYPE_ARROW);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_POINT", CURSOR_TYPE_POINT);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_SPLITV", CURSOR_TYPE_SPLITV);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_SPLITH", CURSOR_TYPE_SPLITH);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_FORBID", CURSOR_TYPE_FORBID);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_UPARROW", CURSOR_TYPE_UPARROW);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_NONE", CURSOR_TYPE_NONE);
	PyModule_AddIntConstant(m, "CURSOR_TYPE_MAX", CURSOR_TYPE_MAX);

	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_NUMLOCK", KEYBOARD_FLAG_NUMLOCK);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_CAPSLOCK", KEYBOARD_FLAG_CAPSLOCK);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_LEFTCTRL", KEYBOARD_FLAG_LEFTCTRL);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_RIGHTCTRL", KEYBOARD_FLAG_RIGHTCTRL);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_LEFTSHIFT", KEYBOARD_FLAG_LEFTSHIFT);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_RIGHTSHIFT", KEYBOARD_FLAG_RIGHTSHIFT);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_LEFTALT", KEYBOARD_FLAG_LEFTALT);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_RIGHTALT", KEYBOARD_FLAG_RIGHTALT);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_SHIFT", KEYBOARD_FLAG_SHIFT);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_CTRL", KEYBOARD_FLAG_CTRL);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_ALT", KEYBOARD_FLAG_ALT);
	PyModule_AddIntConstant(m, "KEYBOARD_FLAG_ALTGR", KEYBOARD_FLAG_ALTGR);

	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ESCAPE", KEYBOARD_BUTTON_ESCAPE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ONE", KEYBOARD_BUTTON_ONE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_TWO", KEYBOARD_BUTTON_TWO);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_THREE", KEYBOARD_BUTTON_THREE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_FOUR", KEYBOARD_BUTTON_FOUR);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_FIVE", KEYBOARD_BUTTON_FIVE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SIX", KEYBOARD_BUTTON_SIX);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SEVEN", KEYBOARD_BUTTON_SEVEN);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_EIGHT", KEYBOARD_BUTTON_EIGHT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_NINE", KEYBOARD_BUTTON_NINE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ZERO", KEYBOARD_BUTTON_ZERO);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_MINUS", KEYBOARD_BUTTON_MINUS);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_EQUAL", KEYBOARD_BUTTON_EQUAL);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_DELETE", KEYBOARD_BUTTON_DELETE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_TAB", KEYBOARD_BUTTON_TAB);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_q", KEYBOARD_BUTTON_q);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_w", KEYBOARD_BUTTON_w);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_e", KEYBOARD_BUTTON_e);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_r", KEYBOARD_BUTTON_r);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_t", KEYBOARD_BUTTON_t);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_y", KEYBOARD_BUTTON_y);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_u", KEYBOARD_BUTTON_u);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_i", KEYBOARD_BUTTON_i);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_o", KEYBOARD_BUTTON_o);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_p", KEYBOARD_BUTTON_p);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_BRACKETLEFT", KEYBOARD_BUTTON_BRACKETLEFT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_BRACKETRIGHT", KEYBOARD_BUTTON_BRACKETRIGHT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_RETURN", KEYBOARD_BUTTON_RETURN);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_LEFTCONTROL", KEYBOARD_BUTTON_LEFTCONTROL);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_a", KEYBOARD_BUTTON_a);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_s", KEYBOARD_BUTTON_s);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_d", KEYBOARD_BUTTON_d);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_f", KEYBOARD_BUTTON_f);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_g", KEYBOARD_BUTTON_g);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_h", KEYBOARD_BUTTON_h);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_j", KEYBOARD_BUTTON_j);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_k", KEYBOARD_BUTTON_k);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_l", KEYBOARD_BUTTON_l);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SEMICOLON", KEYBOARD_BUTTON_SEMICOLON);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_APOSTROPHE", KEYBOARD_BUTTON_APOSTROPHE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_GRAVE", KEYBOARD_BUTTON_GRAVE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_LEFTSHIFT", KEYBOARD_BUTTON_LEFTSHIFT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_BACKSLASH", KEYBOARD_BUTTON_BACKSLASH);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_z", KEYBOARD_BUTTON_z);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_x", KEYBOARD_BUTTON_x);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_c", KEYBOARD_BUTTON_c);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_v", KEYBOARD_BUTTON_v);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_b", KEYBOARD_BUTTON_b);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_n", KEYBOARD_BUTTON_n);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_m", KEYBOARD_BUTTON_m);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_COMMA", KEYBOARD_BUTTON_COMMA);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PERIOD", KEYBOARD_BUTTON_PERIOD);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SLASH", KEYBOARD_BUTTON_SLASH);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_RIGHTSHIFT", KEYBOARD_BUTTON_RIGHTSHIFT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_MULTIPLY", KEYBOARD_BUTTON_KP_MULTIPLY);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ALT", KEYBOARD_BUTTON_ALT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SPACE", KEYBOARD_BUTTON_SPACE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_CAPS_LOCK", KEYBOARD_BUTTON_CAPS_LOCK);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F1", KEYBOARD_BUTTON_F1);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F2", KEYBOARD_BUTTON_F2);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F3", KEYBOARD_BUTTON_F3);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F4", KEYBOARD_BUTTON_F4);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F5", KEYBOARD_BUTTON_F5);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F6", KEYBOARD_BUTTON_F6);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F7", KEYBOARD_BUTTON_F7);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F8", KEYBOARD_BUTTON_F8);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F9", KEYBOARD_BUTTON_F9);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F10", KEYBOARD_BUTTON_F10);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_NUM_LOCK", KEYBOARD_BUTTON_NUM_LOCK);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SCROLL_LOCK", KEYBOARD_BUTTON_SCROLL_LOCK);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_7", KEYBOARD_BUTTON_KP_7);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_8", KEYBOARD_BUTTON_KP_8);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_9", KEYBOARD_BUTTON_KP_9);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_SUBTRACT", KEYBOARD_BUTTON_KP_SUBTRACT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_4", KEYBOARD_BUTTON_KP_4);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_5", KEYBOARD_BUTTON_KP_5);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_6", KEYBOARD_BUTTON_KP_6);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_ADD", KEYBOARD_BUTTON_KP_ADD);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_1", KEYBOARD_BUTTON_KP_1);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_2", KEYBOARD_BUTTON_KP_2);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_3", KEYBOARD_BUTTON_KP_3);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_0", KEYBOARD_BUTTON_KP_0);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_PERIOD", KEYBOARD_BUTTON_KP_PERIOD);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_LAST_CONSOLE", KEYBOARD_BUTTON_LAST_CONSOLE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_LESS", KEYBOARD_BUTTON_LESS);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F11", KEYBOARD_BUTTON_F11);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F12", KEYBOARD_BUTTON_F12);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_ENTER", KEYBOARD_BUTTON_KP_ENTER);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_RIGHTCONTROL", KEYBOARD_BUTTON_RIGHTCONTROL);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_KP_DIVIDE", KEYBOARD_BUTTON_KP_DIVIDE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_VOIDSYMBOL", KEYBOARD_BUTTON_VOIDSYMBOL);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ALTGR", KEYBOARD_BUTTON_ALTGR);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_BREAK", KEYBOARD_BUTTON_BREAK);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HOME", KEYBOARD_BUTTON_HOME);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_UP", KEYBOARD_BUTTON_UP);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PAGEUP", KEYBOARD_BUTTON_PAGEUP);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_LEFT", KEYBOARD_BUTTON_LEFT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_RIGHT", KEYBOARD_BUTTON_RIGHT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_END", KEYBOARD_BUTTON_END);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_DOWN", KEYBOARD_BUTTON_DOWN);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PAGEDOWN", KEYBOARD_BUTTON_PAGEDOWN);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_INSERT", KEYBOARD_BUTTON_INSERT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_REMOVE", KEYBOARD_BUTTON_REMOVE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PAUSE", KEYBOARD_BUTTON_PAUSE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_EXCLAM", KEYBOARD_BUTTON_EXCLAM);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_AT", KEYBOARD_BUTTON_AT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_NUMBERSIGN", KEYBOARD_BUTTON_NUMBERSIGN);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_DOLLAR", KEYBOARD_BUTTON_DOLLAR);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PERCENT", KEYBOARD_BUTTON_PERCENT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ASCIICIRCUM", KEYBOARD_BUTTON_ASCIICIRCUM);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_AMPERSAND", KEYBOARD_BUTTON_AMPERSAND);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ASTERISK", KEYBOARD_BUTTON_ASTERISK);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PARENLEFT", KEYBOARD_BUTTON_PARENLEFT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PARENRIGHT", KEYBOARD_BUTTON_PARENRIGHT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_UNDERSCORE", KEYBOARD_BUTTON_UNDERSCORE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_PLUS", KEYBOARD_BUTTON_PLUS);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_Q", KEYBOARD_BUTTON_Q);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_W", KEYBOARD_BUTTON_W);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_E", KEYBOARD_BUTTON_E);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_R", KEYBOARD_BUTTON_R);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_T", KEYBOARD_BUTTON_T);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_Y", KEYBOARD_BUTTON_Y);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_U", KEYBOARD_BUTTON_U);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_I", KEYBOARD_BUTTON_I);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_O", KEYBOARD_BUTTON_O);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_P", KEYBOARD_BUTTON_P);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_BRACELEFT", KEYBOARD_BUTTON_BRACELEFT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_BRACERIGHT", KEYBOARD_BUTTON_BRACERIGHT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_A", KEYBOARD_BUTTON_A);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_S", KEYBOARD_BUTTON_S);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_D", KEYBOARD_BUTTON_D);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F", KEYBOARD_BUTTON_F);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_G", KEYBOARD_BUTTON_G);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_H", KEYBOARD_BUTTON_H);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_J", KEYBOARD_BUTTON_J);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_K", KEYBOARD_BUTTON_K);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_L", KEYBOARD_BUTTON_L);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_COLON", KEYBOARD_BUTTON_COLON);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_QUOTEDBL", KEYBOARD_BUTTON_QUOTEDBL);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_ASCIITILDE", KEYBOARD_BUTTON_ASCIITILDE);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_BAR", KEYBOARD_BUTTON_BAR);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_Z", KEYBOARD_BUTTON_Z);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_X", KEYBOARD_BUTTON_X);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_C", KEYBOARD_BUTTON_C);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_V", KEYBOARD_BUTTON_V);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_B", KEYBOARD_BUTTON_B);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_N", KEYBOARD_BUTTON_N);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_M", KEYBOARD_BUTTON_M);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_GREATER", KEYBOARD_BUTTON_GREATER);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_QUESTION", KEYBOARD_BUTTON_QUESTION);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F13", KEYBOARD_BUTTON_F13);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F14", KEYBOARD_BUTTON_F14);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F15", KEYBOARD_BUTTON_F15);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F16", KEYBOARD_BUTTON_F16);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F17", KEYBOARD_BUTTON_F17);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F18", KEYBOARD_BUTTON_F18);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F19", KEYBOARD_BUTTON_F19);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F20", KEYBOARD_BUTTON_F20);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F21", KEYBOARD_BUTTON_F21);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F22", KEYBOARD_BUTTON_F22);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SHOW_MEMORY", KEYBOARD_BUTTON_SHOW_MEMORY);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F23", KEYBOARD_BUTTON_F23);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_F24", KEYBOARD_BUTTON_F24);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SCROLL_BACKWARD", KEYBOARD_BUTTON_SCROLL_BACKWARD);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SCROLL_FORWARD", KEYBOARD_BUTTON_SCROLL_FORWARD);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_CURRENCY", KEYBOARD_BUTTON_CURRENCY);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_CENT", KEYBOARD_BUTTON_CENT);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_C", KEYBOARD_BUTTON_HEX_C);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_A", KEYBOARD_BUTTON_HEX_A);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_SHOW_REGISTERS", KEYBOARD_BUTTON_SHOW_REGISTERS);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_7", KEYBOARD_BUTTON_HEX_7);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_8", KEYBOARD_BUTTON_HEX_8);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_9", KEYBOARD_BUTTON_HEX_9);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_D", KEYBOARD_BUTTON_HEX_D);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_4", KEYBOARD_BUTTON_HEX_4);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_5", KEYBOARD_BUTTON_HEX_5);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_6", KEYBOARD_BUTTON_HEX_6);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_E", KEYBOARD_BUTTON_HEX_E);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_1", KEYBOARD_BUTTON_HEX_1);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_2", KEYBOARD_BUTTON_HEX_2);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_3", KEYBOARD_BUTTON_HEX_3);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_0", KEYBOARD_BUTTON_HEX_0);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_F", KEYBOARD_BUTTON_HEX_F);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_HEX_B", KEYBOARD_BUTTON_HEX_B);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER0", KEYBOARD_BUTTON_USER0);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER1", KEYBOARD_BUTTON_USER1);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER2", KEYBOARD_BUTTON_USER2);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER3", KEYBOARD_BUTTON_USER3);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER4", KEYBOARD_BUTTON_USER4);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER5", KEYBOARD_BUTTON_USER5);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER6", KEYBOARD_BUTTON_USER6);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER7", KEYBOARD_BUTTON_USER7);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER8", KEYBOARD_BUTTON_USER8);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER9", KEYBOARD_BUTTON_USER9);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER10", KEYBOARD_BUTTON_USER10);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER11", KEYBOARD_BUTTON_USER11);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER12", KEYBOARD_BUTTON_USER12);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER13", KEYBOARD_BUTTON_USER13);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER14", KEYBOARD_BUTTON_USER14);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER15", KEYBOARD_BUTTON_USER15);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER16", KEYBOARD_BUTTON_USER16);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER17", KEYBOARD_BUTTON_USER17);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER18", KEYBOARD_BUTTON_USER18);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER19", KEYBOARD_BUTTON_USER19);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER20", KEYBOARD_BUTTON_USER20);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER21", KEYBOARD_BUTTON_USER21);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER22", KEYBOARD_BUTTON_USER22);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER23", KEYBOARD_BUTTON_USER23);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER24", KEYBOARD_BUTTON_USER24);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER25", KEYBOARD_BUTTON_USER25);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER26", KEYBOARD_BUTTON_USER26);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER27", KEYBOARD_BUTTON_USER27);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER28", KEYBOARD_BUTTON_USER28);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER29", KEYBOARD_BUTTON_USER29);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER30", KEYBOARD_BUTTON_USER30);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER31", KEYBOARD_BUTTON_USER31);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER32", KEYBOARD_BUTTON_USER32);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER33", KEYBOARD_BUTTON_USER33);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER34", KEYBOARD_BUTTON_USER34);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER35", KEYBOARD_BUTTON_USER35);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER36", KEYBOARD_BUTTON_USER36);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER37", KEYBOARD_BUTTON_USER37);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER38", KEYBOARD_BUTTON_USER38);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER39", KEYBOARD_BUTTON_USER39);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_USER40", KEYBOARD_BUTTON_USER40);
	PyModule_AddIntConstant(m, "KEYBOARD_BUTTON_NOCODE", KEYBOARD_BUTTON_NOCODE);

	PyModule_AddIntConstant(m, "MOUSE_BUTTON_RIGHT", MOUSE_BUTTON_RIGHT);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_MIDDLE", MOUSE_BUTTON_MIDDLE);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_LEFT", MOUSE_BUTTON_LEFT);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_FOURTH", MOUSE_BUTTON_FOURTH);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_FIFTH", MOUSE_BUTTON_FIFTH);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_SIXTH", MOUSE_BUTTON_SIXTH);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_RESET", MOUSE_BUTTON_RESET);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_WHEELX_UP", MOUSE_BUTTON_WHEELX_UP);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_WHEELX_DOWN", MOUSE_BUTTON_WHEELX_DOWN);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_WHEELY_UP", MOUSE_BUTTON_WHEELY_UP);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_WHEELY_DOWN", MOUSE_BUTTON_WHEELY_DOWN);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER0", MOUSE_BUTTON_USER0);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER1", MOUSE_BUTTON_USER1);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER2", MOUSE_BUTTON_USER2);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER3", MOUSE_BUTTON_USER3);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER4", MOUSE_BUTTON_USER4);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER5", MOUSE_BUTTON_USER5);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER6", MOUSE_BUTTON_USER6);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER7", MOUSE_BUTTON_USER7);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER8", MOUSE_BUTTON_USER8);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER9", MOUSE_BUTTON_USER9);
	PyModule_AddIntConstant(m, "MOUSE_BUTTON_USER10", MOUSE_BUTTON_USER10);

	PyModule_AddIntConstant(m, "EVENT_TYPE_UNKNOWN", EVENT_TYPE_UNKNOWN);
	PyModule_AddIntConstant(m, "EVENT_TYPE_QUIT", EVENT_TYPE_QUIT);
	PyModule_AddIntConstant(m, "EVENT_TYPE_KEYBOARD", EVENT_TYPE_KEYBOARD);
	PyModule_AddIntConstant(m, "EVENT_TYPE_KEYBOARD_RELEASED", EVENT_TYPE_KEYBOARD_RELEASED);
	PyModule_AddIntConstant(m, "EVENT_TYPE_KEYBOARD_PRESSED", EVENT_TYPE_KEYBOARD_PRESSED);
	PyModule_AddIntConstant(m, "EVENT_TYPE_KEYBOARD_EXTENSION_IRR", EVENT_TYPE_KEYBOARD_EXTENSION_IRR);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE", EVENT_TYPE_MOUSE);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_OVER", EVENT_TYPE_MOUSE_OVER);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_RELEASED", EVENT_TYPE_MOUSE_RELEASED);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_PRESSED", EVENT_TYPE_MOUSE_PRESSED);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_CLICKED", EVENT_TYPE_MOUSE_CLICKED);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_ENTER", EVENT_TYPE_MOUSE_ENTER);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_EXIT", EVENT_TYPE_MOUSE_EXIT);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_HINT1", EVENT_TYPE_MOUSE_HINT1);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_HINT2", EVENT_TYPE_MOUSE_HINT2);
	PyModule_AddIntConstant(m, "EVENT_TYPE_EXPOSE", EVENT_TYPE_EXPOSE);
	PyModule_AddIntConstant(m, "EVENT_TYPE_CONFIG", EVENT_TYPE_CONFIG);
	PyModule_AddIntConstant(m, "EVENT_TYPE_CONFIG_X", EVENT_TYPE_CONFIG_X);
	PyModule_AddIntConstant(m, "EVENT_TYPE_CONFIG_Y", EVENT_TYPE_CONFIG_Y);
	PyModule_AddIntConstant(m, "EVENT_TYPE_CONFIG_W", EVENT_TYPE_CONFIG_W);
	PyModule_AddIntConstant(m, "EVENT_TYPE_CONFIG_H", EVENT_TYPE_CONFIG_H);
	PyModule_AddIntConstant(m, "EVENT_TYPE_FOCUS", EVENT_TYPE_FOCUS);
	PyModule_AddIntConstant(m, "EVENT_TYPE_FOCUS_IN", EVENT_TYPE_FOCUS_IN);
	PyModule_AddIntConstant(m, "EVENT_TYPE_FOCUS_OUT", EVENT_TYPE_FOCUS_OUT);
	PyModule_AddIntConstant(m, "EVENT_TYPE_DESKTOP", EVENT_TYPE_DESKTOP);
	PyModule_AddIntConstant(m, "EVENT_TYPE_TIMER", EVENT_TYPE_TIMER);
	PyModule_AddIntConstant(m, "EVENT_TYPE_REMOTE", EVENT_TYPE_REMOTE);
	PyModule_AddIntConstant(m, "EVENT_TYPE_SIGNAL", EVENT_TYPE_SIGNAL);
	PyModule_AddIntConstant(m, "EVENT_TYPE_KEYBOARD_MASK", EVENT_TYPE_KEYBOARD_MASK);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MOUSE_MASK", EVENT_TYPE_MOUSE_MASK);
	PyModule_AddIntConstant(m, "EVENT_TYPE_MASK", EVENT_TYPE_MASK);

	Py_INCREF(&p_window_type);
	PyModule_AddObject(m, "window", (PyObject *) ((void *) (&p_window_type)));
//	PyModule_AddObject(m, "event", (PyObject *) ((void *) (&p_event_type)));
}
