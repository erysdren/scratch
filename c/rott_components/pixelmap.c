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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "math.h"
#include "pixelmap.h"

/* allocate pixelmap */
pixelmap_t *pixelmap_allocate(int width, int height, int type, void *buffer)
{
	/* allocate pixelmap */
	pixelmap_t *pixelmap = calloc(1, sizeof(pixelmap_t));

	/* get bpp */
	switch (type)
	{
		case PM_TYPE_INDEX_8:
			pixelmap->bpp = 8;
			break;

		case PM_TYPE_DEPTH_16:
		case PM_TYPE_RGB_565:
			pixelmap->bpp = 16;
			break;

		case PM_TYPE_RGB_888:
			pixelmap->bpp = 24;
			break;

		case PM_TYPE_DEPTH_32:
		case PM_TYPE_RGBA_8888:
			pixelmap->bpp = 32;
			break;

		default:
			return NULL;
	}

	/* calculate stride */
	pixelmap->stride = width * (pixelmap->bpp / 8);

	/* setup structure data */
	pixelmap->width = width;
	pixelmap->height = height;
	pixelmap->pixels = buffer != NULL ? buffer : calloc(height, pixelmap->stride);
	pixelmap->shared = buffer != NULL;
	pixelmap->scanlines.b = calloc(height, sizeof(void *));

	/* calculate scanline pointers */
	while (height--)
		pixelmap->scanlines.b[height] = (uint8_t *)pixelmap->pixels + pixelmap->stride * height;

	return pixelmap;
}

/* free pixelmap */
void pixelmap_free(pixelmap_t *pixelmap)
{
	if (!pixelmap)
		return;

	if (!pixelmap->shared)
		free(pixelmap->pixels);

	if (pixelmap->scanlines.b)
		free(pixelmap->scanlines.b);

	free(pixelmap);
}

/* clear pixelmap with colour */
void pixelmap_clear8(pixelmap_t *pixelmap, uint8_t color)
{
	memset(pixelmap->pixels, color, pixelmap->stride * pixelmap->height);
}

/* draw pixelmap on another */
void pixelmap_draw8(pixelmap_t *dst, pixelmap_t *src, int x, int y, int mode)
{
	pixelmap_blit8(dst, x, y, x + src->width, y + src->height, src, 0, 0, src->width, src->height, mode);
}

/* blit pixelmap from one to another */
void pixelmap_blit8(pixelmap_t *dst, int x1, int y1, int x2, int y2, pixelmap_t *src, int u1, int v1, int u2, int v2,
					int mode)
{
	int w, h, u, uu, vv;

	if ((w = x2 - x1) <= 0 || (h = y2 - y1) <= 0)
		return;

	u1 = FIX32(u1);
	v1 = FIX32(v1);
	u2 = FIX32(u2);
	v2 = FIX32(v2);

	uu = (u2 - u1) / w;
	vv = (v2 - v1) / h;

	if (x1 < 0)
	{
		u1 -= x1 * uu;
		x1 = 0;
	}
	if (y1 < 0)
	{
		v1 -= y1 * vv;
		y1 = 0;
	}
	if (x2 > dst->width)
	{
		x2 = dst->width;
	}
	if (y2 > dst->height)
	{
		y2 = dst->height;
	}

	if ((w = x2 - x1) <= 0 || (h = y2 - y1) <= 0)
		return;

	switch (mode)
	{
		/* straight copy */
		case PM_MODE_COPY: {
			if (uu == FIX32(1))
			{
				for (; y1 < y2; y1++, v1 += vv)
				{
					memcpy(&dst->scanlines.b[y1][x1], &src->scanlines.b[FIX32_TO_INT(v1)][FIX32_TO_INT(u1)],
								x2 - x1);
				}
			}
			else
			{
				for (; y1 < y2; y1++, v1 += vv)
				{

					uint8_t *I = src->scanlines.b[FIX32_TO_INT(v1)];
					uint8_t *O = &dst->scanlines.b[y1][x1];

					for (w = x2 - x1, u = u1; w--; u += uu, O++)
					{
						*O = I[FIX32_TO_INT(u)];
					}
				}
			}
		}

		/* colorkey */
		case PM_MODE_COLORKEY: {
			uint8_t pen = 0;
			for (; y1 < y2; y1++, v1 += vv)
			{
				uint8_t *I = src->scanlines.b[FIX32_TO_INT(v1)];
				uint8_t *O = &dst->scanlines.b[y1][x1];

				for (w = x2 - x1, u = u1; w--; u += uu, O++)
				{
					if ((pen = I[FIX32_TO_INT(u)]) != 255)
						*O = pen;
				}
			}
		}
	}
}

