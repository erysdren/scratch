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

#include <stdio.h>
#include <stdbool.h>
#include "engine.h"
#include "utils.h"
#include "console.h"
#include "adlib.h"
#include "imf.h"

static bool imf_started = false;
static uint16_t *imf_buffer = NULL;
static int imf_buffer_size = 0;

void imf_init(const char *filename)
{
	FILE *file;

	if (imf_started)
		error("tried to start imf player, but it's already started");

	/* open file */
	file = fopen(filename, "rb");
	if (!file)
		error("couldn't find %s", filename);

	/* get file size */
	fseek(file, 0, SEEK_END);
	imf_buffer_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	/* allocate file buffer */
	imf_buffer = calloc(1, imf_buffer_size);
	if (!imf_buffer)
		error("couldn't allocate memory for imf player");

	/* read file buffer */
	fread(imf_buffer, imf_buffer_size, 1, file);

	/* close file */
	fclose(file);

	/* start */
	imf_started = true;
	console_printf("imf player started");
}

void imf_play(void)
{
	if (!imf_started)
		error("tried to run imf service, but it's not started yet");
}

void imf_quit(void)
{
	imf_started = false;
	imf_buffer_size = 0;

	free(imf_buffer);

	imf_buffer = NULL;

	adlib_reset();

	console_printf("imf player shutdown");
}
