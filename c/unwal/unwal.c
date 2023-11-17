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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "palette.h"

typedef struct
{
	char name[32];
	int32_t width;
	int32_t height;
	int32_t mipmap_offsets[4];
	char next_name[32];
	uint32_t flags;
	uint32_t contents;
	uint32_t value;
} wal_t;

bool strext(char *str, char *ext)
{
	char *ptr = str + strlen(str) - strlen(ext);
	return strcmp(ptr, ext) == 0 ? true : false;
}

void changeext(char *str, char *ext)
{
	char *ptr = str + strlen(str) - strlen(ext);
	strcpy(ptr, ext);
}

int main(int argc, char *argv[])
{
	int i, p;
	uint8_t c;
	wal_t wal;
	FILE *file;
	uint8_t *pixels;

	if (argc < 2)
	{
		printf("useage: unwal file.wal\n");
		return 0;
	}

	for (i = 1; i < argc; i++)
	{
		// talk to you
		printf("processing %s\n", argv[i]);

		// check ext
		if (!strext(argv[i], ".wal") && !strext(argv[1], ".WAL"))
		{
			printf("%s has no WAL extension, will not try!\n", argv[i]);
			continue;
		}

		// open file
		file = fopen(argv[i], "rb");
		if (!file)
		{
			printf("failed to open %s!\n", argv[i]);
			continue;
		}

		// read wad header
		fread(&wal, sizeof(wal_t), 1, file);

		// alloc pixel buffer
		pixels = malloc(wal.width * wal.height * 3);

		// seek to mip 0
		fseek(file, wal.mipmap_offsets[0], SEEK_SET);

		// convert to rgba
		for (p = 0; p < wal.width * wal.height; p++)
		{
			c = fgetc(file);
			pixels[p * 3] = palette_data[c * 3];
			pixels[(p * 3) + 1] = palette_data[(c * 3) + 1];
			pixels[(p * 3) + 2] = palette_data[(c * 3) + 2];
		}

		// change output filename
		changeext(argv[i], ".png");

		// write png
		stbi_write_png(argv[i], wal.width, wal.height, 3, pixels, wal.width * 3);

		// talk to you
		printf("saved %s\n", argv[i]);

		// free memory
		free(pixels);
		fclose(file);
	}

	return 0;
}