/* copy pixelmap to another */
void pixelmap_copy(pixelmap_t *dst, pixelmap_t *src)
{
	pixelmap_assert_same(dst, src);
	memcpy(dst->pixels, src->pixels, src->height * src->stride);
}

/* flip pixelmap to another */
void pixelmap_flip8(pixelmap_t *dst, pixelmap_t *src)
{
	int x, y1, y2;

	pixelmap_assert_same(dst, src);

	for (y1 = 0, y2 = dst->height - 1; y1 < y2; y1++, y2--)
	{
		uint8_t *s1 = src->scanlines.b[y1];
		uint8_t *s2 = src->scanlines.b[y2];
		uint8_t *d1 = dst->scanlines.b[y1];
		uint8_t *d2 = dst->scanlines.b[y2];

		for (x = dst->width; x--;)
		{
			uint8_t tmp = *s1++;
			*d1++ = *s2++;
			*d2++ = tmp;
		}
	}
}

/* liquid effects */
void pixelmap_liquid8(pixelmap_t *dst, pixelmap_t *src, uint64_t tick)
{
	int y;
	for (y = dst->height; y--;)
	{
		int x = FIX32_SIN(y * 32 + tick * 5) >> 13;

		pixelmap_blit8(dst, x, y, x + dst->width, y + 1, src, 0, y, src->width, y + 1, PM_MODE_COPY);
		pixelmap_blit8(dst, x - dst->width, y, x, y + 1, src, 0, y, src->width, y + 1, PM_MODE_COPY);
		pixelmap_blit8(dst, x + dst->width, y, x + dst->width + dst->width, y + 1, src, 0, y, src->width, y + 1,
					PM_MODE_COPY);
	}
}

/* assert if pixelmaps are the same */
void pixelmap_assert_same(pixelmap_t *dst, pixelmap_t *src)
{
	assert(dst && src);
	assert(dst->width == src->width);
	assert(dst->height == src->height);
	assert(dst->bpp == src->bpp);
}

/* blend */
void pixelmap_blend8(pixelmap_t *dst, pixelmap_t *src1, pixelmap_t *src2, pixelmap_t *clut)
{
	int x, y;

	for (y = dst->height; y--;)
	{
		uint8_t *a = dst->scanlines.b[y];
		uint8_t *b = src1->scanlines.b[y];
		uint8_t *c = src2->scanlines.b[y];

		for (x = dst->width; x--;)
		{
			*a++ = clut->pixels[*b++ * clut->width + *c++];
		}
	}
}

/* generate clut */
pixelmap_t *pixelmap_generate_clut(pixelmap_t *palette)
{
	int x, y, r, g, b;
	pixelmap_t *clut;

	clut = pixelmap_allocate(256, 256, PM_TYPE_INDEX_8, NULL);

	for (x = 0; x < clut->width; x++)
	{
		for (y = 0; y < clut->height; y++)
		{
			r = (palette->pixels[x * 3] + palette->pixels[y * 3]) >> 1;
			g = (palette->pixels[x * 3 + 1] + palette->pixels[y * 3 + 1]) >> 1;
			b = (palette->pixels[x * 3 + 2] + palette->pixels[y * 3 + 2]) >> 1;

			clut->pixels[y * clut->width + x] = (uint8_t)palette_search(palette, r, g, b);
		}
	}

	return clut;
}

