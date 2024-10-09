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

#ifndef _PALETTE_H_
#define _PALETTE_H_

#include <stdint.h>

enum {
	PAL_BLACK = 0,
	PAL_DARK_BLUE = 1,
	PAL_DARK_GREEN = 2,
	PAL_DARK_TEAL = 3,
	PAL_DARK_RED = 4,
	PAL_DARK_ORANGE = 5,
	PAL_DARK_GOLD = 6,
	PAL_LIGHT_GREY = 7,
	PAL_DARK_GREY = 8,
	PAL_LIGHT_BLUE = 9,
	PAL_LIGHT_GREEN = 10,
	PAL_LIGHT_TEAL = 11,
	PAL_LIGHT_RED = 12,
	PAL_LIGHT_ORANGE = 13,
	PAL_LIGHT_GOLD = 14,
	PAL_WHITE = 15
};

static const uint8_t palette[16 * 3] = {
	0x00, 0x00, 0x00, 0x00, 0x33, 0x98, 0x28, 0xc8, 0x28, 0x33, 0xcb, 0xcb,
	0xcb, 0x00, 0x33, 0xff, 0x65, 0x00, 0xff, 0xcb, 0x00, 0x88, 0x88, 0x88,
	0x50, 0x50, 0x50, 0x33, 0x66, 0x98, 0x5a, 0xff, 0x5a, 0x33, 0xff, 0xff,
	0xff, 0x33, 0x33, 0xff, 0xcf, 0x00, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff
};

#endif /* _PALETTE_H_ */
