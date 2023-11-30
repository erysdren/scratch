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
 * Name: RTL Format Module
 *
 * Description: Support for Rise of the Triad level files, with support for the
 * RTL 1.1, RXL 1.1, and RXL 2.0 format versions.
 *
 * Dependencies:
 * - libc
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

/* rott format constants */
static const uint32_t rtl_version = 0x0101;
static const uint32_t rxl_version = 0x0200;
static const uint32_t rle_tag_registered = 0x4344;
static const uint32_t rle_tag_shareware = 0x4d4b;
static const char rtl_magic[4] = {'R', 'T', 'L', '\0'};
static const char rtc_magic[4] = {'R', 'T', 'C', '\0'};
static const char rxl_magic[4] = {'R', 'X', 'L', '\0'};
static const char rxc_magic[4] = {'R', 'X', 'C', '\0'};

/* returns true is this file is a valid rtl */
static bool rtl_is_valid(FILE *file)
{
	char magic[4];
	uint32_t version;

	/* read magic and version */
	fseek(file, 0, SEEK_SET);
	fread(magic, 1, 4, file);
	fread(&version, 4, 1, file);

	/* rott */
	if ((memcmp(magic, rtl_magic, 4) == 0 ||
		memcmp(magic, rtc_magic, 4) == 0) &&
		version <= rtl_version)
		return true;

	/* rott: ludicrous edition */
	if ((memcmp(magic, rxl_magic, 4) == 0 ||
		memcmp(magic, rxc_magic, 4) == 0) &&
		version <= rxl_version)
		return true;

	/* fail */
	return false;
}

/* returns true if this rtl file is from rott: ludicrous edition */
static bool rtl_is_ludicrous(FILE *file)
{
	char magic[4];

	/* read magic */
	fseek(file, 0, SEEK_SET);
	fread(magic, 1, 4, file);

	/* check magics */
	if (memcmp(magic, rxl_magic, 4) == 0 || memcmp(magic, rxc_magic, 4) == 0)
		return true;

	/* nope */
	return false;
}

/* returns true if this rtl file is intended for comm-bat */
static bool rtl_is_commbat(FILE *file)
{
	char read[4];

	fseek(file, 0, SEEK_SET);
	fread(read, 1, 4, file);

	/* singleplayer */
	if (memcmp(read, rtl_magic, 4) == 0 || memcmp(read, rxl_magic, 4) == 0)
		return false;

	/* comm-bat */
	if (memcmp(read, rtc_magic, 4) == 0 || memcmp(read, rxc_magic, 4) == 0)
		return true;

	/* fail */
	return false;
}

/* return offset of map array in rtl file */
static uint32_t rtl_get_map_array_offset(FILE *file)
{
	uint64_t ofs_info_headers;
	uint64_t num_info_headers;
	char info_header_magic[16];
	uint64_t info_header_ofs;
	uint64_t info_header_len;
	int i;

	if (rtl_is_ludicrous(file))
	{
		fseek(file, 8, SEEK_SET);
		fread(&ofs_info_headers, 8, 1, file);
		fread(&num_info_headers, 8, 1, file);

		fseek(file, ofs_info_headers, SEEK_SET);

		for (i = 0; i < num_info_headers; i++)
		{
			fread(info_header_magic, 1, 16, file);
			fread(&info_header_ofs, 8, 1, file);
			fread(&info_header_len, 8, 1, file);

			/* RXL 1.1 provides "MAPSET", RXL 2.0 provides "MAPS" */
			if (strcmp(info_header_magic, "MAPS") == 0 ||
				strcmp(info_header_magic, "MAPSET") == 0)
				return info_header_ofs;
		}
	}

	return 8;
}

/* returns true is this rtl file is intended for shareware  */
static bool rtl_is_shareware(FILE *file)
{
	int i;
	uint32_t map_array_offset;

	map_array_offset = rtl_get_map_array_offset(file);

	for (i = 0; i < RTL_NUM_MAPS; i++)
	{
		uint32_t used;
		uint32_t crc;

		fseek(file, (i * 64) + map_array_offset, SEEK_SET);
		fread(&used, 4, 1, file);
		fread(&crc, 4, 1, file);

		if (used)
		{
			if (crc == rle_tag_registered)
				return false;
			if (crc == rle_tag_shareware)
				return true;
		}
	}

	/* fail */
	return false;
}

/* get number of used maps in rtl file */
static int rtl_get_used_maps(FILE *file)
{
	int i;
	uint32_t map_array_offset;
	int used_maps;

	map_array_offset = rtl_get_map_array_offset(file);

	used_maps = 0;
	for (i = 0; i < RTL_NUM_MAPS; i++)
	{
		uint32_t used;

		fseek(file, (i * 64) + map_array_offset, SEEK_SET);
		fread(&used, 4, 1, file);

		if (used)
			used_maps++;
	}

	return used_maps;
}

