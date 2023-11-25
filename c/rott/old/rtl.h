
#pragma once
#ifndef _RTL_H_
#define _RTL_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* map dimensions */
#define RTL_MAP_WIDTH (128)
#define RTL_MAP_HEIGHT (128)

/* size of walls, sprites and infos planes in bytes */
#define RTL_PLANE_SIZE (RTL_MAP_WIDTH * RTL_MAP_HEIGHT * sizeof(uint16_t))

/* only one map flag is used */
enum {
	RTL_MAPFLAG_TOGGLE_PUSHWALLS = 1 << 0
};

/* RTL/RTC file map structure */
typedef struct rtl_map_t {
	uint32_t crc; /* crc to identify the map for comm-bat */
	uint32_t flags; /* map flags (only bit 0 is used for anything) */
	uint16_t *walls; /* walls plane, RTL_PLANE_SIZE bytes in size */
	uint16_t *sprites; /* sprites plane, RTL_PLANE_SIZE bytes in size */
	uint16_t *infos; /* infos plane, RTL_PLANE_SIZE bytes in size */
	char name[24]; /* null-terminated name string */
} rtl_map_t;

/* RTL/RTC file structure */
typedef struct rtl_t {
	rtl_map_t *maps; /* allocated buffer of maps, num_maps in length */
	int num_maps; /* number of maps in the read RTL/RTC file, may be 0 */
	bool commbat; /* true if this file is intended for comm-bat only */
	const char *error; /* pointer to string if rtl_load() returns false */
} rtl_t;

/* allocate RTL/RTC in memory */
bool rtl_allocate(int num_maps, bool commbat, rtl_t *rtl);

/* load RTL/RTC file from filename */
bool rtl_load(const char *filename, rtl_t *rtl);

/* save RTL structure to disk */
bool rtl_save(const char *filename, rtl_t *rtl);

/* generate crc for all maps */
bool rtl_generate_crc(rtl_t *rtl);

/* free RTL/RTC file data */
void rtl_free(rtl_t *rtl);

#ifdef __cplusplus
}
#endif
#endif /* _RTL_H_ */
