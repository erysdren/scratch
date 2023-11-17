
#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "inttypes.h"

/* video memory locations */
extern uint16_t __far *text_memory;
extern uint8_t __far *cga_memory_even;
extern uint8_t __far *cga_memory_odd;
extern uint8_t __far *vga_memory;

/* video mode codes */
#define VIDEO_MODE_00H 0x00 /* text, 40×25, 16 colors */
#define VIDEO_MODE_01H 0x01 /* text, 40×25, 16 colors */
#define VIDEO_MODE_02H 0x02 /* text, 80×25, 16 colors */
#define VIDEO_MODE_03H 0x03 /* text, 80×25, 16 colors */
#define VIDEO_MODE_04H 0x04 /* graphics, 320x200, 4 colors */
#define VIDEO_MODE_05H 0x05 /* graphics, 320x200, 4 colors */
#define VIDEO_MODE_06H 0x06 /* graphics, 640x200, 2 colors */
#define VIDEO_MODE_07H 0x07 /* text, 80×25, monochrome */
#define VIDEO_MODE_0DH 0x0D /* graphics, 320x200, 16 colors */
#define VIDEO_MODE_0EH 0x0E /* graphics, 640x200, 16 colors */
#define VIDEO_MODE_0FH 0x0F /* graphics, 640x350, monochrome */
#define VIDEO_MODE_10H 0x10 /* graphics, 640x350, 16 colors */
#define VIDEO_MODE_11H 0x11 /* graphics, 640x480, 2 colors */
#define VIDEO_MODE_12H 0x12 /* graphics, 640x480, 16 colors */
#define VIDEO_MODE_13H 0x13 /* graphics, 320x200, 256 colors */

/* set video mode */
uint8_t video_set_mode(uint8_t mode);

/* get video mode */
uint8_t video_get_mode(void);

#endif /* _VIDEO_H_ */
