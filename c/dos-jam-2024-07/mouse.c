/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

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

#include "luna.h"

/* enable mouse input */
void mouse_enable(void)
{
	__dpmi_regs r;

	r.x.ax = 0x00;
	__dpmi_int(0x33, &r);

	if (r.x.ax != 0xFFFF)
		die("Mouse driver not found");
}

/* show mouse cursor */
void mouse_show(void)
{
	__dpmi_regs r;

	r.x.ax = 0x01;
	__dpmi_int(0x33, &r);
}

/* hide mouse cursor */
void mouse_hide(void)
{
	__dpmi_regs r;

	r.x.ax = 0x02;
	__dpmi_int(0x33, &r);
}

/* read mouse position and returns button mask */
int16_t mouse_read(int16_t *x, int16_t *y)
{
	__dpmi_regs r;

	r.x.ax = 0x03;
	__dpmi_int(0x33, &r);

	if (x) *x = r.x.cx;
	if (y) *y = r.x.dx;

	return r.x.bx;
}
