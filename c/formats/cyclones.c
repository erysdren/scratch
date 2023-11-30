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
 * Name: CyClones Format Module
 *
 * Description: Support for the CyClones (1994) data storage file format.
 *
 * Dependencies:
 * - libc
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cyclones.h"

/* get number of chunks in cyfile */
static int get_num_chunks(FILE *file)
{
	char name[4];
	uint16_t type;
	uint32_t len;
	int r = 0;

	fseek(file, 0, SEEK_SET);

	/* loop through chunks */
	while (fread(name, 1, 4, file) == 4)
	{
		fread(&type, 2, 1, file);
		fread(&len, 4, 1, file);
		fseek(file, len, SEEK_CUR);
		r++;
	}

	return r;
}

/* allocate cyfile */
cyfile_t *cyfile_allocate(int num_chunks)
{
	cyfile_t *cyfile;
	cyfile = calloc(1, sizeof(cyfile_t));
	cyfile->num_chunks = num_chunks;
	cyfile->chunks = calloc(num_chunks, sizeof(cychunk_t));
	return cyfile;
}

/* open cyfile from filename */
cyfile_t *cyfile_open(const char *filename)
{
	FILE *file;
	cyfile_t *cyfile;
	int num_chunks;
	int i;

	/* open file */
	file = fopen(filename, "rb");
	if (file == NULL)
		return NULL;

	/* get number of chunks */
	num_chunks = get_num_chunks(file);

	/* allocate structure */
	cyfile = cyfile_allocate(num_chunks);

	/* read chunk data */
	fseek(file, 0, SEEK_SET);
	for (i = 0; i < num_chunks; i++)
	{
		fread(cyfile->chunks[i].name, 1, 4, file);
		fread(&cyfile->chunks[i].type, 2, 1, file);
		fread(&cyfile->chunks[i].len, 4, 1, file);
		cyfile->chunks[i].ofs = ftell(file);
		fseek(file, cyfile->chunks[i].len, SEEK_CUR);
	}

	/* assign file pointer */
	cyfile->file = file;

	return cyfile;
}

/* close cyfile and free used memory */
void cyfile_close(cyfile_t *cyfile)
{
	if (cyfile)
	{
		if (cyfile->file)
			fclose(cyfile->file);

		if (cyfile->chunks)
			free(cyfile->chunks);

		free(cyfile);
	}
}

/* get chunk index from name */
int cyfile_get_index_from_name(cyfile_t *cyfile, const char *name)
{
	int i;

	/* sanity check */
	if (cyfile == NULL || name == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < cyfile->num_chunks; i++)
	{
		if (strncmp(cyfile->chunks[i].name, name, 4) == 0)
			return i;
	}

	/* fail */
	return -1;
}

/* read chunk data into buffer */
void *cyfile_read_chunk(cyfile_t *cyfile, int chunk, void *buffer)
{
	/* sanity check */
	if (cyfile == NULL || buffer == NULL)
		return NULL;
	if (cyfile->file == NULL || chunk < 0 || chunk >= cyfile->num_chunks)
		return NULL;

	/* read chunk data */
	fseek(cyfile->file, cyfile->chunks[chunk].ofs, SEEK_SET);
	fread(buffer, cyfile->chunks[chunk].len, 1, cyfile->file);

	return buffer;
}
