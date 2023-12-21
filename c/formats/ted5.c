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
 * Name: TED5 Format Module
 *
 * Description: Support for the TED5 level format, used by various games that
 * utilized id Software's tile-based engines.
 *
 * Dependencies:
 * - Carmack
 * - RLEW
 * - libc
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ted5.h"
#include "rlew.h"

/* ted5 format constants */
static const char ted5_magic[8] = "TED5v1.0";
static const uint16_t ted5_tag = 0xABCD;

/* returns true if the file is a valid MAPTEMP file */
static bool file_is_maptemp(FILE *file)
{
	char magic[8];

	fseek(file, 0, SEEK_SET);

	fread(magic, 1, 8, file);

	if (memcmp(ted5_magic, magic, 8) == 0)
		return true;

	return false;
}

/* returns true if the file is a valid MAPHEAD file */
static bool file_is_maphead(FILE *file)
{
	uint16_t read;

	fseek(file, 0, SEEK_SET);

	fread(&read, 2, 1, file);

	if (read == ted5_tag)
		return true;

	return false;
}

/* check if map plane is carmackized */
static bool plane_is_carmackized(ted5_t *ted5, int map, int plane)
{
	uint16_t read;

	/* seek to plane */
	fseek(ted5->files.maptemp, ted5->maps[map].ofs_planes[plane], SEEK_SET);
	fread(&read, 2, 1, ted5->files.maptemp);

	/* if it doesn't match the expeceted size, it might be carmackized */
	if (read != ted5->maps[map].width * ted5->maps[map].height * 2)
	{
		/* read the next word */
		fread(&read, 2, 1, ted5->files.maptemp);

		/* if it matches the expected plane size, then its carmackized */
		if (read == ted5->maps[map].width * ted5->maps[map].height * 2)
			return true;
	}

	return false;
}

/* create ted5 struct from MAPHEAD and MAPTEMP files */
ted5_t *ted5_open(const char *maphead, const char *maptemp)
{
	ted5_t *ted5;
	int i;

	/* allocate structure */
	ted5 = calloc(1, sizeof(ted5_t));
	if (!ted5)
		return NULL;

	/* open files */
	ted5->files.maphead = fopen(maphead, "rb");
	ted5->files.maptemp = fopen(maptemp, "rb");
	if (!ted5->files.maphead || !ted5->files.maptemp)
	{
		ted5_close(ted5);
		return NULL;
	}

	/* check signatures in input files */
	if (!file_is_maptemp(ted5->files.maptemp) || !file_is_maphead(ted5->files.maphead))
	{
		ted5_close(ted5);
		return NULL;
	}

	/* reset file pointers */
	fseek(ted5->files.maphead, 0, SEEK_SET);
	fseek(ted5->files.maptemp, 0, SEEK_SET);

	/* read RLEW tag from head */
	fread(&ted5->tag, 2, 1, ted5->files.maphead);

	/* process map data */
	for (i = 0; i < TED5_NUM_MAPS; i++)
	{
		int32_t ofs_map;

		/* read map offset from head file */
		fseek(ted5->files.maphead, (i * 4) + 2, SEEK_SET);
		fread(&ofs_map, 4, 1, ted5->files.maphead);

		/* invalid values */
		if (ofs_map <= 0)
			continue;

		/* read header data from disk */
		fseek(ted5->files.maptemp, ofs_map, SEEK_SET);
		fread(&ted5->maps[i], sizeof(ted5_map_t), 1, ted5->files.maptemp);
	}

	return ted5;
}

/* close ted5 map and free memory */
void ted5_close(ted5_t *ted5)
{
	if (ted5)
	{
		if (ted5->files.maphead)
			fclose(ted5->files.maphead);

		if (ted5->files.maptemp)
			fclose(ted5->files.maptemp);

		free(ted5);
	}
}

/* get size (in bytes) of a given map's plane, for memory allocation */
/* returns 0 on error */
uint32_t ted5_get_plane_size(ted5_t *ted5, int map, int plane)
{
	uint16_t read;

	/* sanity checks */
	if (!ted5 || map < 0 || map >= TED5_NUM_MAPS || plane < 0 || plane >= TED5_NUM_PLANES)
		return 0;

	/* check if map and plane is valid */
	if (ted5->maps[map].ofs_planes[plane] <= 0)
		return 0;

	/* seek to plane */
	fseek(ted5->files.maptemp, ted5->maps[map].ofs_planes[plane], SEEK_SET);
	fread(&read, 2, 1, ted5->files.maptemp);

	/* if this doesn't match the expected value, then map is carmackized */
	if (read != ted5->maps[map].width * ted5->maps[map].height * 2)
	{
		/* read the next word */
		fread(&read, 2, 1, ted5->files.maptemp);

		/* if it still doesn't match expected size, then something is wrong */
		if (read != ted5->maps[map].width * ted5->maps[map].height * 2)
			return 0;
	}

	/* return the size of plane */
	return read;
}

/* read map planes into user-allocated buffers */
/* allocated buffer size should be determined with ted5_get_plane_size() */
bool ted5_read_plane(ted5_t *ted5, int map, int plane, void *buffer)
{
	/* sanity checks */
	if (!ted5 || map < 0 || map >= TED5_NUM_MAPS || plane < 0 || plane >= TED5_NUM_PLANES || buffer == NULL)
		return false;

	/* we can't do carmackization yet */
	if (plane_is_carmackized(ted5, map, plane))
		return false;

	/* allocate and read plane */
	void *planebuf = calloc(1, ted5->maps[map].len_planes[plane]);
	fseek(ted5->files.maptemp, ted5->maps[map].ofs_planes[plane], SEEK_SET);
	fread(planebuf, ted5->maps[map].len_planes[plane], 1, ted5->files.maptemp);

	/* do plane reading */
	rlew_uncompress(
		planebuf,
		ted5->maps[map].len_planes[plane],
		ted5->tag,
		buffer,
		ted5_get_plane_size(ted5, map, plane)
	);

	free(planebuf);

	return true;
}

/* get map index from name */
/* returns -1 on error */
int ted5_get_map_from_name(ted5_t *ted5, const char *name)
{
	int i;

	/* sanity check */
	if (ted5 == NULL || name == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < TED5_NUM_MAPS; i++)
	{
		if (strncmp(ted5->maps[i].name, name, 16) == 0)
			return i;
	}

	/* fail */
	return -1;
}
