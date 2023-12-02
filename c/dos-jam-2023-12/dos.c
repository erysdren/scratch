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

#include <stdio.h>

/*
 * mode-agnostic functions
 */

/* set mode of vga adapter */
int dos_set_mode(uint16_t mode)
{
	union REGS r;
	r.w.ax = mode;
	int386(0x10, &r, &r);

	return dos_get_mode();
}

/* get mode of vga adapter */
int dos_get_mode()
{
	union REGS r;
	r.h.ah = 0x0f;
	int386(0x10, &r, &r);
	return r.h.al;
}

/* clear both video mode and text mode screen memory */
void dos_clear_screen()
{
	dos_graphics_clear_screen();
	dos_text_clear_screen();
}

/*
 * graphics mode functions
 */

/* clear vga screen buffer */
void dos_graphics_clear_screen()
{
	memset((void *)DOS_GRAPHICS_MEMORY, 0, 64000);
	dos_text_set_cursor_pos(0, 0);
}

/* place n 1-byte segments from pointer s to the graphics memory */
void dos_graphics_putb(uint8_t *s, size_t n)
{
	/* sanity check */
	if (n > 64000) return;
	memcpy((void *)DOS_GRAPHICS_MEMORY, (void *)s, n * sizeof(uint8_t));
}

/* set a color in the palette */
void dos_set_palette_color(uint8_t i, uint8_t r, uint8_t g, uint8_t b)
{
	outp(0x3c8, i);
	outp(0x3c9, (r * 63) / 255);
	outp(0x3c9, (g * 63) / 255);
	outp(0x3c9, (b * 63) / 255);
}

/* set the palette from a file */
int dos_set_palette_from_file(const char *filename)
{
	static uint8_t palette[256][3];
	FILE *file;
	int i;

	/* open file */
	file = fopen(filename, "rb");
	if (!file)
		return 0;

	/* read palette */
	fread(palette, 768, 1, file);

	/* close file */
	fclose(file);

	/* set palette */
	for (i = 0; i < 256; i++)
	{
		uint8_t r = palette[i][0];
		uint8_t g = palette[i][1];
		uint8_t b = palette[i][2];
		dos_set_palette_color(i, r, g, b);
	}

	return 1;
}

/*
 * vesa functions
 */

/* fill vesa info into struct */
int dos_vesa_get_info(vesa_info_t *vesa_info)
{
	/* variables */
	__dpmi_regs r;
	long dosbuf;
	int c;

	/* use the conventional memory transfer buffer */
	dosbuf = __tb & 0xFFFFF;

	/* initialize the buffer to zero */
	for (c = 0; c < sizeof(vesa_info_t); c++)
		_farpokeb(_dos_ds, dosbuf + c, 0);

	dosmemput("VBE2", 4, dosbuf);

	/* call the VESA function */
	r.x.ax = 0x4F00;
	r.x.di = dosbuf & 0xF;
	r.x.es = (dosbuf >> 4) & 0xFFFF;
	__dpmi_int(0x10, &r);

	/* quit if there was an error */
	if (r.h.ah)
		return 0;

	/* copy the resulting data into our structure */
	dosmemget(dosbuf, sizeof(vesa_info_t), vesa_info);

	/* check that we got the right magic marker value */
	if (memcmp(vesa_info->VESASignature, "VESA", 4) != 0)
		return 0;

	/* return success */
	return 1;
}

/* fill vesa mode info into struct */
int dos_vesa_get_mode_info(vesa_mode_info_t *vesa_mode_info, int mode)
{
	/* variables */
	__dpmi_regs r;
	long dosbuf;
	int c;

	/* use the conventional memory transfer buffer */
	dosbuf = __tb & 0xFFFFF;

	/* initialize the buffer to zero */
	for (c = 0; c < sizeof(vesa_mode_info_t); c++)
		_farpokeb(_dos_ds, dosbuf + c, 0);

	/* call the VESA function */
	r.x.ax = 0x4F01;
	r.x.di = dosbuf & 0xF;
	r.x.es = (dosbuf>>4) & 0xFFFF;
	r.x.cx = mode;
	__dpmi_int(0x10, &r);

	/* quit if there was an error */
	if (r.h.ah)
		return 0;

	/* copy the resulting data into our structure */
	dosmemget(dosbuf, sizeof(vesa_mode_info_t), vesa_mode_info);

	/* return success */
	return 1;
}

