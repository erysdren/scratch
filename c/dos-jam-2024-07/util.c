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

#include "luna.h"

__attribute__((pure)) int imin(int x, int y)
{
	return x < y ? x : y;
}

__attribute__((pure)) int imax(int x, int y)
{
	return x > y ? x : y;
}

__attribute__((pure)) int iclamp(int i, int min, int max)
{
	return imax(imin(i, max), min);
}

int file_exists(const char *filename)
{
	return access(filename, R_OK) == 0 ? 1 : 0;
}

void die(const char *fmt, ...)
{
	va_list ap;

	vid_mode_set(0x02);

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	fflush(stderr);
	va_end(ap);

	exit(1);
}

void *memset8(void *dest, uint8_t val, size_t n)
{
	asm (
		"rep stosb\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}

void *memset16(void *dest, uint16_t val, size_t n)
{
	asm (
		"rep stosw\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}

void *memset32(void *dest, uint32_t val, size_t n)
{
	asm (
		"rep stosl\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}
