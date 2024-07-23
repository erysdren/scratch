
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <dos.h>
#include <io.h>
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

#include "mouse.h"
#include "util.h"

/* enable mouse input */
void mouse_enable(void)
{
	union REGS r;

	r.w.ax = 0x00;
	int86(0x33, &r, &r);

	if (r.w.ax != 0xFFFF)
		die("Mouse driver not found");
}

/* show mouse cursor */
void mouse_show(void)
{
	union REGS r;

	r.w.ax = 0x01;
	int86(0x33, &r, &r);
}

/* hide mouse cursor */
void mouse_hide(void)
{
	union REGS r;

	r.w.ax = 0x02;
	int86(0x33, &r, &r);
}

/* read mouse position and returns button mask */
int16_t mouse_read(int16_t *x, int16_t *y)
{
	union REGS r;

	r.w.ax = 0x03;
	int86(0x33, &r, &r);

	if (x) *x = r.w.cx;
	if (y) *y = r.w.dx;

	return r.w.bx;
}
