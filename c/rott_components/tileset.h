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
#ifndef _TILESET_H_
#define _TILESET_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* tileset entry */
typedef struct tileset_entry_t {
	const char *name;
	int index;
} tileset_entry_t;

/* tileset */
typedef struct tileset_t {
	tileset_entry_t *entries;
	int num_entries;
} tileset_t;

/* helper macros */
#define TILESET_ENTRY(i, n) [i] = {.index = i, .name = n}

/* get tileset index from tile name */
/* returns -1 on error */
int tileset_get_index_from_name(tileset_t *tileset, const char *name);

/* get tile name from tileset index */
/* returns NULL on error */
const char *tileset_get_name_from_index(tileset_t *tileset, int index);

#ifdef __cplusplus
}
#endif
#endif /* _TILESET_H_ */
