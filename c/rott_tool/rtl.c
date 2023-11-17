
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

/* constants */
#define RTL_VERSION 0x0101
#define RTL_MAX_MAPS 100
static const char rtl_magic[4] = {'R', 'T', 'L', '\0'};
static const char rtc_magic[4] = {'R', 'T', 'C', '\0'};
enum {
	ERR_NONE = 0,
	ERR_MEMORY = 1,
	ERR_FILE = 2,
	ERR_MAGIC = 3,
	ERR_VERSION = 4,
	ERR_MAPS = 5,
	ERR_FILENAME = 6
};
const char *rtl_errors[] = {
	"No error",
	"Couldn't allocate memory",
	"Couldn't find file",
	"Invalid file magic",
	"Invalid file version",
	"File contains no used maps",
	"NULL filename pointer passed to function"
};

/* format enum */
enum { FMT_RTL = 1, FMT_RTC = 2 };

/* read format magic and return enum */
static int rtl_format(FILE *file)
{
	char read[4];

	fseek(file, 0, SEEK_SET);
	fread(read, 1, 4, file);

	if (memcmp(read, rtl_magic, 4) == 0)
		return FMT_RTL;
	else if (memcmp(read, rtc_magic, 4) == 0)
		return FMT_RTC;
	else
		return 0;
}

/* read format version and return it */
static uint32_t rtl_version(FILE *file)
{
	uint32_t version;

	fseek(file, 4, SEEK_SET);
	fread(&version, 1, 4, file);

	return version;
}

/* get number of maps in rtl */
static int rtl_num_maps(FILE *file)
{
	int i;

	for (i = 0; i < RTL_MAX_MAPS; i++)
	{
		uint32_t used;

		fseek(file, (i * 64) + 8, SEEK_SET);
		fread(&used, 1, 4, file);

		if (!used) break;
	}

	return i;
}

/* read plane from map */
static void rtl_read_plane(FILE *file, int ofs, int len, uint16_t tag, uint16_t *buffer)
{
	/* seek to plane offset */
	fseek(file, ofs, SEEK_SET);

	/* read plane data */
	int pos = 0;
	int written = 0;
	while (pos < len && written < RTL_PLANE_SIZE)
	{
		/* read test value */
		uint16_t test;
		fread(&test, 1, sizeof(uint16_t), file);

		if (test == tag)
		{
			/* read compressed data */
			uint16_t rle_len, rle_value;
			fread(&rle_len, 1, sizeof(uint16_t), file);
			fread(&rle_value, 1, sizeof(uint16_t), file);

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

/* read map into structure */
static void rtl_read_map(FILE *file, int i, rtl_map_t *map)
{
	uint32_t used, tag, ofs_walls, ofs_sprites, ofs_infos;
	uint32_t len_walls, len_sprites, len_infos;

	/* get to map header */
	fseek(file, (i * 64) + 8, SEEK_SET);

	/* read data */
	fread(&used, 1, sizeof(uint32_t), file);
	fread(&map->crc, 1, sizeof(uint32_t), file);
	fread(&tag, 1, sizeof(uint32_t), file);
	fread(&map->flags, 1, sizeof(uint32_t), file);
	fread(&ofs_walls, 1, sizeof(uint32_t), file);
	fread(&ofs_sprites, 1, sizeof(uint32_t), file);
	fread(&ofs_infos, 1, sizeof(uint32_t), file);
	fread(&len_walls, 1, sizeof(uint32_t), file);
	fread(&len_sprites, 1, sizeof(uint32_t), file);
	fread(&len_infos, 1, sizeof(uint32_t), file);
	fread(&map->name, 1, 24, file);

	/* allocate planes */
	map->walls = calloc(1, RTL_PLANE_SIZE);
	map->sprites = calloc(1, RTL_PLANE_SIZE);
	map->infos = calloc(1, RTL_PLANE_SIZE);

	/* check for memory allocation error */
	if (map->walls == NULL || map->sprites == NULL || map->infos == NULL)
		return;

	/* read planes */
	rtl_read_plane(file, ofs_walls, len_walls, tag, map->walls);
	rtl_read_plane(file, ofs_sprites, len_sprites, tag, map->sprites);
	rtl_read_plane(file, ofs_infos, len_infos, tag, map->infos);
}

/* free map data */
void rtl_free(rtl_t *rtl)
{
	if (rtl->num_maps && rtl->maps != NULL)
	{
		for (int i = 0; i < rtl->num_maps; i++)
		{
			if (rtl->maps[i].walls) free(rtl->maps[i].walls);
			if (rtl->maps[i].sprites) free(rtl->maps[i].sprites);
			if (rtl->maps[i].infos) free(rtl->maps[i].infos);
		}

		free(rtl->maps);
	}
}

/* load RTL or RTC from filename */
bool rtl_load(const char *filename, rtl_t *rtl)
{
	/* oops */
	if (rtl == NULL)
		return false;
	if (filename == NULL)
	{
		rtl->error = rtl_errors[ERR_FILENAME];
		return false;
	}

	/* default state */
	memset(rtl, 0, sizeof(rtl_t));
	rtl->error = rtl_errors[ERR_NONE];

	/* open file */
	FILE *file = fopen(filename, "rb");
	if (file == NULL)
	{
		/* couldn't find file */
		rtl->error = rtl_errors[ERR_FILE];
		return false;
	}

	/* check format */
	switch (rtl_format(file))
	{
		/* singleplayer maps */
		case FMT_RTL:
			rtl->commbat = false;
			break;

		/* comm-bat maps */
		case FMT_RTC:
			rtl->commbat = true;
			break;

		/* incorrect format */
		default:
			rtl->error = rtl_errors[ERR_MAGIC];
			return false;
	}

	/* check version */
	if (rtl_version(file) != RTL_VERSION)
	{
		rtl->error = rtl_errors[ERR_VERSION];
		return false;
	}

	/* get number of used maps */
	rtl->num_maps = rtl_num_maps(file);
	if (rtl->num_maps == 0)
	{
		rtl->error = rtl_errors[ERR_MAPS];
		return false;
	}

	/* now allocate map structures */
	rtl->maps = calloc(rtl->num_maps, sizeof(rtl_map_t));
	if (rtl->maps == NULL)
	{
		rtl->error = rtl_errors[ERR_MEMORY];
		return false;
	}

	/* read map data */
	for (int i = 0; i < rtl->num_maps; i++)
	{
		rtl_read_map(file, i, &rtl->maps[i]);

		/* check for failed memory allocation */
		if (rtl->maps[i].walls == NULL ||
			rtl->maps[i].sprites == NULL ||
			rtl->maps[i].infos == NULL)
		{
			rtl->error = rtl_errors[ERR_MEMORY];
			return false;
		}
	}

	/* return success */
	return true;
}
