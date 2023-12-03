/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "dos.h"
#include "main.h"
#include "keyboard.h"

#define BUFSZ 64
#define ADVANCE(x) ((x) = ((x) + 1) & (BUFSZ - 1))
static int buffer[BUFSZ];
static int buf_ridx, buf_widx;

static int scan_to_ascii[128] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static int shifted_to_ascii[128] = {
	0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
	0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
	0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void kbhandler(void)
{
	/* get key */
	char key = (char)inp(0x60);

	/* add to keys buffer */
	if (!(key & 0x80))
	{
		buffer[buf_widx] = key & 0x7F;

		ADVANCE(buf_widx);

		if (buf_widx == buf_ridx)
			ADVANCE(buf_ridx);
	}

	/* add to key table */
	engine.keys[engine.key_last = key & 0x7F] = !(key & 0x80);
	outp(0x20, 0x20);
}

void kb_init(void)
{
	/* clear keyboard queue */
	kb_clearqueue();

	/* setup keyboard handler */
	_go32_dpmi_get_protected_mode_interrupt_vector(9, &engine.kbhandler_old);
	engine.kbhandler_new.pm_offset = (int)kbhandler;
	engine.kbhandler_new.pm_selector = _go32_my_cs();
	_go32_dpmi_allocate_iret_wrapper(&engine.kbhandler_new);
	_go32_dpmi_set_protected_mode_interrupt_vector(9, &engine.kbhandler_new);
}

void kb_quit(void)
{
	/* clear keyboard queue */
	kb_clearqueue();

	/* restore old keyboard handler */
	_go32_dpmi_set_protected_mode_interrupt_vector(9, &engine.kbhandler_old);
	_go32_dpmi_free_iret_wrapper(&engine.kbhandler_new);
}

int kb_getkey(void)
{
	int res;

	if (buf_ridx == buf_widx)
		return -1;

	res = buffer[buf_ridx];
	ADVANCE(buf_ridx);

	return res;
}

int kb_toascii(int sc)
{
	/* return shifted ascii */
	if (engine.keys[SC_LSHIFT] || engine.keys[SC_RSHIFT])
		return shifted_to_ascii[sc & 0x7F];

	/* return normal ascii */
	return scan_to_ascii[sc & 0x7F];
}

void kb_clearqueue(void)
{
	buf_ridx = buf_widx = 0;
}
