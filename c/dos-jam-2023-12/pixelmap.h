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
#ifndef _PIXELMAP_H_
#define _PIXELMAP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* pixelmap type */
enum {
	/* color */
	PM_TYPE_INDEX_8, /* 8 bits per pixel */
	PM_TYPE_RGB_565, /* 16 bits per pixel */
	PM_TYPE_RGB_888, /* 24 bits per pixel */
	PM_TYPE_RGBA_8888, /* 32 bits per pixel */

	/* depth */
	PM_TYPE_DEPTH_16, /* 16 bits per pixel */
	PM_TYPE_DEPTH_32 /* 32 bits per pixel */
};

/* copy mode */
enum {
	PM_MODE_COPY,
	PM_MODE_COLORKEY
};

/* scanlines union */
typedef union scanlines_t {
	uint8_t **b;
	uint16_t **w;
	uint32_t **l;
} scanlines_t;

/* pixelmap structure */
typedef struct pixelmap_t {
	int32_t type; /* type enum */
	int32_t width; /* width of picture in pixels */
	int32_t height; /* height of picture in pixels */
	int32_t bpp; /* bits per pixel */
	int32_t stride; /* bytes per row. rows are 4 byte aligned */
	int32_t shared; /* false if buffer is owned */
	uint8_t *pixels; /* allocated pixel buffer */
	scanlines_t scanlines; /* pre-calculated scanline pointers */
} pixelmap_t;

/* creation and destruction */
pixelmap_t *pixelmap_allocate(int width, int height, int type, void *buffer);
void pixelmap_free(pixelmap_t *pixelmap);

/* copy */
void pixelmap_copy(pixelmap_t *dst, pixelmap_t *src);

/* utilities */
void pixelmap_assert_same(pixelmap_t *dst, pixelmap_t *src);
int palette_search(pixelmap_t *palette, int r, int g, int b);
pixelmap_t *pixelmap_generate_clut(pixelmap_t *palette);
pixelmap_t *pixelmap_generate_lightmap(pixelmap_t *palette, int brightness);

/* bpp-specific */
void pixelmap_clear8(pixelmap_t *pixelmap, uint8_t color);
void pixelmap_draw8(pixelmap_t *dst, pixelmap_t *src, int x, int y, int mode);
void pixelmap_blit8(pixelmap_t *dst, int x1, int y1, int x2, int y2, pixelmap_t *src, int u1, int v1, int u2, int v2, int mode);
void pixelmap_flip8(pixelmap_t *dst, pixelmap_t *src);
void pixelmap_liquid8(pixelmap_t *dst, pixelmap_t *src, uint64_t tick);
void pixelmap_blend8(pixelmap_t *dst, pixelmap_t *src1, pixelmap_t *src2, pixelmap_t *clut);
void pixelmap_line8(pixelmap_t *dst, int x1, int y1, int x2, int y2, uint8_t color);
void pixelmap_rect8(pixelmap_t *dst, int x, int y, int w, int h, uint8_t color);
#define pixelmap_pixel8(p, x, y) (p)->pixels[(y) * (p)->width + (x)]

#ifdef __cplusplus
}
#endif
#endif /* _PIXELMAP_H_ */
