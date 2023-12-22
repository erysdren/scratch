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
#ifndef _EUI_H_
#define _EUI_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/* element alignment */
enum {
	EUI_ALIGN_START,
	EUI_ALIGN_MIDDLE,
	EUI_ALIGN_END
};

/* true/false/unset */
enum {
	EUI_UNSET = -1,
	EUI_FALSE = 0,
	EUI_TRUE = 1
};

/* button type */
enum {
	EUI_BUTTON_LEFT,
	EUI_BUTTON_RIGHT
};

/* event type */
enum {
	EUI_EVENT_NONE,
	EUI_EVENT_KEY_DOWN,
	EUI_EVENT_KEY_UP,
	EUI_EVENT_MOUSE,
	EUI_EVENT_BUTTON_DOWN,
	EUI_EVENT_BUTTON_UP
};

/*
 *
 * eui types
 *
 */

/* default pixel depth is 8bpp */
#ifndef EUI_PIXEL_DEPTH
#define EUI_PIXEL_DEPTH (8)
#endif

/* pixel color type */
#if (EUI_PIXEL_DEPTH == 8)
typedef uint8_t eui_color_t;
#elif (EUI_PIXEL_DEPTH == 16)
typedef uint16_t eui_color_t;
#elif (EUI_PIXEL_DEPTH == 32)
typedef uint32_t eui_color_t;
#else
#error Unsupported pixel depth!
#endif

/* vec2 */
typedef struct eui_vec2_t {
	int x, y;
} eui_vec2_t;

/* event */
typedef union eui_event_t {
	int type;
	struct { int type; uint32_t scancode; } key;
	struct { int type; int x; int y; int xrel; int yrel; } mouse;
	struct { int type; int x; int y; int button; } button;
} eui_event_t;

/* pixelmap */
typedef struct eui_pixelmap_t {
	int w;
	int h;
	int pitch;
	eui_color_t *pixels;
} eui_pixelmap_t;

/* general callback function */
typedef void eui_callback(void *user);

/*
 *
 * helper macros
 *
 */

/* create vec2 */
#define EUI_VEC2(x, y) (eui_vec2_t){(x), (y)}

/* create pixelmap */
#define EUI_PIXELMAP(w, h, pitch, pixels) (eui_pixelmap_t){(w), (h), (pitch), (pixels)}

/*
 *
 * basic transforms
 *
 */

/* transform point to current frame, with alignment */
void eui_transform_point(eui_vec2_t *pos);

/* transform box to current frame, with alignment */
void eui_transform_box(eui_vec2_t *pos, eui_vec2_t size);

/* clip box to screen size, returns false if the shape will never be visible */
bool eui_clip_box(eui_vec2_t *pos, eui_vec2_t *size);

/*
 *
 * frame handling
 *
 */

/* go to subframe, transformed from current frame */
void eui_push_frame(eui_vec2_t pos, eui_vec2_t size);

/* return to parent frame */
void eui_pop_frame(void);

/* reset all frame transforms */
void eui_reset_frame(void);

/* set current frame alignment */
void eui_set_align(int xalign, int yalign);

/*
 *
 * event handling
 *
 */

/* push event to the queue */
void eui_push_event(eui_event_t event);

/* pop event from the top of the queue */
int eui_pop_event(eui_event_t *out);

/*
 *
 * begin/end
 *
 */

/* begin eui with given pixelmap destination */
bool eui_begin(eui_pixelmap_t dest);

/* end eui */
void eui_end(void);

/*
 *
 * utilities
 *
 */

/* get dimensions of text string, with newlines */
eui_vec2_t eui_get_text_size(char *s);

/* returns true if the mouse cursor is hovering over the given area */
bool eui_is_hovered(eui_vec2_t pos, eui_vec2_t size);

/*
 *
 * drawing primitives
 *
 */

/* draw filled box at pos, transformed */
void eui_filled_box(eui_vec2_t pos, eui_vec2_t size, eui_color_t color);

/* draw hollow box at pos, transformed */
void eui_border_box(eui_vec2_t pos, eui_vec2_t size, int width, eui_color_t color);

/* draw text at pos, transformed */
void eui_text(eui_vec2_t pos, eui_color_t color, char *s);

/* draw formatted text at pos, transformed */
void eui_textf(eui_vec2_t pos, eui_color_t color, char *s, ...);

/* draw filled triangle with provided points, transformed */
void eui_filled_triangle(eui_vec2_t p0, eui_vec2_t p1, eui_vec2_t p2, eui_color_t color);

/* draw line from p0 to p1, transformed */
void eui_line(eui_vec2_t p0, eui_vec2_t p1, eui_color_t color);

/*
 *
 * widgets
 *
 */

/* fires callback function if pressed and returns true if hovered */
bool eui_button(eui_vec2_t pos, eui_vec2_t size, char *text, eui_callback callback, void *user);

#ifdef __cplusplus
}
#endif
#endif /* _EUI_H_ */
