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
#ifndef _WAD_H_
#define _WAD_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* lump structure */
typedef struct lump_t {
	uint32_t ofs;
	uint32_t len;
	char name[8];
} lump_t;

/* wad structure */
typedef struct wad_t {
	uint32_t num_lumps;
	lump_t *lumps;
	FILE *file;
} wad_t;

/* allocate wad */
wad_t *wad_allocate(int num_lumps);

/* open wad handle from filename */
wad_t *wad_open(const char *filename);

/* close wad handle */
void wad_close(wad_t *wad);

/* get wad index from name */
int wad_get_index_from_name(wad_t *wad, const char *name);

/* get name from wad index */
const char *wad_get_name_from_index(wad_t *wad, int index);

/* read lump data into buffer */
void *wad_read_lump(wad_t *wad, int lump, void *buffer);

#ifdef __cplusplus
}
#endif
#endif /* _WAD_H_ */
