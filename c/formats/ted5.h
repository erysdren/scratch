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
 * - libc
 */

#pragma once
#ifndef _TED5_H_
#define _TED5_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* ted5 format constants */
#define TED5_NUM_MAPS (100)
#define TED5_NUM_PLANES (3)

/* ted5 map struct */
typedef struct ted5_map_t {
	int32_t ofs_planes[TED5_NUM_PLANES];
	uint16_t len_planes[TED5_NUM_PLANES];
	uint16_t width;
	uint16_t height;
	char name[16];
} ted5_map_t;

/* ted5 format struct */
typedef struct ted5_t {
	ted5_map_t maps[TED5_NUM_MAPS];
	uint16_t tag;
	struct {
		FILE *maphead;
		FILE *maptemp;
	} files;
} ted5_t;

/* create ted5 struct from MAPHEAD and MAPTEMP files */
ted5_t *ted5_open(const char *maphead, const char *maptemp);

/* close ted5 file handles and free used memory */
void ted5_close(ted5_t *ted5);

/* get size (in bytes) of a given map's plane, for memory allocation */
/* returns 0 on error */
size_t ted5_get_plane_size(ted5_t *ted5, int map, int plane);

/* read map plane into user-allocated buffer */
/* allocated buffer size should be determined with ted5_get_plane_size() */
bool ted5_read_plane(ted5_t *ted5, int map, int plane, void *buffer);

/* get map index from name */
/* returns -1 on error */
int ted5_get_map_from_name(ted5_t *ted5, const char *name);

#ifdef __cplusplus
}
#endif
#endif /* _TED5_H_ */
