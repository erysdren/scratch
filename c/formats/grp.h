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
 * Name: GRP Format Module
 *
 * Description: Support for the BUILD Engine GRP file format.
 *
 * Dependencies:
 * - libc
 */

#pragma once
#ifndef _GRP_H_
#define _GRP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* grp file struct */
typedef struct grp_file_t {
	char name[12];
	uint32_t len;
	uint32_t ofs;
} grp_file_t;

/* grp struct */
typedef struct grp_t {
	grp_file_t *files;
	int num_files;
	FILE *file;
} grp_t;

/* allocate grp */
grp_t *grp_allocate(int num_files);

/* open grp from filename */
grp_t *grp_open(const char *filename);

/* close grp and free used memory */
void grp_close(grp_t *grp);

/* get file index from name */
int grp_get_index_from_name(grp_t *grp, const char *name);

/* read file data into buffer */
void *grp_read_file(grp_t *grp, int file, void *buffer);

#ifdef __cplusplus
}
#endif
#endif /* _GRP_H_ */