/* generate lightmap */
pixelmap_t *pixelmap_generate_lightmap(pixelmap_t *palette, int brightness)
{
	int fr = 0;
	int fg = 0;
	int fb = 0;
	int i, j;
	int r, g, b;
	pixelmap_t *lm = pixelmap_allocate(256, 32, PM_TYPE_INDEX_8, NULL);

	for (i = 0; i < lm->height; i++)
	{
		for (j = 0; j < lm->width; j++)
		{
			r = imin(imuldiv(fr + imuldiv(palette->pixels[i * 3] - fr, j, 31), brightness * 4, 31), 255);
			g = imin(imuldiv(fg + imuldiv(palette->pixels[i * 3 + 1] - fg, j, 31), brightness * 4, 31), 255);
			b = imin(imuldiv(fb + imuldiv(palette->pixels[i * 3 + 2] - fb, j, 31), brightness * 4, 31), 255);

			lm->pixels[i * lm->width + j] = palette_search(palette, r, g, b);
		}
	}

	return lm;
}

/* search in palette */
int palette_search(pixelmap_t *palette, int r, int g, int b)
{
	int i, pen = 0, dist = INT32_MAX;

	for (i = 256; i--;)
	{
		int rank = isqr(palette->pixels[i * 3] - r) + isqr(palette->pixels[(i * 3) + 1] - g) + isqr(palette->pixels[(i * 3) + 2] - b);

		if (rank < dist)
		{
			pen = i;
			dist = rank;
		}
	}

	return pen;
}

/* bresenham's line drawing */
void pixelmap_line8(pixelmap_t *dst, int x1, int y1, int x2, int y2, uint8_t color)
{
	int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

	dx = x2 - x1; /* the horizontal distance of the line */
	dy = y2 - y1; /* the vertical distance of the line */
	dxabs = abs(dx);
	dyabs = abs(dy);
	sdx = sgn(dx);
	sdy = sgn(dy);
	x = dyabs >> 1;
	y = dxabs >> 1;
	px = x1;
	py = y1;

	pixelmap_pixel8(dst, px, py) = color;

	if (dxabs >= dyabs) /* the line is more horizontal than vertical */
	{
		for (i = 0; i < dxabs; i++)
		{
			y += dyabs;
			if (y >= dxabs)
			{
				y -= dxabs;
				py += sdy;
			}
			px += sdx;
			if (px < 0 || px >= dst->width || py < 0 || py >= dst->height)
				break;
			pixelmap_pixel8(dst, px, py) = color;
		}
	}
	else /* the line is more vertical than horizontal */
	{
		for (i = 0; i < dyabs; i++)
		{
			x += dxabs;
			if (x >= dyabs)
			{
				x -= dyabs;
				px += sdx;
			}
			py += sdy;
			if (px < 0 || px >= dst->width || py < 0 || py >= dst->height)
				break;
			pixelmap_pixel8(dst, px, py) = color;
		}
	}
}

/* rectangle */
void pixelmap_rect8(pixelmap_t *dst, int x, int y, int w, int h, uint8_t color)
{
	int i, top, bottom, left, right;

	/* sanity check */
	if (!w || !h)
		return;

	/* assign values */
	top = y;
	bottom = y + h;
	left = x;
	right = x + w;

	/* draw horizontal lines */
	for (i = left; i < right; i++)
	{
		if (i < 0 || i >= dst->width)
			continue;

		pixelmap_pixel8(dst, i, top) = color;
		pixelmap_pixel8(dst, i, bottom) = color;
	}

	/* draw vertical lines */
	for (i = top; i < bottom; i++)
	{
		if (i < 0 || i >= dst->height)
			continue;

		pixelmap_pixel8(dst, left, i) = color;
		pixelmap_pixel8(dst, right, i) = color;
	}
}
