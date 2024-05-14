/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

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
#ifndef __ERYSDREN_UTILS_H__
#define __ERYSDREN_UTILS_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

/* we have assert() at home */
#define ASSERT(e) \
	do { \
		if (!(e)) die("assertion (" #e ") failed at " __FILE__ "#%d", __LINE__); \
	} while (0)

/* true and false */
#define TRUE (1 == 1)
#define FALSE (1 == 0)

/* static array size */
#define ASIZE(a) (sizeof(a) / sizeof(a[0]))

/* stop everything and die immediately */
void die(const char *s, ...);

/* memory */
void *mem_alloc(size_t size);
void mem_free(void *ptr);

/* file handling */
FILE *file_open(const char *filename, const char *mode);
int file_close(FILE *stream);
size_t file_write(void *ptr, size_t size, size_t n, FILE *stream);

/* strings */
int string_endswith(char *str, char *ext);
char *string_duplicate(const char *s, ...);

#ifdef __cplusplus
}
#endif
#endif /* __ERYSDREN_UTILS_H__ */
