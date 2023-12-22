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
	EUI_ALIGN_CENTER,
	EUI_ALIGN_END
};

/* true/false/unset */
enum {
	EUI_UNSET = -1,
	EUI_FALSE = 0,
	EUI_TRUE = 1
};

/*
 *
 * eui types
 *
 */

/* vector */
typedef struct eui_vec2_t {
	int x, y;
} eui_vec2_t;

/*
 *
 * helper macros
 *
 */

/* vec2 */
#define EUI_VEC2(x, y) (eui_vec2_t){(x), (y)}

/*
 *
 * function prototypes
 *
 */

/* transforms */
void eui_transform_point(eui_vec2_t *pos);
void eui_transform_box(eui_vec2_t *pos, eui_vec2_t size);
void eui_clip_box(eui_vec2_t *pos, eui_vec2_t *size);

/* frame handling */
void eui_push_frame(eui_vec2_t pos, eui_vec2_t size);
void eui_pop_frame(void);
void eui_reset_frame(void);
void eui_set_align(int x, int y);

/* input handling */
void eui_set_cursor(eui_vec2_t pos);
void eui_move_cursor(eui_vec2_t move);
void eui_set_button(int left, int right);

/* begin/end */
bool eui_begin(int w, int h, int pitch, uint8_t *pixels);
void eui_end(void);

/* draw handling */
void eui_set_bg_color(uint8_t color);
void eui_set_fg_color(uint8_t color);

/* draw primitives */
void eui_filled_box(eui_vec2_t pos, eui_vec2_t size, uint8_t color);
void eui_border_box(eui_vec2_t pos, eui_vec2_t size, int width, uint8_t color);
void eui_text(eui_vec2_t pos, uint8_t color, char *s);
void eui_textf(eui_vec2_t pos, uint8_t color, char *s, ...);

/* widgets */
bool eui_button(eui_vec2_t pos, eui_vec2_t size, char *text);

#ifdef __cplusplus
}
#endif
#endif /* _EUI_H_ */