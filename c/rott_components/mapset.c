
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mapset.h"

/* mapset constants */
static uint32_t rtl_version = 0x0101;
static uint32_t rxl_version = 0x0200;
static uint32_t rle_tag_registered = 0x4344;
static uint32_t rle_tag_shareware = 0x4d4b;
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
static uint32_t mapset_get_map_array_offset(FILE *file)
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

			if (strcmp(info_header_magic, "MAPS") == 0 ||
				strcmp(info_header_magic, "MAPSET") == 0)
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

	map_array_ofs = mapset_get_map_array_offset(file);

	for (i = 0; i < MAPSET_NUM_MAPS; i++)
	{
		uint32_t used;

		fseek(file, (i * 64) + map_array_ofs, SEEK_SET);
		fread(&used, 4, 1, file);

		if (!used) break;
	}

	return i;
}

/* read plane from map */
static void mapset_read_plane(FILE *file, int ofs, int len, uint16_t tag, uint16_t *buffer)
{
	/* seek to plane offset */
	fseek(file, ofs, SEEK_SET);

	/* read plane data */
	int pos = 0;
	int written = 0;
	while (pos < len && written < MAP_PLANE_SIZE)
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

/* allocate mapset */
mapset_t *mapset_allocate(void)
{
	mapset_t *mapset;

	/* allocate structure */
	mapset = calloc(1, sizeof(mapset_t));
	if (mapset == NULL)
		return NULL;

	return mapset;
}

/* open mapset from filename */
mapset_t *mapset_open(const char *filename)
{
	mapset_t *mapset;
	int num_maps;
	uint32_t map_array_ofs;
	FILE *file;

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
	if (num_maps <= 0 || num_maps > MAPSET_NUM_MAPS)
		return NULL;

	/* allocate mapset */
	mapset = mapset_allocate();
	if (mapset == NULL)
		return NULL;

	/* read map data */
	map_array_ofs = mapset_get_map_array_offset(file);
	fseek(file, map_array_ofs, SEEK_SET);
	fread(mapset->maps, sizeof(map_t), MAPSET_NUM_MAPS, file);

	/* assign values */
	mapset->commbat = mapset_is_commbat(file);
	mapset->expanded = mapset_is_ludicrous(file);
	mapset->file = file;

	/* return success */
	return mapset;
}

/* close mapset and free memory */
void mapset_close(mapset_t *mapset)
{
	if (mapset)
	{
		if (mapset->file != NULL)
			fclose(mapset->file);

		free(mapset);
	}
}

/* get mapset index from name */
int mapset_get_index_from_name(mapset_t *mapset, const char *name)
{
	int i;

	/* sanity check */
	if (mapset == NULL || name == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < MAPSET_NUM_MAPS; i++)
	{
		if (!mapset->maps[i].used)
			continue;

		if (strncmp(mapset->maps[i].name, name, 24) == 0)
			return i;
	}

	/* fail */
	return -1;
}

/* get name from mapset index */
const char *mapset_get_name_from_index(mapset_t *mapset, int index)
{
	/* sanity checks */
	if (mapset == NULL || index < 0 || index >= MAPSET_NUM_MAPS)
		return NULL;
	if (!mapset->maps[index].used)
		return NULL;

	return mapset->maps[index].name;
}

/* read and uncompress map planes into provided buffers */
bool mapset_read_map(mapset_t *mapset, int map, void *walls, void *sprites, void *infos)
{
	/* sanity checks */
	if (mapset == NULL || (walls == NULL && sprites == NULL && infos == NULL))
		return false;
	if (mapset->file == NULL || map < 0 || map >= MAPSET_NUM_MAPS)
		return false;
	if (!mapset->maps[map].used)
		return false;

	if (walls != NULL)
		mapset_read_plane(mapset->file,
			mapset->maps[map].ofs_walls,
			mapset->maps[map].len_walls,
			mapset->maps[map].tag,
			walls);

	if (sprites != NULL)
		mapset_read_plane(mapset->file,
			mapset->maps[map].ofs_sprites,
			mapset->maps[map].len_sprites,
			mapset->maps[map].tag,
			sprites);

	if (infos != NULL)
		mapset_read_plane(mapset->file,
			mapset->maps[map].ofs_infos,
			mapset->maps[map].len_infos,
			mapset->maps[map].tag,
			infos);

	return true;
}