/* read plane from rtl file map */
static void rtl_read_plane(FILE *file, int ofs, int len, uint16_t tag, uint16_t *buffer)
{
	/* seek to plane offset */
	fseek(file, ofs, SEEK_SET);

	/* read plane data */
	int pos = 0;
	int written = 0;
	while (pos < len && written < RTL_MAP_PLANE_SIZE)
	{
		/* read test value */
		uint16_t test;
		fread(&test, sizeof(uint16_t), 1, file);

		if (test == tag)
		{
			/* read compressed data */
			uint16_t rle_len, rle_value;
			fread(&rle_len, sizeof(uint16_t), 1, file);
			fread(&rle_value, sizeof(uint16_t), 1, file);

			/* write compressed data */
			for (int r = 0; r < rle_len; r++)
			{
				*buffer = rle_value;
				buffer++;
			}

			written += rle_len * sizeof(uint16_t);
		}
		else
		{
			/* write uncompressed data */
			*buffer = test;
			buffer++;

			written += sizeof(uint16_t);
		}

		pos = ftell(file) - ofs;
	}
}

/* open rtl from filename */
/* returns NULL on error */
rtl_t *rtl_open(const char *filename)
{
	rtl_t *rtl;
	int num_maps;
	uint32_t map_array_offset;
	FILE *file;

	/* sanity check */
	if (filename == NULL)
		return NULL;

	/* open file */
	file = fopen(filename, "rb");
	if (file == NULL)
		return NULL;

	/* check if it's a valid rtl file */
	if (rtl_is_valid(file) == false)
		return NULL;

	/* get number of used maps */
	num_maps = rtl_get_used_maps(file);
	if (num_maps <= 0 || num_maps > RTL_NUM_MAPS)
		return NULL;

	/* allocate rtl format structure */
	rtl = calloc(1, sizeof(rtl_t));
	if (rtl == NULL)
		return NULL;

	/* read map data */
	map_array_offset = rtl_get_map_array_offset(file);
	fseek(file, map_array_offset, SEEK_SET);
	fread(rtl->maps, sizeof(rtl_map_t), RTL_NUM_MAPS, file);

	/* assign values */
	rtl->commbat = rtl_is_commbat(file);
	rtl->ludicrous = rtl_is_ludicrous(file);
	rtl->shareware = rtl_is_shareware(file);
	rtl->file = file;

	/* return success */
	return rtl;
}

/* close rtl and free memory */
void rtl_close(rtl_t *rtl)
{
	if (rtl)
	{
		if (rtl->file != NULL)
			fclose(rtl->file);

		free(rtl);
	}
}

/* get rtl index from name */
/* returns -1 on error */
int rtl_get_index_from_name(rtl_t *rtl, const char *name)
{
	int i;

	/* sanity check */
	if (rtl == NULL || name == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < RTL_NUM_MAPS; i++)
	{
		if (!rtl->maps[i].used)
			continue;

		if (strncmp(rtl->maps[i].name, name, 24) == 0)
			return i;
	}

	/* fail */
	return -1;
}

/* get name from rtl index */
/* returns NULL on error */
const char *rtl_get_name_from_index(rtl_t *rtl, int index)
{
	/* sanity checks */
	if (rtl == NULL || index < 0 || index >= RTL_NUM_MAPS)
		return NULL;
	if (!rtl->maps[index].used)
		return NULL;

	return rtl->maps[index].name;
}

/* read and uncompress map planes into user-provided buffers */
/* each user-provided buffer should be exactly RTL_MAP_PLANE_SIZE in size */
bool rtl_read_map(rtl_t *rtl, int map, void *walls, void *sprites, void *infos)
{
	/* sanity checks */
	if (rtl == NULL || (walls == NULL && sprites == NULL && infos == NULL))
		return false;
	if (rtl->file == NULL || map < 0 || map >= RTL_NUM_MAPS)
		return false;
	if (!rtl->maps[map].used)
		return false;

	if (walls != NULL)
		rtl_read_plane(rtl->file, rtl->maps[map].ofs_walls, rtl->maps[map].len_walls, rtl->maps[map].tag, walls);

	if (sprites != NULL)
		rtl_read_plane(rtl->file, rtl->maps[map].ofs_sprites, rtl->maps[map].len_sprites, rtl->maps[map].tag, sprites);

	if (infos != NULL)
		rtl_read_plane(rtl->file, rtl->maps[map].ofs_infos, rtl->maps[map].len_infos, rtl->maps[map].tag, infos);

	return true;
}
