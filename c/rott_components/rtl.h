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
#ifndef _RTL_H_
#define _RTL_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* rtl format constants */
#define RTL_MAP_WIDTH (128)
#define RTL_MAP_HEIGHT (128)
#define RTL_MAP_PLANE_SIZE (RTL_MAP_WIDTH * RTL_MAP_HEIGHT * sizeof(uint16_t))
#define RTL_NUM_MAPS (100)

/* rtl map flags  */
enum {
	RTL_MAP_OPEN_PUSHWALLS = 1 << 0
};

/* rtl map structure */
typedef struct rtl_map_t {
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
} rtl_map_t;

/* rtl format structure */
typedef struct rtl_t {
	rtl_map_t maps[RTL_NUM_MAPS];	/* static number of map headers */
	bool commbat;					/* true if this is for comm-bat only */
	bool ludicrous;					/* true if this is from ROTT: Ludicrous Edition */
	FILE *file;						/* file handle for reading map planes */
} rtl_t;

/* open rtl from filename */
/* returns NULL on error */
rtl_t *rtl_open(const char *filename);

/* close rtl and free memory */
void rtl_close(rtl_t *rtl);

/* get rtl index from name */
/* returns -1 on error */
int rtl_get_index_from_name(rtl_t *rtl, const char *name);

/* get name from rtl index */
/* returns NULL on error */
const char *rtl_get_name_from_index(rtl_t *rtl, int index);

/* read and uncompress map planes into user-provided buffers */
/* each user-provided buffer should be exactly RTL_MAP_PLANE_SIZE in size */
bool rtl_read_map(rtl_t *rtl, int map, void *walls, void *sprites, void *infos);

#ifdef __cplusplus
}
#endif
#endif /* _RTL_H_ */
