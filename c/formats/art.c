/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

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
 * Name: ART Format Module
 *
 * Description: Support for the BUILD Engine ART file format.
 *
 * Dependencies:
 * - libc
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "art.h"

/* art format constants */
static const uint32_t art_version = 1;

/* allocate art */
art_t *art_allocate(int num_tiles)
{
	art_t *art;
	art = calloc(1, sizeof(art_t));
	art->num_tiles = num_tiles;
	art->tiles = calloc(num_tiles, sizeof(art_tile_t));
	return art;
}

/* open art from filename */
art_t *art_open(const char *filename)
{
	FILE *file;
	char magic[12];
	grp_t *grp;
	uint32_t num_files;
	uint32_t version;
	int i;

	/* open file */
	file = fopen(filename, "rb");
	if (file == NULL)
		return NULL;

	/* check validity */
	fread(magic, 1, 12, file);
	if (memcmp(magic, grp_magic, 12) != 0)
	{
		fclose(file);
		return NULL;
	}

	/* get number of files */
	fread(&num_files, 4, 1, file);

	/* allocate structure */
	grp = grp_allocate(num_files);

	/* read initial file data */
	for (i = 0; i < num_files; i++)
	{
		fread(grp->files[i].name, 1, 12, file);
		fread(&grp->files[i].len, 4, 1, file);
	}

	/* now go and get file offsets */
	for (i = 0; i < num_files; i++)
	{
		grp->files[i].ofs = ftell(file);
		fseek(file, grp->files[i].len, SEEK_CUR);
	}

	/* assign file pointer */
	grp->file = file;

	return grp;
}

/* close grp and free used memory */
void grp_close(grp_t *grp)
{
	if (grp)
	{
		if (grp->file)
			fclose(grp->file);

		if (grp->files)
			free(grp->files);

		free(grp);
	}
}

/* get file index from name */
int grp_get_index_from_name(grp_t *grp, const char *name)
{
	int i;

	/* sanity check */
	if (grp == NULL || name == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < grp->num_files; i++)
	{
		if (strncmp(grp->files[i].name, name, 12) == 0)
			return i;
	}

	/* fail */
	return -1;
}

/* read file data into buffer */
void *grp_read_chunk(grp_t *grp, int file, void *buffer)
{
	/* sanity check */
	if (grp == NULL || buffer == NULL)
		return NULL;
	if (grp->file == NULL || file < 0 || file >= grp->num_files)
		return NULL;

	/* read file data */
	fseek(grp->file, grp->files[file].ofs, SEEK_SET);
	fread(buffer, grp->files[file].len, 1, grp->file);

	return buffer;
}
