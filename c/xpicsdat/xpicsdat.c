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
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

#define COLORS (256)
#define WIDTH (64)
#define HEIGHT (64)
#define PICFILE "PICS.DAT"

void say(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	va_end(ap);
}

void die(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	va_end(ap);
	exit(1);
}

int main(void)
{
	uint8_t picture[WIDTH * HEIGHT];
	char outname[256];
	FILE *picfile, *outfile;
	int i;

	/* open files */

	say("opening %s", PICFILE);
	picfile = fopen(PICFILE, "rb");
	if (!picfile)
		die("failed to open %s", PICFILE);

	fseek(picfile, 1024, SEEK_SET);

	/* read then write pictures */
	i = 0;
	while (fread(picture, sizeof(picture), 1, picfile))
	{
		snprintf(outname, sizeof(outname), "pic%03d.data", i);

		outfile = fopen(outname, "wb");
		fwrite(picture, sizeof(picture), 1, outfile);
		fclose(outfile);

		say("%s", outname);

		i++;
	}

	fclose(picfile);

	return 0;
}
