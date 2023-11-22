
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

/* only one map flag is used */
enum {
	MAP_TOGGLE_PUSHWALLS = 1 << 0
};

/* map structure */
typedef struct map_t {
	uint32_t crc;		/* identifying crc */
	uint32_t flags;		/* map flags */
	uint16_t *walls;	/* walls plane */
	uint16_t *sprites;	/* sprites plane */
	uint16_t *infos;	/* infos plane */
	char name[24];		/* name string */
} map_t;

/* mapset structure */
typedef struct mapset_t {
	map_t *maps;		/* allocated buffer of maps, num_maps in length */
	int num_maps;		/* number of maps read from the mapset file */
	bool commbat;		/* true if this mapset is intended for comm-bat only */
} mapset_t;

/* allocate mapset */
mapset_t *mapset_allocate(int num_maps, bool commbat);

/* free mapset */
void *mapset_free(mapset_t *mapset);

/* load mapset from filename */
mapset_t *mapset_load(const char *filename);

/* save mapset to disk */
bool mapset_save(const char *filename, mapset_t *mapset);

/* generate new identifier crc for map in mapset */
bool mapset_generate_crc(mapset_t *mapset, int map);

#ifdef __cplusplus
}
#endif
#endif /* _MAPSET_H_ */
