
/* guards */
#pragma once
#ifndef __DOS_UTILS_H__
#define __DOS_UTILS_H__
#ifdef __cplusplus
extern "C" {
#endif

/*
 * this file is special. we need to trigger a failure
 * if its not being compiled by a supported dos compiler
 */
#if !defined(__DJGPP__) && !defined(__WATCOMC__)
#error i can only be compiled with watcom or djgpp!
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* std */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* shared dos headers */
#if defined(__DJGPP__) || defined(__WATCOMC__)

/* standard dos headers */
#include <dos.h>
#include <io.h>
#include <conio.h>

#endif

/* watcom headers */
#ifdef __WATCOMC__

#include <i86.h>
#include <graph.h>

#endif

/* djgpp headers */
#ifdef __DJGPP__

#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

#endif

/* *************************************
 *
 * the text macros
 *
 * ********************************** */

/*
 * standard video modes supported by all vga cards
 */

#define DOS_MODE_0 0x0				/* 40×25, text, 16 colors */
#define DOS_MODE_1 0x1				/* 40×25, text, 16 colors */
#define DOS_MODE_2 0x2				/* 80×25, text, 16 colors */
#define DOS_MODE_3 0x3				/* 80×25, text, 16 colors */
#define DOS_MODE_4 0x4				/* 320x200, graphics, 4 colors */
#define DOS_MODE_5 0x5				/* 320x200, graphics, 4 colors */
#define DOS_MODE_6 0x6				/* 640x200, graphics, 2 colors */
#define DOS_MODE_7 0x7				/* 80×25, text, monochrome */
#define DOS_MODE_D 0xD				/* 320x200, graphics, 16 colors */
#define DOS_MODE_E 0xE				/* 640x200, graphics, 16 colors */
#define DOS_MODE_F 0xF				/* 640x350, graphics, monochrome */
#define DOS_MODE_10 0x10			/* 640x350, graphics, 16 colors */
#define DOS_MODE_11 0x11			/* 640x480, graphics, 2 colors */
#define DOS_MODE_12 0x12			/* 640x480, graphics, 16 colors */
#define DOS_MODE_13 0x13			/* 320x200, graphics, 256 colors */

/*
 * cursor shapes available in text mode
 */

#define DOS_CURSOR_NONE 0x2000		/* no cursor */
#define DOS_CURSOR_BLOCK 0x0007		/* solid block cursor */
#define DOS_CURSOR_LINE 0x0607		/* default underline cursor */

/*
 * mouse button masks
 */

#define DOS_MOUSE_LMB 0x1
#define DOS_MOUSE_RMB 0x2

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* pointers to memory locations */
#ifdef __DJGPP__
#define DOS_GRAPHICS_MEMORY (0xA0000 + __djgpp_conventional_base)
#define DOS_TEXT_MEMORY (0xB8000 + __djgpp_conventional_base)
#else
#define DOS_GRAPHICS_MEMORY (0xA0000L)
#define DOS_TEXT_MEMORY (0xB8000L)
#endif

/* vesa info */
typedef struct
{ 
	uint8_t VESASignature[4];
	uint16_t VESAVersion;
	uint32_t OEMStringPtr;
	uint8_t Capabilities[4];
	uint32_t VideoModePtr;
	uint16_t TotalMemory;
	uint16_t OemSoftwareRev;
	uint32_t OemVendorNamePtr;
	uint32_t OemProductNamePtr;
	uint32_t OemProductRevPtr;
	uint8_t Reserved[222];
	uint8_t OemData[256];
} vesa_info_t;

/* vesa mode info */
typedef struct
{
	uint16_t ModeAttributes;
	uint8_t WinAAttributes;
	uint8_t WinBAttributes;
	uint16_t WinGranularity;
	uint16_t WinSize;
	uint16_t WinASegment;
	uint16_t WinBSegment;
	uint32_t WinFuncPtr;
	uint16_t BytesPerScanLine;
	uint16_t XResolution;
	uint16_t YResolution;
	uint8_t XCharSize;
	uint8_t YCharSize;
	uint8_t NumberOfPlanes;
	uint8_t BitsPerPixel;
	uint8_t NumberOfBanks;
	uint8_t MemoryModel;
	uint8_t BankSize;
	uint8_t NumberOfImagePages;
	uint8_t Reserved_page;
	uint8_t RedMaskSize;
	uint8_t RedMaskPos;
	uint8_t GreenMaskSize;
	uint8_t GreenMaskPos;
	uint8_t BlueMaskSize;
	uint8_t BlueMaskPos;
	uint8_t ReservedMaskSize;
	uint8_t ReservedMaskPos;
	uint8_t DirectColorModeInfo;
	uint32_t PhysBasePtr;
	uint32_t OffScreenMemOffset;
	uint16_t OffScreenMemSize;
	uint8_t Reserved[206];
} vesa_mode_info_t;

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* mode-agnostic functions */
void dos_set_mode(uint16_t mode);
int dos_get_mode();
void dos_clear_screen();

/* graphics mode functions */
void dos_graphics_clear_screen();
void dos_graphics_putb(uint8_t *s, size_t n);
void dos_set_palette_color(uint8_t i, uint8_t r, uint8_t g, uint8_t b);

/* vesa functions */
int dos_vesa_get_info(vesa_info_t *vesa_info);
int dos_vesa_get_mode_info(vesa_mode_info_t *vesa_mode_info, int mode);
int dos_vesa_find_mode(int w, int h, int bpp);
int dos_vesa_set_mode(uint16_t mode);
void dos_vesa_set_bank(int bank);
void dos_vesa_putb(vesa_mode_info_t *mode_info, uint8_t *s, size_t n);

/* text mode functions */
void dos_text_set_cursor_shape(uint16_t shape);
void dos_text_set_cursor_pos(uint16_t x, uint16_t y);
void dos_text_get_cursor_pos(uint16_t *x, uint16_t *y);
void dos_text_clear_screen();
int dos_text_get_screen_columns();
int dos_text_get_screen_rows();
void dos_text_get_screen_size(int *w, int *h);
int dos_text_get_attributes();
void dos_text_putb(uint16_t x, uint16_t y, uint16_t *s, size_t n);
void dos_text_puts(uint16_t x, uint16_t y, const char *s);
void dos_text_putc(uint16_t x, uint16_t y, char c);

/* microsoft mouse */
void dos_mouse_enable();
void dos_mouse_show();
void dos_mouse_hide();
void dos_mouse_get(int16_t *x, int16_t *y, int16_t *b);
void dos_mouse_set(int16_t x, int16_t y, int16_t b);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * mode-agnostic functions
 */

/* set mode of vga adapter */
void dos_set_mode(uint16_t mode)
{
	union REGS r;
	r.w.ax = mode;
	int386(0x10, &r, &r);
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
	#ifdef __DJGPP__
	return _farpeekb(_dos_ds, 0x44a);
	#else
	return *(char *)0x44a;
	#endif
}

/* get text screen rows */
int dos_text_get_screen_rows()
{
	#ifdef __DJGPP__
	return _farpeekb(_dos_ds, 0x484) + 1;
	#else
	return *(char *)0x484 + 1;
	#endif
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

/* guards */
#ifdef __cplusplus
}
#endif
#endif /* __DOS_UTILS_H__ */
