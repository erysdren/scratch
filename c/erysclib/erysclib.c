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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "erysdren_utils.h"

void die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, s);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	fflush(stderr);
	va_end(ap);

	exit(1);
}

void *mem_alloc(size_t size)
{
	void *ptr = calloc(1, size);

	if (ptr == NULL)
		die("Memory allocation failed with %zu bytes", size);

	return ptr;
}

void mem_free(void *ptr)
{
	if (ptr == NULL)
		die("Tried to free null pointer");

	free(ptr);
}

FILE *file_open(const char *filename, const char *mode)
{
	FILE *file = fopen(filename, mode);

	if (file == NULL)
		die("Opening \"%s\" failed: %s", filename, strerror(errno));

	return file;
}

int file_close(FILE *stream)
{
	if (fclose(stream) == EOF)
		die("fclose() failed: %s", strerror(errno));

	return 0;
}

size_t file_write(void *ptr, size_t size, size_t n, FILE *stream)
{
	size_t r = fwrite(ptr, size, n, stream);

	if (ferror(stream))
		die("fwrite() failed: %s", strerror(errno));

	return r;
}

int string_endswith(char *str, char *ext)
{
	size_t len_str = strlen(str);
	size_t len_ext = strlen(ext);
	if (len_ext > len_str) return FALSE;
	return strcmp(str + len_str - len_ext, ext) == 0 ? TRUE : FALSE;
}

char *string_duplicate(const char *s, ...)
{
	static char buffer[2048];
	va_list list;
	char *ret;

	va_start(list, s);
	vsnprintf(buffer, sizeof(buffer), s, list);
	va_end(list);

	ret = strndup(buffer, sizeof(buffer));

	if (ret == NULL)
		die("strndup() failed: %s", strerror(errno));

	return ret;
}
