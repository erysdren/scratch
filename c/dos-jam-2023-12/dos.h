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

#pragma once
#ifndef _DOS_H_
#define _DOS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <dos.h>
#include <io.h>
#include <conio.h>

#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

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

/*
 * memory locations
 */

#define DOS_GRAPHICS_MEMORY (0xA0000 + __djgpp_conventional_base)
#define DOS_TEXT_MEMORY (0xB8000 + __djgpp_conventional_base)

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

/* mode-agnostic functions */
int dos_set_mode(uint16_t mode);
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

#ifdef __cplusplus
}
#endif
#endif /* _DOS_H_ */

