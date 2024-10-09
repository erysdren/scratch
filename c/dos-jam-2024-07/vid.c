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
#include "ada8x8.xbm"

static uint8_t vid_mode_old = 0x02;
static rect_t stencil;
static point_t offset;
static uint8_t current_z = 0;
static uint8_t zbuffer[VID_HEIGHT][VID_WIDTH];

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
	dosmemput(ada8x8_bits, sizeof(ada8x8_bits), __tb);
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

	/* setup defaults */
	vid_stencil_set(0, 0, VID_WIDTH, VID_HEIGHT);
	vid_offset_set(0, 0);
	vid_zbuffer_clear(0);
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

/* set video mode */
void vid_mode_set(uint8_t mode)
{
	__dpmi_regs r;
	r.h.ah = 0x00;
	r.h.al = mode;
	__dpmi_int(0x10, &r);
}

/* get current video mode */
uint8_t vid_mode_get(void)
{
	__dpmi_regs r;
	r.h.ah = 0x0f;
	__dpmi_int(0x10, &r);
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
	__dpmi_regs r;
	static const uint16_t color_registers[16] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
		0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
	};

	r.x.ax = 0x1010;
	r.x.bx = color_registers[i];
	r.h.dh = red;
	r.h.ch = grn;
	r.h.cl = blu;

	__dpmi_int(0x10, &r);
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

/* put background color at x/y */
#define ADD_BG(cell, color) (((cell) & ~(0x0F << 12)) | (((color) & 0x0F) << 12))
void vid_put_bg(int x, int y, uint8_t c)
{
	uint16_t *ofs = (uint16_t *)(vid_framebuffer_get() + y * VID_PITCH + x * VID_BYTES_PER_PIXEL);
	*ofs = ADD_BG(*ofs, c);
}
#undef ADD_BG

/* put foreground color at x/y */
#define ADD_FG(cell, color) (((cell) & ~(0x0F << 8)) | (((color) & 0x0F) << 8))
void vid_put_fg(int x, int y, uint8_t c)
{
	uint16_t *ofs = (uint16_t *)(vid_framebuffer_get() + y * VID_PITCH + x * VID_BYTES_PER_PIXEL);
	*ofs = ADD_FG(*ofs, c);
}
#undef ADD_FG

/* put foreground character at x/y */
#define ADD_CODE(cell, code) (((cell) & ~(0xFF)) | (((code) & 0xFF)))
void vid_put_code(int x, int y, unsigned char c)
{
	uint16_t *ofs = (uint16_t *)(vid_framebuffer_get() + y * VID_PITCH + x * VID_BYTES_PER_PIXEL);
	*ofs = ADD_CODE(*ofs, c);
}
#undef ADD_CODE

/* fill background color rect at x/y */
void vid_fill_bg(int x, int y, int w, int h, uint8_t c)
{
	x = imax(x + offset.x, stencil.x);
	y = imax(y + offset.y, stencil.y);
	w = imin(x + w, stencil.x + stencil.w) - x;
	h = imin(y + h, stencil.y + stencil.h) - y;

	for (int yy = y; yy < y + h; yy++)
	{
		for (int xx = x; xx < x + w; xx++)
		{
			/* check z */
			if (zbuffer[yy][xx] <= current_z)
			{
				vid_put_bg(xx, yy, c);
				zbuffer[yy][xx] = current_z;
			}
		}
	}
}

/* fill foreground color rect at x/y */
void vid_fill_fg(int x, int y, int w, int h, uint8_t c)
{
	x = imax(x + offset.x, stencil.x);
	y = imax(y + offset.y, stencil.y);
	w = imin(x + w, stencil.x + stencil.w) - x;
	h = imin(y + h, stencil.y + stencil.h) - y;

	for (int yy = y; yy < y + h; yy++)
	{
		for (int xx = x; xx < x + w; xx++)
		{
			/* check z */
			if (zbuffer[yy][xx] <= current_z)
			{
				vid_put_fg(xx, yy, c);
				zbuffer[yy][xx] = current_z;
			}
		}
	}
}

/* fill foreground character rect at x/y */
void vid_fill_code(int x, int y, int w, int h, unsigned char c)
{
	x = imax(x + offset.x, stencil.x);
	y = imax(y + offset.y, stencil.y);
	w = imin(x + w, stencil.x + stencil.w) - x;
	h = imin(y + h, stencil.y + stencil.h) - y;

	for (int yy = y; yy < y + h; yy++)
	{
		for (int xx = x; xx < x + w; xx++)
		{
			/* check z */
			if (zbuffer[yy][xx] <= current_z)
			{
				vid_put_code(xx, yy, c);
				zbuffer[yy][xx] = current_z;
			}
		}
	}
}

/* draw string at x/y */
void vid_put_string(int x, int y, uint8_t c, const char *s)
{
	char *ptr = (char *)s;
	int sx = x;

	/* add offset */
	x += offset.x;
	y += offset.y;

	while (*ptr)
	{
		/* handle control characters */
		if (*ptr == '\n')
		{
			y += 1;
			goto next;
		}
		else if (*ptr == '\r')
		{
			x = sx;
			goto next;
		}
		else if (*ptr == '\t')
		{
			x += 4;
			goto next;
		}

		/* gone out of range */
		if (x >= stencil.x + stencil.w || y >= stencil.y + stencil.h)
			break;

		/* off screen, but could come into view */
		if (x >= stencil.x && y >= stencil.y)
		{
			/* check z */
			if (zbuffer[y][x] <= current_z)
			{
				vid_put_code(x, y, *ptr);
				vid_put_fg(x, y, c);
				zbuffer[y][x] = current_z;
			}
		}

		x += 1;

next:
		ptr++;
	}
}

/* set cursor position */
void vid_cursor_set_position(uint8_t x, uint8_t y)
{
	__dpmi_regs r;
	r.h.ah = 0x02;
	r.h.bh = 0x00;
	r.h.dh = y;
	r.h.dl = x;
	__dpmi_int(0x10, &r);
}

/* set stencil dimensions */
void vid_stencil_set(int x, int y, int w, int h)
{
	stencil.x = x;
	stencil.y = y;
	stencil.w = w;
	stencil.h = h;
}

/* set coordinate offset */
void vid_offset_set(int x, int y)
{
	offset.x = x;
	offset.y = y;
}

/* clear zbuffer */
void vid_zbuffer_clear(uint8_t v)
{
	memset8(zbuffer, v, sizeof(zbuffer));
}

/* fill zbuffer area */
void vid_zbuffer_fill(int x, int y, int w, int h, uint8_t v)
{
	for (int yy = y; yy < y + h; yy++)
	{
		memset8(&zbuffer[yy][x], v, w);
	}
}

/* set current zbuffer value for all draw operations */
void vid_zbuffer_set(uint8_t v)
{
	current_z = v;
}
