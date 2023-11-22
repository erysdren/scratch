
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mapset.h"

/* mapset constants */
#define NUM_MAPS (100)
#define PLANE_SIZE (MAP_WIDTH * MAP_HEIGHT * sizeof(uint16_t))
static uint32_t rtl_version = 0x0101;
static uint32_t rxl_version = 0x0200;
static uint32_t rle_tag = 0x4344;
static const char rtl_magic[4] = {'R', 'T', 'L', '\0'};
static const char rtc_magic[4] = {'R', 'T', 'C', '\0'};
static const char rxl_magic[4] = {'R', 'X', 'L', '\0'};
static const char rxc_magic[4] = {'R', 'X', 'C', '\0'};

/* returns true if it's a valid rott mapset file */
static bool mapset_is_valid(FILE *file)
{
	char magic[4];
	uint32_t version;

	/* read magic and version */
	fseek(file, 0, SEEK_SET);
	fread(magic, 1, 4, file);
	fread(&version, 1, 4, file);

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

/* returns true if mapset is from rott: ludicrous edition */
static bool mapset_is_ludicrous(FILE *file)
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

/* returns true if mapset is intended for comm-bat */
static bool mapset_is_commbat(FILE *file)
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
}

/* return offset of map array */
static uint32_t mapset_get_map_array_ofs(FILE *file)
{
	uint64_t ofs_info_headers;
	uint64_t num_info_headers;
	char info_header_magic[16];
	uint64_t info_header_ofs;
	uint64_t info_header_len;
	int i;

	if (mapset_is_ludicrous(file))
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

			if (strcmp(info_header_magic, "MAPS") == 0 || strcmp(info_header_magic, "MAPSET") == 0)
				return info_header_ofs;
		}
	}
	else
	{
		return 8;
	}
}

/* get number of used maps in mapset */
static int mapset_get_used_maps(FILE *file)
{
	int i;
	uint32_t map_array_ofs;

	map_array_ofs = mapset_get_map_array_ofs(file);

	for (i = 0; i < NUM_MAPS; i++)
	{
		uint32_t used;

		fseek(file, (i * 64) + map_array_ofs, SEEK_SET);
		fread(&used, 1, 4, file);

		if (!used) break;
	}

	return i;
}

