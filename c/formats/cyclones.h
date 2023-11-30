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
 * Name: CyClones Format Module
 *
 * Description: Support for the CyClones (1994) data storage file format.
 *
 * Dependencies:
 * - libc
 */

#pragma once
#ifndef _CYCLONES_H_
#define _CYCLONES_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* format of chunk in file */
typedef struct cychunk_t {
	char name[4];
	uint16_t type;
	uint32_t len;
	uint32_t ofs;
} cychunk_t;

/* cyclones chunk container */
typedef struct cyfile_t {
	cychunk_t *chunks;
	int num_chunks;
	FILE *file;
} cyfile_t;

/* allocate cyfile */
cyfile_t *cyfile_allocate(int num_chunks);

/* open cyfile from filename */
cyfile_t *cyfile_open(const char *filename);

/* close cyfile and free used memory */
void cyfile_close(cyfile_t *cyfile);

/* get chunk index from name */
int cyfile_get_index_from_name(cyfile_t *cyfile, const char *name);

/* read chunk data into buffer */
void *cyfile_read_chunk(cyfile_t *cyfile, int chunk, void *buffer);

#ifdef __cplusplus
}
#endif
#endif /* _CYCLONES_H_ */
