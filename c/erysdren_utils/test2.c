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
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#ifdef _WIN32
#define PATH_SEP_CHAR '\\'
#else
#define PATH_SEP_CHAR '/'
#endif

typedef struct file {
	char *basename;
	char *fullname;
	size_t size;
	size_t pos;
	FILE *fp;
	int fh;
} file_t;

file_t *file_open(const char *filename, const char *mode)
{
	file_t *f = NULL;
	FILE *fp = NULL;
	char *ptr = NULL;

	fp = fopen(filename, mode);
	if (!fp)
		goto fail;

	f = calloc(1, sizeof(file_t));
	if (!f)
		goto fail;

	f->fp = fp;
	f->fh = fileno(fp);
	f->pos = 0;

	/* get basename */
	ptr = strrchr(filename, PATH_SEP_CHAR);
	if (ptr)
		f->basename = strdup(ptr + 1);
	else
		f->basename = strdup(filename);
	if (!f->basename)
		goto fail;

	/* get fullname */
	f->fullname = calloc(1, PATH_MAX);
	if (!f->fullname)
		goto fail;

	realpath(filename, f->fullname);

	fseek(fp, 0L, SEEK_END);
	f->size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	goto done;

fail:
	if (fp)
		fclose(fp);

	if (f)
	{
		if (f->basename)
			free(f->basename);

		if (f->fullname)
			free(f->fullname);

		free(f);

		f = NULL;
	}
done:
	return f;
}

void file_close(file_t **f)
{
	fclose((*f)->fp);
	free((*f)->basename);
	free((*f)->fullname);
	free(*f);
	*f = NULL;
}

int main(int argc, char **argv)
{
	file_t *f = file_open("./test1.c", "r");

	assert(f);

	printf("basename: %s\nfullname: %s\nfh: %d\nsize: %zu bytes\npos: %zu\n", f->basename, f->fullname, f->fh, f->size, f->pos);

	file_close(&f);

	assert(f == NULL);

	return 0;
}
