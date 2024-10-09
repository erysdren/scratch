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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct arena {
	uint8_t *start;
	uint8_t *end;
} arena_t;

void *arena_alloc(arena_t *arena, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count)
{

}

bool arena_init(arena_t *arena, ptrdiff_t max)
{
	if (!arena || !max)
		return false;

	arena->start = malloc(max);
	if (!arena->start)
		return false;

	arena->end = arena->start + max;

	return true;
}

bool arena_free(arena_t **arena)
{
	if (!arena)
		return false;
	if (!*arena)
		return false;

	free(*arena);

	return true;
}
