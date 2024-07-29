
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

#include "mem.h"
#include "util.h"
#include "vid.h"

#include "font8x8.xbm"

static uint8_t vid_mode_old = 0x02;
static uint8_t vid_color_bg = 0x00;
static uint8_t vid_color_fg = 0x0F;

/* start video system */
void vid_init(void)
{
	__dpmi_regs r;

	/* save current video mode */
	vid_mode_old = vid_mode_get();

	/* disable memory protection */
	if (__djgpp_nearptr_enable() == 0)
		die("Failed to enable near pointers");

	/* set mode to 0x03 */
	r.x.ax = 0x0003;
	__dpmi_int(0x10, &r);

	/* change font to ada's 8x8 font */
	dosmemput(font8x8_bits, sizeof(font8x8_bits), __tb);
	r.x.ax = 0x1110;
	r.x.es = __tb >> 4;
	r.x.bp = __tb & 0x0f;
	r.x.cx = 256;
	r.x.dx = 0;
	r.h.bl = 0;
	r.h.bh = 8;
	__dpmi_int(0x10, &r);

	/* disable text blinking */
	inportb(0x03da);
	outportb(0x03c0, 0x30);
	outportb(0x03c0, inportb(0x03c1) & 0xF7);

	/* set text mode cursor to block shape */
	r.h.ah = 0x01;
	r.x.cx = 0x0007;
	__dpmi_int(0x10, &r);
}

/* shutdown video system */
void vid_quit(void)
{
	/* enable memory protection */
	__djgpp_nearptr_disable();

	/* reset video mode */
	vid_mode_set(vid_mode_old);
}

/* get pointer to writeable video framebuffer */
uint8_t *vid_framebuffer_get(void)
{
	return (uint8_t *)0xB8000 + __djgpp_conventional_base;
}

/* clear video framebuffer */
void vid_framebuffer_clear(uint8_t bg, uint8_t fg)
{
	vid_color_bg = bg;
	vid_color_fg = fg;
	memset16(vid_framebuffer_get(), vid_cell(' ', vid_cell_color(bg, fg)), VID_WIDTH * VID_HEIGHT);
}

/* set video mode */
void vid_mode_set(uint8_t mode)
{
	union REGS r;
	r.h.ah = 0x00;
	r.h.al = mode;
	int86(0x10, &r, &r);
}

/* get current video mode */
uint8_t vid_mode_get(void)
{
	union REGS r;
	r.h.ah = 0x0f;
	int86(0x10, &r, &r);
	return r.h.al;
}

/* wait for vertical retrace */
void vid_vsync_wait(void)
{
	while (inp(0x3da) & 0x8);
	while (!(inp(0x3da) & 0x8));
}

/* set palette color */
void vid_palette_set_color(int i, uint8_t red, uint8_t grn, uint8_t blu)
{
	union REGS r;
	static const uint16_t color_registers[16] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
		0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
	};

	r.w.ax = 0x1010;
	r.w.bx = color_registers[i];
	r.h.dh = red;
	r.h.ch = grn;
	r.h.cl = blu;

	int86(0x10, &r, &r);
}

/* set palette of N colors */
void vid_palette_set(int num_colors, uint8_t *colors)
{
	for (int i = 0; i < num_colors; i++)
	{
		uint8_t r, g, b;

		r = colors[i * 3] * 63 / 255;
		g = colors[i * 3 + 1] * 63 / 255;
		b = colors[i * 3 + 2] * 63 / 255;

		vid_palette_set_color(i, r, g, b);
	}
}

/* create packed text cell color */
__attribute__((pure)) uint8_t vid_cell_color(uint8_t bg, uint8_t fg)
{
	return fg | bg << 4;
}

/* create packed text cell */
__attribute__((pure)) uint16_t vid_cell(unsigned char c, uint8_t color)
{
	return (uint16_t)c | (uint16_t)color << 8;
}

/* get current text attributes as a packed cell */
uint8_t vid_get_attributes(void)
{
	return vid_cell_color(vid_color_bg, vid_color_fg);
}

/* set current text attributes */
void vid_set_attributes(uint8_t bg, uint8_t fg)
{
	vid_color_bg = bg;
	vid_color_fg = fg;
}

/* put cell at x,y */
void vid_cell_put(int x, int y, uint16_t cell)
{
	uint16_t *ofs = (uint16_t *)(vid_framebuffer_get() + y * VID_PITCH + x * VID_BYTES_PER_PIXEL);
	*ofs = cell;
}

/* fill cells at x,y with width and height */
void vid_cell_fill(int x, int y, int w, int h, uint16_t cell)
{
	for (int yy = y; yy < y + h; yy++)
	{
		uint8_t *ofs = vid_framebuffer_get() + yy * VID_PITCH + x * VID_BYTES_PER_PIXEL;
		memset16(ofs, cell, w);
	}
}

/* set cursor position */
void vid_cursor_set_position(uint8_t x, uint8_t y)
{
	union REGS r;
	r.h.ah = 0x02;
	r.h.bh = 0x00;
	r.h.dh = y;
	r.h.dl = x;
	int86(0x10, &r, &r);
}
