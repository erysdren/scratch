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

#include "wad.h"

/* wad constants */
static const char iwad_magic[4] = {'I', 'W', 'A', 'D'};
static const char pwad_magic[4] = {'P', 'W', 'A', 'D'};

/* returns true if it's a valid wad */
static bool wad_is_valid(FILE *file)
{
	char magic[4];

	/* read magic */
	fseek(file, 0, SEEK_SET);
	fread(magic, 1, 4, file);

	/* valid iwad or pwad */
	if (memcmp(magic, iwad_magic, 4) == 0 ||
		memcmp(magic, pwad_magic, 4) == 0)
		return true;

	/* fail */
	return false;
}

/* returns size of lump array in wad */
static uint32_t wad_get_lump_array_size(FILE *file)
{
	uint32_t size;

	/* read size */
	fseek(file, 4, SEEK_SET);
	fread(&size, 4, 1, file);

	return size;
}

/* returns offset of lump array in wad */
static uint32_t wad_get_lump_array_offset(FILE *file)
{
	uint32_t ofs;

	/* read ofs */
	fseek(file, 8, SEEK_SET);
	fread(&ofs, 4, 1, file);

	return ofs;
}

/* allocate wad */
wad_t *wad_allocate(int num_lumps)
{
	wad_t *wad;

	/* sanity check */
	if (num_lumps <= 0)
		return NULL;

	/* do calloc */
	wad = calloc(1, sizeof(wad_t));
	if (wad == NULL)
		return NULL;

	/* set values */
	wad->num_lumps = num_lumps;

	/* do calloc */
	wad->lumps = calloc(wad->num_lumps, sizeof(wad_lump_t));
	if (wad->lumps == NULL)
		return NULL;

	/* give back ptr */
	return wad;
}

/* open wad handle from filename */
wad_t *wad_open(const char *filename)
{
	wad_t *wad;
	uint32_t num_lumps;
	uint32_t ofs_lumps;
	FILE *file;

	/* sanity check */
	if (filename == NULL)
		return NULL;

	/* open file */
	file = fopen(filename, "rb");
	if (file == NULL)
		return NULL;

	/* test validity */
	if (wad_is_valid(file) == false)
		return NULL;

	/* get number of lumps */
	num_lumps = wad_get_lump_array_size(file);
	if (num_lumps <= 0)
		return NULL;

	/* get offset of lumps */
	ofs_lumps = wad_get_lump_array_offset(file);

	/* allocate wad */
	wad = wad_allocate(num_lumps);
	if (wad == NULL)
		return NULL;

	/* read lumps */
	fseek(file, ofs_lumps, SEEK_SET);
	fread(wad->lumps, sizeof(wad_lump_t), wad->num_lumps, file);

	/* set values */
	wad->file = file;

	/* return success */
	return wad;
}

/* close wad handle */
void wad_close(wad_t *wad)
{
	if (wad)
	{
		/* close file handle */
		if (wad->file)
			fclose(wad->file);

		/* free lump array */
		if (wad->num_lumps > 0 && wad->lumps != NULL)
			free(wad->lumps);

		free(wad);
	}
}

/* get wad index from name */
int wad_get_index_from_name(wad_t *wad, const char *name)
{
	int i;

	/* sanity check */
	if (wad == NULL || name == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < wad->num_lumps; i++)
	{
		if (strncmp(wad->lumps[i].name, name, 8) == 0)
			return i;
	}

	/* fail */
	return -1;
}

/* get name from wad index */
const char *wad_get_name_from_index(wad_t *wad, int index)
{
	/* sanity check */
	if (index < 0 || index >= wad->num_lumps)
		return NULL;

	return wad->lumps[index].name;
}

/* read lump data into buffer */
void *wad_read_lump(wad_t *wad, int lump, void *buffer)
{
	/* sanity check */
	if (wad == NULL || buffer == NULL)
		return NULL;
	if (wad->file == NULL || lump < 0 || lump >= wad->num_lumps)
		return NULL;

	/* read lump data */
	fseek(wad->file, wad->lumps[lump].ofs, SEEK_SET);
	fread(buffer, wad->lumps[lump].len, 1, wad->file);

	return buffer;
}
