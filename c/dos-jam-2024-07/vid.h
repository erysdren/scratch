
#ifndef _VID_H_
#define _VID_H_

#include <stdint.h>

#define VID_WIDTH (80)
#define VID_HEIGHT (50)
#define VID_BITS_PER_PIXEL (16)
#define VID_BYTES_PER_PIXEL (VID_BITS_PER_PIXEL / 8)
#define VID_PITCH (VID_WIDTH * VID_BYTES_PER_PIXEL)
#define VID_BUFFER_SIZE (VID_PITCH * VID_HEIGHT)

#define VID_FONT_WIDTH (8)
#define VID_FONT_HEIGHT (8)

/* start video system */
void vid_init(void);

/* shutdown video system */
void vid_quit(void);

/* get pointer to writeable video framebuffer */
uint8_t *vid_framebuffer_get(void);

/* clear video framebuffer */
void vid_framebuffer_clear(uint8_t bg, uint8_t fg);

/* set video mode */
void vid_mode_set(uint8_t mode);

/* get current video mode */
uint8_t vid_mode_get(void);

/* wait for vertical retrace */
void vid_vsync_wait(void);

/* set palette color at index */
void vid_palette_set_color(int i, uint8_t red, uint8_t grn, uint8_t blu);

/* set palette of N colors */
void vid_palette_set(int num_colors, uint8_t *colors);

/* create packed text cell color */
__attribute__((pure)) uint8_t vid_cell_color(uint8_t bg, uint8_t fg);

/* create packed text cell */
__attribute__((pure)) uint16_t vid_cell(unsigned char c, uint8_t color);

/* get current text attributes as a packed cell */
uint8_t vid_get_attributes(void);

/* set current text attributes */
void vid_set_attributes(uint8_t bg, uint8_t fg);

/* put cell at x,y */
void vid_cell_put(int x, int y, uint16_t cell);

/* fill cells at x,y with width and height */
void vid_cell_fill(int x, int y, int w, int h, uint16_t cell);

/* set cursor position */
void vid_cursor_set_position(uint8_t x, uint8_t y);

#endif /* _VID_H_ */
