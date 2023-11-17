
#include "sys16.h"

/* write n bytes from buffer to stdout */
void write(void __far *data, uint16_t size)
{
	struct sregs s;
	union regs r;

	/* ah: 0x40 (write to file or device) */
	r.h.ah = 0x40;

	/* bx: 0x1 (stdout) */
	r.w.bx = 0x1;

	/* cx: number of bytes to be written */
	r.w.cx = size;

	/* dx: offset of data */
	r.w.dx = FP_OFS(data);

	/* ds: segment of data */
	s.ds = FP_SEG(data);

	/* fire int 21h */
	int86x(0x21, &r, &r, &s);
}

/* write string to stdout */
void print(string s)
{
	write(s.data, s.len);
}
