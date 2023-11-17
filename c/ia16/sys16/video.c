
#include "sys16.h"

/* video and text mode memory pointers */
uint16_t __far *text_memory = (uint16_t __far *)0xB8000000UL;
uint8_t __far *cga_memory_even = (uint8_t __far *)0xB8000000UL;
uint8_t __far *cga_memory_odd = (uint8_t __far *)0xBA000000UL;
uint8_t __far *vga_memory = (uint8_t __far *)0xA0000000UL;

/* set video mode */
uint8_t video_set_mode(uint8_t mode)
{
	union regs r;

	/* ah = 0x00 (set video mode) */
	r.h.ah = 0x00;

	/* al = mode to set */
	r.h.al = mode;

	/* do int 10h */
	int86(0x10, &r, &r);

	/* return the mode so the programmer can check if its the one they wanted */
	return video_get_mode();
}

/* get video mode */
uint8_t video_get_mode(void)
{
	union regs r;

	/* ah = 0x0f (get video mode) */
	r.h.ah = 0x0f;

	/* do int 10h */
	int86(0x10, &r, &r);

	/* returned mode is stored in al */
	return r.h.al;
}
