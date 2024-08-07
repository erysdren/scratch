
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
