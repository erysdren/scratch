
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

/* constants */
#define RTL_MAX_MAPS 100
static uint32_t rtl_version = 0x0101;
static uint32_t rtl_tag = 0x4344;
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
	"Couldn't open file",
	"Invalid file magic",
	"Invalid file version",
	"File contains no used maps",
	"NULL filename pointer passed to function"
};

/* format enum */
enum { FMT_RTL = 1, FMT_RTC = 2 };

/* read format magic and return enum */
static int rtl_get_format(FILE *file)
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
static uint32_t rtl_get_version(FILE *file)
{
	uint32_t version;

	fseek(file, 4, SEEK_SET);
	fread(&version, 1, 4, file);

	return version;
}

/* get number of maps in rtl */
static int rtl_get_num_maps(FILE *file)
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

/* compress and write plane with run-length encoding */
static uint32_t rtl_write_plane(FILE *file, uint16_t *plane, uint16_t tag)
{
	uint32_t startpos = ftell(file);
	int read = 0;
	uint16_t count;

	/* compress and write source data */
	while (read < RTL_PLANE_SIZE)
	{
		count = 1;

		/* read word from source */
		uint16_t value = *plane++;
		read++;

		/* count repetitions */
		while (*plane == value && read < RTL_PLANE_SIZE)
		{
			count++; /* repetitions */
			plane++; /* source data */
			read++; /* total number of bytes read */
		}

		/* if more than 3 repetitions, or the value is the same as the tag */
		if (count > 3 || value == tag)
		{
			fwrite(&tag, 2, 1, file); /* tag */
			fwrite(&count, 2, 1, file); /* repetitions */
			fwrite(&value, 2, 1, file); /* value */
		}
		else
		{
			/* otherwise write out the read values */
			for (int i = 0; i < count; i++)
			{
				fwrite(&value, 2, 1, file);
			}
		}
	}

	return ftell(file) - startpos;
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

/* crc generator */
#define FNV_OFFSET 2166136261UL
#define FNV_PRIME 16777619UL
static uint32_t rtl_hash(void *buf, int len)
{
	uint32_t hash = FNV_OFFSET;

	for (int i = 0; i < len; i++)
	{
		hash ^= (uint32_t)((uint8_t *)buf)[i];
		hash *= FNV_PRIME;
	}

	return hash;
}

/* generate crc for all maps */
bool rtl_generate_crc(rtl_t *rtl)
{
	for (int i = 0; i < rtl->num_maps; i++)
	{
		rtl->maps[i].crc = rtl_hash(rtl->maps[i].walls, RTL_PLANE_SIZE);
		rtl->maps[i].crc ^= rtl_hash(rtl->maps[i].sprites, RTL_PLANE_SIZE);
		rtl->maps[i].crc ^= rtl_hash(rtl->maps[i].infos, RTL_PLANE_SIZE);
	}

	return true;
}

/* allocate RTL/RTC in memory */
bool rtl_allocate(int num_maps, bool commbat, rtl_t *rtl)
{
	/* oops */
	if (rtl == NULL)
		return false;
	if (num_maps <= 0 || num_maps > RTL_MAX_MAPS)
		return false;

	/* default state */
	memset(rtl, 0, sizeof(rtl_t));
	rtl->error = rtl_errors[ERR_NONE];

	/* set values */
	rtl->num_maps = num_maps;
	rtl->commbat = commbat;

	/* allocate maps */
	rtl->maps = calloc(rtl->num_maps, sizeof(rtl_map_t));
	if (rtl->maps == NULL)
	{
		rtl->error = rtl_errors[ERR_MEMORY];
		return false;
	}

	/* allocate data for each maps */
	for (int i = 0; i < rtl->num_maps; i++)
	{
		rtl->maps[i].walls = calloc(1, RTL_PLANE_SIZE);
		rtl->maps[i].sprites = calloc(1, RTL_PLANE_SIZE);
		rtl->maps[i].infos = calloc(1, RTL_PLANE_SIZE);

		/* check for failed memory allocation */
		if (rtl->maps[i].walls == NULL ||
			rtl->maps[i].sprites == NULL ||
			rtl->maps[i].infos == NULL)
		{
			rtl->error = rtl_errors[ERR_MEMORY];
			return false;
		}
	}

	return true;
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
	switch (rtl_get_format(file))
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
	if (rtl_get_version(file) != rtl_version)
	{
		rtl->error = rtl_errors[ERR_VERSION];
		return false;
	}

	/* get number of used maps */
	rtl->num_maps = rtl_get_num_maps(file);
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

/* save RTL structure to disk */
bool rtl_save(const char *filename, rtl_t *rtl)
{
	/* oops */
	if (rtl == NULL)
		return false;
	if (filename == NULL)
	{
		rtl->error = rtl_errors[ERR_FILENAME];
		return false;
	}

	/* open file for writing */
	FILE *file = fopen(filename, "wb");
	if (file == NULL)
	{
		/* couldn't find file */
		rtl->error = rtl_errors[ERR_FILE];
		return false;
	}

	/* write magic */
	if (rtl->commbat)
		fwrite(rtc_magic, 1, 4, file);
	else
		fwrite(rtl_magic, 1, 4, file);

	/* write version */
	fwrite(&rtl_version, 4, 1, file);

	/* write used map headers */
	for (int i = 0; i < rtl->num_maps; i++)
	{
		uint32_t used = 1;
		uint32_t ofs_walls = 0;
		uint32_t ofs_sprites = 0;
		uint32_t ofs_infos = 0;
		uint32_t len_walls = 0;
		uint32_t len_sprites = 0;
		uint32_t len_infos = 0;

		fwrite(&used, 4, 1, file);
		fwrite(&rtl->maps[i].crc, 4, 1, file);
		fwrite(&rtl_tag, 4, 1, file);
		fwrite(&rtl->maps[i].flags, 4, 1, file);
		fwrite(&ofs_walls, 4, 1, file);
		fwrite(&ofs_sprites, 4, 1, file);
		fwrite(&ofs_infos, 4, 1, file);
		fwrite(&len_walls, 4, 1, file);
		fwrite(&len_sprites, 4, 1, file);
		fwrite(&len_infos, 4, 1, file);
		fwrite(rtl->maps[i].name, 1, 24, file);
	}

	/* write the remaining blank headers */
	for (int i = 0; i < RTL_MAX_MAPS - rtl->num_maps; i++)
	{
		uint32_t used = 0;
		char whatever[60] = {0};

		fwrite(&used, 4, 1, file);
		fwrite(whatever, 1, 60, file);
	}

	/* allocate some arrays to store values */
	uint32_t ofs_walls_array[rtl->num_maps];
	uint32_t ofs_sprites_array[rtl->num_maps];
	uint32_t ofs_infos_array[rtl->num_maps];
	uint32_t len_walls_array[rtl->num_maps];
	uint32_t len_sprites_array[rtl->num_maps];
	uint32_t len_infos_array[rtl->num_maps];

	/* write plane data */
	for (int i = 0; i < rtl->num_maps; i++)
	{
		ofs_walls_array[i] = ftell(file);
		len_walls_array[i] = rtl_write_plane(file, rtl->maps[i].walls, rtl_tag);

		ofs_sprites_array[i] = ftell(file);
		len_sprites_array[i] = rtl_write_plane(file, rtl->maps[i].sprites, rtl_tag);

		ofs_infos_array[i] = ftell(file);
		len_infos_array[i] = rtl_write_plane(file, rtl->maps[i].infos, rtl_tag);
	}

	/* now write the offsets and lengths */
	for (int i = 0; i < rtl->num_maps; i++)
	{
		fseek(file, (i * 64) + 8 + 16, SEEK_SET);
		fwrite(&ofs_walls_array[i], 4, 1, file);
		fwrite(&ofs_sprites_array[i], 4, 1, file);
		fwrite(&ofs_infos_array[i], 4, 1, file);
		fwrite(&len_walls_array[i], 4, 1, file);
		fwrite(&len_sprites_array[i], 4, 1, file);
		fwrite(&len_infos_array[i], 4, 1, file);
	}

	/* return success */
	return true;
}
