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
#include "level.h"

const char lvl_magic[4] = "LVL\0";

level_t *level_load(const char *filename)
{
	FILE *file;
	pixelmap_t *level;
	char magic[4];
	int32_t width, height;

	/* open file */
	file = fopen(filename, "rb");
	if (!file)
		return NULL;

	/* read magic */
	fread(magic, 1, 4, file);
	if (memcmp(magic, lvl_magic, 4) != 0)
		return NULL;

	/* read header */
	fread(&width, 4, 1, file);
	fread(&height, 4, 1, file);

	/* create level */
	level = level_allocate(width, height);

	/* read planes */
	fread(level->planes[0], 2, width * height, file);
	fread(level->planes[1], 2, width * height, file);
	fread(level->planes[2], 2, width * height, file);

	/* close file */
	fclose(file);

	return level;
}

void level_save(level_t *level, const char *filename)
{
	FILE *file;

	/* open file */
	file = fopen(filename, "wb");
	if (!file)
		return;

	/* write header */
	fwrite(lvl_magic, 1, 4, file);
	fwrite(&level->width, 4, 1, file);
	fwrite(&level->height, 4, 1, file);

	/* write planes */
	fwrite(level->planes[0], 2, level->width * level->height, file);
	fwrite(level->planes[1], 2, level->width * level->height, file);
	fwrite(level->planes[2], 2, level->width * level->height, file);

	/* close file */
	fclose(file);
}

level_t *level_allocate(int width, int height)
{
	level_t *level;

	level = calloc(1, sizeof(level_t));
	level->planes[0] = calloc(2, width * height);
	level->planes[1] = calloc(2, width * height);
	level->planes[2] = calloc(2, width * height);

	level->width = width;
	level->height = height;

	return level;
}

void level_free(level_t *level)
{
	if (level)
	{
		if (level->planes[0])
			free(level->planes[0])
		if (level->planes[1])
			free(level->planes[1])
		if (level->planes[2])
			free(level->planes[2])

		free(level);
	}
}
