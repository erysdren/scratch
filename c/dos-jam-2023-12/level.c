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
	level_t *level;
	char magic[4];
	int32_t width, height, num_planes;
	int i;

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
	fread(&num_planes, 4, 1, file);

	/* create level */
	level = level_allocate(width, height, num_planes);

	/* read planes */
	for (i = 0; i < num_planes; i++)
		fread(level->planes[i], 2, width * height, file);

	/* close file */
	fclose(file);

	return level;
}

void level_save(level_t *level, const char *filename)
{
	FILE *file;
	int i;

	/* open file */
	file = fopen(filename, "wb");
	if (!file)
		return;

	/* write header */
	fwrite(lvl_magic, 1, 4, file);
	fwrite(&level->width, 4, 1, file);
	fwrite(&level->height, 4, 1, file);
	fwrite(&level->num_planes, 4, 1, file);

	/* write planes */
	for (i = 0; i < level->num_planes; i++)
		fwrite(level->planes[i], 2, level->width * level->height, file);

	/* close file */
	fclose(file);
}

level_t *level_allocate(int width, int height, int num_planes)
{
	level_t *level;
	int i;

	if (!width || !height || !num_planes)
		return NULL;

	level = calloc(1, sizeof(level_t));
	level->planes = calloc(num_planes, sizeof(uint16_t *));

	for (i = 0; i < num_planes; i++)
		level->planes[i] = calloc(2, width * height);

	level->width = width;
	level->height = height;
	level->num_planes = num_planes;

	return level;
}

void level_free(level_t *level)
{
	int i;

	if (level)
	{
		if (level->planes)
		{
			for (i = 0; i < level->num_planes; i++)
				free(level->planes[i]);

			free(level->planes);
		}

		free(level);
	}
}
