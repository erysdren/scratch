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

#pragma once
#ifndef _MAPSET_H_
#define _MAPSET_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* mapset constants */
#define MAP_WIDTH (128)
#define MAP_HEIGHT (128)
#define MAP_PLANE_SIZE (MAP_WIDTH * MAP_HEIGHT * sizeof(uint16_t))
#define MAPSET_NUM_MAPS (100)

/* only one map flag is used */
enum {
	MAP_TOGGLE_PUSHWALLS = 1 << 0
};

/* map structure */
typedef struct map_t {
	uint32_t used;			/* nonzero if map is used */
	uint32_t crc;			/* identifying crc */
	uint32_t tag;			/* tag for decompressing plane data */
	uint32_t flags;			/* map flags */
	uint32_t ofs_walls;		/* offset of walls plane */
	uint32_t ofs_sprites;	/* offset of sprites plane */
	uint32_t ofs_infos;		/* offset of infos plane */
	uint32_t len_walls;		/* size of walls plane */
	uint32_t len_sprites;	/* size of sprites plane */
	uint32_t len_infos;		/* size of infos plane */
	char name[24];			/* name string */
} map_t;

/* mapset structure */
typedef struct mapset_t {
	map_t maps[MAPSET_NUM_MAPS];	/* static number of map headers */
	bool commbat;					/* true if this is a comm-bat mapset */
	bool expanded;					/* true if this is a RottEX mapset */
	FILE *file;						/* file handle for reading map planes */
} mapset_t;

/* allocate mapset */
mapset_t *mapset_allocate(void);

/* open mapset from filename */
mapset_t *mapset_open(const char *filename);

/* close mapset and free memory */
void mapset_close(mapset_t *mapset);

/* get mapset index from name */
int mapset_get_index_from_name(mapset_t *mapset, const char *name);

/* get name from mapset index */
const char *mapset_get_name_from_index(mapset_t *mapset, int index);

/* read and uncompress map planes into user-provided buffers */
/* each user-provided buffer should be exactly MAP_PLANE_SIZE in size */
bool mapset_read_map(mapset_t *mapset, int map, void *walls, void *sprites, void *infos);

#ifdef __cplusplus
}
#endif
#endif /* _MAPSET_H_ */