/* request vesa mode from width, height and bpp */
int dos_vesa_find_mode(int w, int h, int bpp)
{
	int mode_list[256];
	int number_of_modes;
	long mode_ptr;
	int c;
	vesa_info_t vesa_info;
	vesa_mode_info_t vesa_mode_info;

	/* check that the VESA driver exists, and get information about it */
	if (!dos_vesa_get_info(&vesa_info))
		return 0;

	/* convert the mode list pointer from seg:offset to a linear address */
	mode_ptr = ((vesa_info.VideoModePtr & 0xFFFF0000) >> 12) + 
		(vesa_info.VideoModePtr & 0xFFFF);

	number_of_modes = 0;

	/* read the list of available modes */
	while (_farpeekw(_dos_ds, mode_ptr) != 0xFFFF)
	{
		mode_list[number_of_modes] = _farpeekw(_dos_ds, mode_ptr);
		number_of_modes++;
		mode_ptr += 2;
	}

	/* scan through the list of modes looking for the one that we want */
	for (c = 0; c < number_of_modes; c++)
	{
		/* get information about this mode */
		if (!dos_vesa_get_mode_info(&vesa_mode_info, mode_list[c]))
			continue;

		/* check the flags field to make sure this is a color graphics mode,
		* and that it is supported by the current hardware */
		if ((vesa_mode_info.ModeAttributes & 0x19) != 0x19)
			continue;

		/* check that this mode is the right size */
		if ((vesa_mode_info.XResolution != w) || (vesa_mode_info.YResolution != h))
			continue;

		/* check that there is only one color plane */
		if (vesa_mode_info.NumberOfPlanes != 1)
			continue;

		/* check that this is an 8-bit (256 color) mode */
		if (vesa_mode_info.BitsPerPixel != bpp)
			continue;

		/* if it passed all those checks, this must be the mode we want! */
		return mode_list[c];
	}

	/* oh dear, there was no mode matching the one we wanted! */
	return 0; 
}

/* find and set vesa mode from width, height and bpp */
int dos_vesa_set_mode(uint16_t mode)
{
	__dpmi_regs r;

	/* call the VESA mode set function */
	r.x.ax = 0x4F02;
	r.x.bx = mode;
	__dpmi_int(0x10, &r);

	/* check for error */
	if (r.h.ah)
		return 0;

	/* it worked! */
	return 1;
}

/* set vesa bank for writing pixels */
void dos_vesa_set_bank(int bank)
{
	__dpmi_regs r;

	r.x.ax = 0x4F05;
	r.x.bx = 0;
	r.x.dx = bank;
	__dpmi_int(0x10, &r);
}

/* place a buffer on the screen based on current mode info */
void dos_vesa_putb(vesa_mode_info_t *mode_info, uint8_t *s, size_t n)
{
	int bank_size = mode_info->WinSize * 1024;
	int bank_granularity = mode_info->WinGranularity * 1024;
	int bank_number = 0;
	int todo = n;
	int copy_size = 0;

	while (todo > 0)
	{
		/* select the appropriate bank */
		dos_vesa_set_bank(bank_number);

		/* how much can we copy in one go? */
		if (todo > bank_size)
			copy_size = bank_size;
		else
			copy_size = todo;

		/* copy a bank of data to the screen */
		dosmemput(s, copy_size, 0xA0000);

		/* move on to the next bank of data */
		todo -= copy_size;
		s += copy_size;
		bank_number += bank_size / bank_granularity;
	}
}

/*
 * text mode functions
 */

/* set the shape of the cursor */
void dos_text_set_cursor_shape(uint16_t shape)
{
	union REGS r;
	r.h.ah = 1;
	r.w.cx = shape;
	int386(0x10, &r, &r);
}

