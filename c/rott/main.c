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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"
#include "wad.h"
#include "pixelmap.h"
#include "ray.h"
#include "darkwar.h"

wad_t *wad;
pixelmap_t *palette;
pixelmap_t *color;
int palette_lump;

int main(int argc, char **argv)
{
	/* open darkwar.wad */
	wad = wad_open("darkwar.wad");

	/* allocate pixelmaps */
	palette = pixelmap_allocate(16, 16, PM_TYPE_RGB_888, NULL);
	color = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);

	/* read palette data */
	palette_lump = wad_get_index_from_name(wad, "PAL");
	wad_read_lump(wad, palette_lump, palette->pixels);

	/* render map */
	ray_render(color);

	FILE *file = fopen("color.data", "wb");
	fwrite(color->pixels, 320 * 200, 1, file);
	fclose(file);

	/* free data */
	wad_close(wad);
	pixelmap_free(palette);
	pixelmap_free(color);

	return 0;
}
