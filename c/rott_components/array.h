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
#ifndef _ARRAY_H_
#define _ARRAY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* array type */
typedef struct array_t {
	void *entries;		/* pointer to tightly packed array of entries */
	size_t length;		/* number of entries in the array */
	size_t size;		/* size in bytes of each entry in the array */
	bool allocated;		/* true if the array and its entries are allocated */
} array_t;

/* helper macros */
#define VALUE_AT_INDEX(i, n) [i] = n

/* allocate array and entries on the heap */
array_t *array_allocate(size_t length, size_t size);

/* free heap-allocated array */
void array_free(array_t *array);

#ifdef __cplusplus
}
#endif
#endif /* _ARRAY_H_ */
