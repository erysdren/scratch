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
 * Name: ART Format Module
 *
 * Description: Support for the BUILD Engine ART file format.
 *
 * Dependencies:
 * - libc
 */

#pragma once
#ifndef _ART_H_
#define _ART_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* art tile struct */
typedef struct art_tile_t {
	uint16_t width;
	uint16_t height;
	uint32_t flags;
	uint32_t len;
	uint32_t ofs;
} art_tile_t;

/* art struct */
typedef struct art_t {
	art_tile_t *files;
	int num_tiles;
	FILE *file;
} art_t;

/* allocate art */
art_t *art_allocate(int num_tiles);

/* open art from filename */
art_t *art_open(const char *filename);

/* close art and free used memory */
void art_close(art_t *art);

/* read tile data into buffer */
void *art_read_tile(art_t *art, int file, void *buffer);

#ifdef __cplusplus
}
#endif
#endif /* _ART_H_ */