/* set text cursor position */
void dos_text_set_cursor_pos(uint16_t x, uint16_t y)
{
	union REGS r;
	r.h.ah = 2;
	r.h.bh = 0;
	r.h.dh = y;
	r.h.dl = x;
	int386(0x10, &r, &r);
}

/* get text cursor position */
void dos_text_get_cursor_pos(uint16_t *x, uint16_t *y)
{
	union REGS r;
	r.h.ah = 3;
	r.h.bh = 0;
	int386(0x10, &r, &r);
	if (x) *x = r.h.dl;
	if (y) *y = r.h.dh;
}

/* clear text screen buffer */
void dos_text_clear_screen()
{
	/* variables */
	size_t s;
	uint16_t c;
	uint16_t *vidmem;

	/* calculate screen size */
	s = dos_text_get_screen_rows() * dos_text_get_screen_columns();

	/* text value we're putting in */
	c = ' ' | (dos_text_get_attributes() << 8);

	/* set memory */
	vidmem = (uint16_t *)DOS_TEXT_MEMORY;
	while (s--) *vidmem++ = c;

	/* reset cursor pos */
	dos_text_set_cursor_pos(0, 0);
}

/* get text screen columns */
int dos_text_get_screen_columns()
{
	return _farpeekb(_dos_ds, 0x44a);
}

/* get text screen rows */
int dos_text_get_screen_rows()
{
	return _farpeekb(_dos_ds, 0x484) + 1;
}

/* get text screen size */
void dos_text_get_screen_size(int *rows, int *columns)
{
	if (rows) *rows = dos_text_get_screen_rows();
	if (columns) *columns = dos_text_get_screen_columns();
}

/* retrieve current text attributes */
int dos_text_get_attributes()
{
	union REGS r;
	r.h.ah = 0x08;
	r.h.bh = 0;
	int386(0x10, &r, &r);

	return r.h.ah;
}

/* place n 2-byte segments from pointer s to the text memory */
void dos_text_putb(uint16_t x, uint16_t y, uint16_t *s, size_t n)
{
	/* variables */
	size_t max, rows, cols, ofs;

	/* set variables */
	rows = dos_text_get_screen_rows();
	cols = dos_text_get_screen_columns();
	max = rows * cols;
	ofs = (y * cols + x) * sizeof(uint16_t);

	/* sanity checks */
	if (n > max) return;

	/* do copy */
	memcpy((void *)(DOS_TEXT_MEMORY + ofs), (void *)s, n * sizeof(uint16_t));
}

/* place char sequence s at column x, row y */
void dos_text_puts(uint16_t x, uint16_t y, const char *s)
{
	/* variables */
	int i;

	/* perform put loop */
	for (i = 0; i < strlen(s); i++)
		dos_text_putc(x + i, y, s[i]);
}

/* place char c at column x, row y */
void dos_text_putc(uint16_t x, uint16_t y, char c)
{
	((uint16_t *)DOS_TEXT_MEMORY)[y * dos_text_get_screen_columns() + x] = 
		c | (dos_text_get_attributes() << 8);
}

/*
 * microsoft mouse
 */

/* enable mouse driver */
void dos_mouse_enable()
{
	union REGS r;
	r.w.ax = 0x00;
	int386(0x33, &r, &r);
}

/* show mouse cursor */
void dos_mouse_show()
{
	union REGS r;
	r.w.ax = 0x01;
	int386(0x33, &r, &r);
}

/* hide mouse cursor */
void dos_mouse_hide()
{
	union REGS r;
	r.w.ax = 0x02;
	int386(0x33, &r, &r);
}

/* get mouse values */
void dos_mouse_get(int16_t *x, int16_t *y, int16_t *b)
{
	union REGS r;
	r.w.ax = 0x03;
	int386(0x33, &r, &r);
	if (b) *b = r.w.bx;
	if (x) *x = r.w.cx;
	if (y) *y = r.w.dx;
}

/* set mouse values */
void dos_mouse_set(int16_t x, int16_t y, int16_t b)
{
	union REGS r;
	r.w.ax = 0x04;
	r.w.bx = b;
	r.w.cx = x;
	r.w.dx = y;
	int386(0x33, &r, &r);
}
