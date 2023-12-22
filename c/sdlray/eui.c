/*
MIT License

Copyright (c) 2018 shpuld
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

/*
 *
 * EUI.C
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "eui.h"

/*
 *
 * font8x8
 *
 */

unsigned char font8x8_basic[128][8] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0000 (nul)
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0001
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0002
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0003
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0004
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0005
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0006
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0007
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0008
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0009
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000A
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000B
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000C
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000D
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000E
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000F
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0010
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0011
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0012
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0013
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0014
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0015
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0016
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0017
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0018
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0019
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001A
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001B
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001C
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001D
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001E
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001F
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0020 (space)
	{ 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, // U+0021 (!)
	{ 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0022 (")
	{ 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00}, // U+0023 (#)
	{ 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00}, // U+0024 ($)
	{ 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00}, // U+0025 (%)
	{ 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00}, // U+0026 (&)
	{ 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0027 (')
	{ 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00}, // U+0028 (()
	{ 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00}, // U+0029 ())
	{ 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, // U+002A (*)
	{ 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00}, // U+002B (+)
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+002C (,)
	{ 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // U+002D (-)
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+002E (.)
	{ 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00}, // U+002F (/)
	{ 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00}, // U+0030 (0)
	{ 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}, // U+0031 (1)
	{ 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00}, // U+0032 (2)
	{ 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00}, // U+0033 (3)
	{ 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00}, // U+0034 (4)
	{ 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00}, // U+0035 (5)
	{ 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00}, // U+0036 (6)
	{ 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00}, // U+0037 (7)
	{ 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00}, // U+0038 (8)
	{ 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00}, // U+0039 (9)
	{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+003A (:)
	{ 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+003B (;)
	{ 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00}, // U+003C (<)
	{ 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00}, // U+003D (=)
	{ 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, // U+003E (>)
	{ 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00}, // U+003F (?)
	{ 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00}, // U+0040 (@)
	{ 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}, // U+0041 (A)
	{ 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00}, // U+0042 (B)
	{ 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00}, // U+0043 (C)
	{ 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00}, // U+0044 (D)
	{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00}, // U+0045 (E)
	{ 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00}, // U+0046 (F)
	{ 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00}, // U+0047 (G)
	{ 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}, // U+0048 (H)
	{ 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0049 (I)
	{ 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00}, // U+004A (J)
	{ 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00}, // U+004B (K)
	{ 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00}, // U+004C (L)
	{ 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00}, // U+004D (M)
	{ 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00}, // U+004E (N)
	{ 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00}, // U+004F (O)
	{ 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00}, // U+0050 (P)
	{ 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00}, // U+0051 (Q)
	{ 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00}, // U+0052 (R)
	{ 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00}, // U+0053 (S)
	{ 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0054 (T)
	{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00}, // U+0055 (U)
	{ 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0056 (V)
	{ 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}, // U+0057 (W)
	{ 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00}, // U+0058 (X)
	{ 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00}, // U+0059 (Y)
	{ 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00}, // U+005A (Z)
	{ 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00}, // U+005B ([)
	{ 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, // U+005C (\)
	{ 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00}, // U+005D (])
	{ 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00}, // U+005E (^)
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // U+005F (_)
	{ 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0060 (`)
	{ 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00}, // U+0061 (a)
	{ 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00}, // U+0062 (b)
	{ 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00}, // U+0063 (c)
	{ 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00}, // U+0064 (d)
	{ 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00}, // U+0065 (e)
	{ 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00}, // U+0066 (f)
	{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0067 (g)
	{ 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00}, // U+0068 (h)
	{ 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0069 (i)
	{ 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E}, // U+006A (j)
	{ 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00}, // U+006B (k)
	{ 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+006C (l)
	{ 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00}, // U+006D (m)
	{ 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00}, // U+006E (n)
	{ 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00}, // U+006F (o)
	{ 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F}, // U+0070 (p)
	{ 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78}, // U+0071 (q)
	{ 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00}, // U+0072 (r)
	{ 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00}, // U+0073 (s)
	{ 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00}, // U+0074 (t)
	{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00}, // U+0075 (u)
	{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0076 (v)
	{ 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00}, // U+0077 (w)
	{ 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00}, // U+0078 (x)
	{ 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0079 (y)
	{ 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00}, // U+007A (z)
	{ 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00}, // U+007B ({)
	{ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00}, // U+007C (|)
	{ 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00}, // U+007D (})
	{ 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+007E (~)
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // U+007F
};

/*
 *
 * local types
 *
 */

/* frame */
typedef struct frame_t {
	eui_vec2_t pos;
	eui_vec2_t size;
	eui_vec2_t align;
} frame_t;

/* pixelmap */
typedef struct pixelmap_t {
	int w;
	int h;
	int pitch;
	uint8_t *pixels;
} pixelmap_t;

/*
 *
 * local variables
 *
 */

/* frames */
#define MAX_FRAMES (64)
static frame_t frames[MAX_FRAMES] = {0};
static int frame_index = 0;

/* destination pixelmap */
static pixelmap_t dest = {0};
#define PIXEL(x, y) dest.pixels[y * dest.pitch + x]

/* configuration */
static uint8_t fg_color = 0;
static uint8_t bg_color = 0;
static uint8_t text_color = 0;
static uint8_t border_color = 0;
static int border_width = 1;
static int window_padding = 0;

/* input handling */
static eui_vec2_t cursor = {-1, -1};
static eui_vec2_t button = {0, 0};

/*
 *
 * transforms
 *
 */

void eui_transform_point(eui_vec2_t *pos)
{
	switch (frames[frame_index].align.x)
	{
		case EUI_ALIGN_START:
			pos->x += frames[frame_index].pos.x;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x / 2;
			break;
		case EUI_ALIGN_END:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x;
			break;
		default:
			break;
	}

	switch (frames[frame_index].align.y)
	{
		case EUI_ALIGN_START:
			pos->y += frames[frame_index].pos.y;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y / 2;
			break;
		case EUI_ALIGN_END:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y;
			break;
		default:
			break;
	}
}

void eui_transform_box(eui_vec2_t *pos, eui_vec2_t size)
{
	switch (frames[frame_index].align.x)
	{
		case EUI_ALIGN_START:
			pos->x += frames[frame_index].pos.x;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x / 2 - size.x / 2;
			break;
		case EUI_ALIGN_END:
			pos->x += frames[frame_index].pos.x + frames[frame_index].size.x - size.x;
			break;
		default:
			break;
	}

	switch (frames[frame_index].align.y)
	{
		case EUI_ALIGN_START:
			pos->y += frames[frame_index].pos.y;
			break;
		case EUI_ALIGN_MIDDLE:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y / 2 - size.y / 2;
			break;
		case EUI_ALIGN_END:
			pos->y += frames[frame_index].pos.y + frames[frame_index].size.y - size.y;
			break;
		default:
			break;
	}
}

void eui_clip_box(eui_vec2_t *pos, eui_vec2_t *size)
{
	/* it will never become visible */
	if (pos->x >= dest.w)
		return;
	if (pos->y >= dest.h)
		return;
	if (pos->x + size->x < 0)
		return;
	if (pos->y + size->y < 0)
		return;

	/* clip to top edge */
	if (pos->y < 0)
	{
		size->y += pos->y;
		pos->y = 0;
	}

	/* clip to bottom edge */
	if (pos->y + size->y >= dest.h)
	{
		size->y = dest.h - pos->y;
	}

	/* clip to left edge */
	if (pos->x < 0)
	{
		size->x += pos->x;
		pos->x = 0;
	}

	/* clip to right edge */
	if (pos->x + size->x >= dest.w)
	{
		size->x = dest.w - pos->x;
	}
}

/*
 *
 * frame handling
 *
 */

void eui_push_frame(eui_vec2_t pos, eui_vec2_t size)
{
	eui_transform_box(&pos, size);

	frame_index += 1;

	frames[frame_index].pos = pos;
	frames[frame_index].size = size;
	frames[frame_index].align.x = EUI_ALIGN_START;
	frames[frame_index].align.y = EUI_ALIGN_START;
}


void eui_pop_frame(void)
{
	if (frame_index)
		frame_index -= 1;
}

void eui_reset_frame(void)
{
	frame_index = 0;
}

/*
 *
 * input handling
 *
 */

static bool is_cursor_above(eui_vec2_t pos, eui_vec2_t size)
{
	if (cursor.x < pos.x || cursor.x > pos.x + size.x)
		return false;
	if (cursor.y < pos.y || cursor.y > pos.y + size.y)
		return false;
	return true;
}

void eui_set_cursor(eui_vec2_t pos)
{
	cursor = pos;
}

void eui_move_cursor(eui_vec2_t move)
{
	cursor.x += move.x;
	cursor.y += move.y;
}

void eui_set_button(int left, int right)
{
	if (left != EUI_UNSET)
		button.x = left;
	if (right != EUI_UNSET)
		button.y = right;
}

/*
 *
 * begin/end
 *
 */

bool eui_begin(int w, int h, int pitch, uint8_t *pixels)
{
	dest.w = w;
	dest.h = h;
	dest.pitch = pitch;
	dest.pixels = pixels;

	eui_reset_frame();
	eui_push_frame(EUI_VEC2(0, 0), EUI_VEC2(w, h));

	return true;
}

void eui_end(void)
{

}

/*
 *
 * configuration
 *
 */

void eui_set_bg_color(uint8_t color)
{
	bg_color = color;
}

void eui_set_fg_color(uint8_t color)
{
	fg_color = color;
}

void eui_set_text_color(uint8_t color)
{
	text_color = color;
}

void eui_set_border_color(uint8_t color)
{
	border_color = color;
}

void eui_set_border_width(int width)
{
	border_width = width;
}

void eui_set_window_padding(int padding)
{
	window_padding = padding;
}

void eui_set_align(int xalign, int yalign)
{
	frames[frame_index].align.x = xalign;
	frames[frame_index].align.y = yalign;
}

/*
 *
 * primitives
 *
 */

void eui_filled_box(eui_vec2_t pos, eui_vec2_t size, uint8_t color)
{
	eui_transform_box(&pos, size);
	eui_clip_box(&pos, &size);

	for (int y = pos.y; y < pos.y + size.y; y++)
	{
		memset(&PIXEL(pos.x, y), color, size.x);
	}
}

void eui_border_box(eui_vec2_t pos, eui_vec2_t size, int width, uint8_t color)
{
	/* top line */
	eui_filled_box(pos, EUI_VEC2(size.x, width), color);

	/* bottom line */
	eui_filled_box(EUI_VEC2(pos.x, pos.y + size.y - width), EUI_VEC2(size.x, width), color);

	/* left line */
	eui_filled_box(EUI_VEC2(pos.x, pos.y + width), EUI_VEC2(width, size.y - width * 2), color);

	/* right line */
	eui_filled_box(EUI_VEC2(pos.x + size.x - width, pos.y + width), EUI_VEC2(width, size.y - width * 2), color);
}

static void eui_font8x8(eui_vec2_t pos, unsigned char *bitmap, uint8_t color)
{
	int x, y;
	int xx, yy;

	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			if (bitmap[x] & 1 << y)
			{
				xx = pos.x + y;
				yy = pos.y + x;

				if (xx < 0 || xx >= dest.w || yy < 0 || yy >= dest.h)
					continue;

				PIXEL(xx, yy) = color;
			}
		}
	}
}

void eui_text(eui_vec2_t pos, uint8_t color, char *s)
{
	eui_vec2_t size;
	int c;

	size.x = strlen(s) * 8;
	size.y = 8;

	eui_transform_box(&pos, size);

	while ((c = *s++))
	{
		eui_font8x8(pos, font8x8_basic[c], color);
		pos.x += 8;
	}
}

void eui_textf(eui_vec2_t pos, uint8_t color, char *s, ...)
{
	static char text[1024];
	va_list args;

	va_start(args, s);
	vsnprintf(text, sizeof(text), s, args);
	va_end(args);

	eui_text(pos, color, text);
}

/*
 *
 * widgets
 *
 */

bool eui_window_begin(eui_vec2_t pos, eui_vec2_t size, char *title)
{
	/* window base and border */
	eui_filled_box(pos, size, bg_color);
	eui_border_box(pos, size, border_width, border_color);

	/* window title */
	eui_border_box(pos, EUI_VEC2(size.x, 16), border_width, border_color);
	eui_push_frame(pos, EUI_VEC2(size.x, 16));
	eui_set_align(EUI_ALIGN_MIDDLE, EUI_ALIGN_MIDDLE);
	eui_text(EUI_VEC2(0, 0), text_color, title);
	eui_pop_frame();

	/* window draw area */
	pos.x += window_padding;
	pos.y += window_padding + 16;
	size.x -= window_padding * 2;
	size.y -= window_padding * 2 + 16;
	eui_push_frame(pos, size);

	return true;
}

void eui_window_end(void)
{
	eui_pop_frame();
}
