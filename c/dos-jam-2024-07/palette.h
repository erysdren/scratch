
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
