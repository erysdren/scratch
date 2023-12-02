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

/*
 * other constants
 */

#define DOS_CLOCK_SPEED 1193181

/*
 * keyboard scancodes
 */

enum {
	SC_ESCAPE = 0x01,
	SC_1 = 0x02,
	SC_2 = 0x03,
	SC_3 = 0x04,
	SC_4 = 0x05,
	SC_5 = 0x06,
	SC_6 = 0x07,
	SC_7 = 0x08,
	SC_8 = 0x09,
	SC_9 = 0x0A,
	SC_0 = 0x0B,
	SC_MINUS = 0x0C,
	SC_EQUALS = 0x0D,
	SC_BACKSPACE = 0x0E,
	SC_TAB = 0x0F,
	SC_Q = 0x10,
	SC_W = 0x11,
	SC_E = 0x12,
	SC_R = 0x13,
	SC_T = 0x14,
	SC_Y = 0x15,
	SC_U = 0x16,
	SC_I = 0x17,
	SC_O = 0x18,
	SC_P = 0x19,
	SC_LEFTBRACKET = 0x1A,
	SC_RIGHTBRACKET = 0x1B,
	SC_ENTER = 0x1C,
	SC_CONTROL = 0x1D,
	SC_A = 0x1E,
	SC_S = 0x1F,
	SC_D = 0x20,
	SC_F = 0x21,
	SC_G = 0x22,
	SC_H = 0x23,
	SC_J = 0x24,
	SC_K = 0x25,
	SC_L = 0x26,
	SC_SEMICOLON = 0x27,
	SC_QUOTE = 0x28,
	SC_TILDE = 0x29,
	SC_LSHIFT = 0x2A,
	SC_BACKSLASH = 0x2B,
	SC_Z = 0x2C,
	SC_X = 0x2D,
	SC_C = 0x2E,
	SC_V = 0x2F,
	SC_B = 0x30,
	SC_N = 0x31,
	SC_M = 0x32,
	SC_COMMA = 0x33,
	SC_PERIOD = 0x34,
	SC_SLASH = 0x35,
	SC_RSHIFT = 0x36,
	SC_MULTIPLY = 0x37,
	SC_ALT = 0x38,
	SC_SPACE = 0x39,
	SC_CAPSLOCK = 0x3A,
	SC_F1 = 0x3B,
	SC_F2 = 0x3C,
	SC_F3 = 0x3D,
	SC_F4 = 0x3E,
	SC_F5 = 0x3F,
	SC_F6 = 0x40,
	SC_F7 = 0x41,
	SC_F8 = 0x42,
	SC_F9 = 0x43,
	SC_F10 = 0x44,
	SC_NUMLOCK = 0x45,
	SC_SCROLLLOCK = 0x46,
	SC_HOME = 0x47,
	SC_UP = 0x48,
	SC_PAGEUP = 0x49,
	SC_LEFT = 0x4B,
	SC_CLEAR = 0x4C,
	SC_CENTER = 0x4C,
	SC_RIGHT = 0x4D,
	SC_PLUS = 0x4E,
	SC_END = 0x4F,
	SC_DOWN = 0x50,
	SC_PAGEDOWN = 0x51,
	SC_INSERT = 0x52,
	SC_DELETE = 0x53,
	SC_F11 = 0x57,
	SC_F12 = 0x58
};

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
void dos_set_palette(uint8_t palette[256][3]);

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