/* compress and write plane with run-length encoding */
static uint32_t mapset_write_plane(FILE *file, uint16_t *plane, uint16_t tag)
{
	uint32_t startpos = ftell(file);
	int read = 0;
	uint16_t count;

	/* compress and write source data */
	while (read < PLANE_SIZE)
	{
		count = 1;

		/* read 16-bit word from source */
		uint16_t value = *plane++;
		read += 2;

		/* count repetitions */
		while (*plane == value && read < PLANE_SIZE)
		{
			count++; /* repetitions */
			plane++; /* source data */
			read += 2; /* total number of bytes read */
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
static void mapset_read_plane(FILE *file, int ofs, int len, uint16_t tag, uint16_t *buffer)
{
	/* seek to plane offset */
	fseek(file, ofs, SEEK_SET);

	/* read plane data */
	int pos = 0;
	int written = 0;
	while (pos < len && written < PLANE_SIZE)
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

/* read map from file */
static bool mapset_read_map(FILE *file, int i, map_t *map)
{
	uint32_t used, tag, ofs_walls, ofs_sprites, ofs_infos;
	uint32_t len_walls, len_sprites, len_infos;
	uint32_t map_array_ofs;

	/* sanity checks */
	if (file == NULL || map == NULL || i < 0 || i >= NUM_MAPS)
		return false;

	map_array_ofs = mapset_get_map_array_ofs(file);

	/* get to map header */
	fseek(file, (i * 64) + map_array_ofs, SEEK_SET);

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
	map->walls = calloc(1, PLANE_SIZE);
	map->sprites = calloc(1, PLANE_SIZE);
	map->infos = calloc(1, PLANE_SIZE);

	/* check for memory allocation error */
	if (map->walls == NULL || map->sprites == NULL || map->infos == NULL)
		return false;

	/* read planes */
	mapset_read_plane(file, ofs_walls, len_walls, tag, map->walls);
	mapset_read_plane(file, ofs_sprites, len_sprites, tag, map->sprites);
	mapset_read_plane(file, ofs_infos, len_infos, tag, map->infos);

	return true;
}

/* crc generator */
#define FNV_OFFSET 2166136261UL
#define FNV_PRIME 16777619UL
static uint32_t mapset_make_hash(void *buf, int len)
{
	uint32_t hash = FNV_OFFSET;

	for (int i = 0; i < len; i++)
	{
		hash ^= (uint32_t)((uint8_t *)buf)[i];
		hash *= FNV_PRIME;
	}

	return hash;
}

/* allocate RTL/RTC in memory */
mapset_t *mapset_allocate(int num_maps, bool commbat)
{
	mapset_t *mapset;
	int i;

	/* sanity check */
	if (num_maps <= 0 || num_maps > NUM_MAPS)
		return NULL;

	/* allocate structure */
	mapset = calloc(1, sizeof(mapset_t));
	if (mapset == NULL)
		return NULL;

	/* set values */
	mapset->num_maps = num_maps;
	mapset->commbat = commbat;

	/* allocate maps */
	mapset->maps = calloc(mapset->num_maps, sizeof(map_t));
	if (mapset->maps == NULL)
		return NULL;

	/* allocate data for each maps */
	for (i = 0; i < mapset->num_maps; i++)
	{
		mapset->maps[i].walls = calloc(1, PLANE_SIZE);
		mapset->maps[i].sprites = calloc(1, PLANE_SIZE);
		mapset->maps[i].infos = calloc(1, PLANE_SIZE);

		/* check for failed memory allocation */
		if (mapset->maps[i].walls == NULL || mapset->maps[i].sprites == NULL || mapset->maps[i].infos == NULL)
			return NULL;
	}

	return mapset;
}

/* free map data */
void *mapset_free(mapset_t *mapset)
{
	int i;

	if (mapset)
	{
		if (mapset->num_maps > 0 && mapset->maps != NULL)
		{
			for (i = 0; i < mapset->num_maps; i++)
			{
				if (mapset->maps[i].walls)
					free(mapset->maps[i].walls);

				if (mapset->maps[i].sprites)
					free(mapset->maps[i].sprites);

				if (mapset->maps[i].infos)
					free(mapset->maps[i].infos);
			}

			free(mapset->maps);
		}

		free(mapset);
	}

	return NULL;
}

/* load mapset from filename */
mapset_t *mapset_load(const char *filename)
{
	mapset_t *mapset;
	int num_maps;
	bool commbat;
	FILE *file;
	int i;

	/* sanity check */
	if (filename == NULL)
		return NULL;

	/* open file */
	file = fopen(filename, "rb");
	if (file == NULL)
		return NULL;

	/* check if it's a valid rott mapset file */
	if (mapset_is_valid(file) == false)
		return NULL;

	/* get number of used maps */
	num_maps = mapset_get_used_maps(file);
	if (num_maps <= 0 || num_maps > NUM_MAPS)
		return NULL;

	/* check if it's intended for comm-bat */
	commbat = mapset_is_commbat(file);

	/* now allocate map */
	mapset = mapset_allocate(num_maps, commbat);
	if (mapset == NULL)
		return NULL;

	/* read map data */
	for (i = 0; i < mapset->num_maps; i++)
	{
		/* read data for this map */
		if (!mapset_read_map(file, i, &mapset->maps[i]))
			return NULL;
	}

	/* close file */
	fclose(file);

	/* return success */
	return mapset;
}

/* save mapset to disk */
bool mapset_save(const char *filename, mapset_t *mapset)
{
	FILE *file;
	int i;
	uint32_t map_array_ofs;

	/* sanity check */
	if (mapset == NULL || filename == NULL)
		return false;

	/* open file for writing */
	file = fopen(filename, "wb");
	if (file == NULL)
		return false;

	/* write magic */
	if (mapset->commbat)
		fwrite(rtc_magic, 1, 4, file);
	else
		fwrite(rtl_magic, 1, 4, file);

	/* write version */
	fwrite(&rtl_version, 4, 1, file);

	/* write used map headers */
	for (i = 0; i < mapset->num_maps; i++)
	{
		uint32_t used = 1;
		uint32_t ofs_walls = 0;
		uint32_t ofs_sprites = 0;
		uint32_t ofs_infos = 0;
		uint32_t len_walls = 0;
		uint32_t len_sprites = 0;
		uint32_t len_infos = 0;

		fwrite(&used, 4, 1, file);
		fwrite(&mapset->maps[i].crc, 4, 1, file);
		fwrite(&rle_tag, 4, 1, file);
		fwrite(&mapset->maps[i].flags, 4, 1, file);
		fwrite(&ofs_walls, 4, 1, file);
		fwrite(&ofs_sprites, 4, 1, file);
		fwrite(&ofs_infos, 4, 1, file);
		fwrite(&len_walls, 4, 1, file);
		fwrite(&len_sprites, 4, 1, file);
		fwrite(&len_infos, 4, 1, file);
		fwrite(mapset->maps[i].name, 1, 24, file);
	}

	/* write the remaining blank headers */
	for (i = 0; i < NUM_MAPS - mapset->num_maps; i++)
	{
		char whatever[64];
		memset(whatever, 0, 64);
		fwrite(whatever, 1, 64, file);
	}

	/* allocate some arrays to store values */
	uint32_t ofs_len_array[mapset->num_maps * 6];

	/* write plane data */
	for (i = 0; i < mapset->num_maps; i++)
	{
		ofs_len_array[(i * 6)] = ftell(file);
		ofs_len_array[(i * 6) + 3] = mapset_write_plane(file, mapset->maps[i].walls, rle_tag);

		ofs_len_array[(i * 6) + 1] = ftell(file);
		ofs_len_array[(i * 6) + 4] = mapset_write_plane(file, mapset->maps[i].sprites, rle_tag);

		ofs_len_array[(i * 6) + 2] = ftell(file);
		ofs_len_array[(i * 6) + 5] = mapset_write_plane(file, mapset->maps[i].infos, rle_tag);
	}

	/* now write the offsets and lengths */
	map_array_ofs = 8;
	for (i = 0; i < mapset->num_maps; i++)
	{
		fseek(file, (i * 64) + map_array_ofs + 16, SEEK_SET);
		fwrite(&ofs_len_array[i * 6], 4, 6, file);
	}

	/* close file */
	fclose(file);

	/* success */
	return true;
}

/* generate crc for all maps */
bool mapset_generate_crc(mapset_t *mapset, int map)
{
	if (map < 0 || map >= mapset->num_maps)
		return false;

	/* generate initial hash and then OR it by subsequent hashes */
	mapset->maps[map].crc = mapset_make_hash(mapset->maps[map].walls, PLANE_SIZE);
	mapset->maps[map].crc ^= mapset_make_hash(mapset->maps[map].sprites, PLANE_SIZE);
	mapset->maps[map].crc ^= mapset_make_hash(mapset->maps[map].infos, PLANE_SIZE);

	return true;
}
