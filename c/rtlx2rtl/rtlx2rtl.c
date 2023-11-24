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
#include <stdlib.h>
#include <string.h>

#define error(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define warning(...) fprintf(stderr, __VA_ARGS__)

static const uint32_t rtl_version = 0x0101;
static const uint32_t rxl_version = 0x0200;
static const char rtl_magic[4] = {'R', 'T', 'L', '\0'};
static const char rtc_magic[4] = {'R', 'T', 'C', '\0'};
static const char rxl_magic[4] = {'R', 'X', 'L', '\0'};
static const char rxc_magic[4] = {'R', 'X', 'C', '\0'};

static bool strext(const char *s, const char *e)
{
	if (strlen(e) > strlen(s)) return false;
	return strcmp(s + strlen(s) - strlen(e), e) == 0 ? true : false;
}

#ifndef strdup
static char *strdup(const char *s)
{
	char *r;
	r = calloc(1, strlen(s) + 1);
	memcpy(r, s, strlen(s));
	return r;
}
#endif

static char *get_output_filename(const char *s)
{
	char *ret = NULL;

	if (strext(s, ".rtlx") || strext(s, ".rtcx"))
	{
		ret = strdup(s);
		ret[strlen(s) - 1] = '\0';
	}
	else
	{
		error("Error: Input filename doesn't end in .rtlx or .rtcx so I'm stupid and don't know what to do!\n");
	}

	return ret;
}

static void print_help(void)
{
	printf("\nUsage: rtlx2rtl file.rtlx file.rtcx ...\n\n");
	exit(0);
}

int main(int argc, char **argv)
{
	int i;

	if (argc < 2)
		print_help();

	for (i = 1; i < argc; i++)
	{
		FILE *input;
		FILE *output;
		char magic[4];
		uint32_t version;
		uint64_t ofs_infos;
		uint64_t num_infos;
		uint64_t map_array_offset;
		uint64_t map_array_size;
		uint64_t x;
		int m;
		void *map_array_buffer;
		char *output_filename;
		bool commbat;

		/* open input for reading */
		input = fopen(argv[i], "rb");
		if (input == NULL)
		{
			warning("Warning: Couldn't open \"%s\" for reading!\n", argv[i]);
			continue;
		}

		/* check if it's a valid RTLX file */
		fread(magic, 1, 4, input);
		fread(&version, 4, 1, input);
		if ((memcmp(magic, rxl_magic, 4) != 0 && memcmp(magic, rxc_magic, 4) != 0) || version > rxl_version)
		{
			warning("Warning: \"%s\" is not a valid RTLX or RTCX file!\n", argv[i]);
			fclose(input);
			continue;
		}

		/* commbat */
		commbat = memcmp(magic, rxc_magic, 4) == 0 ? true : false;

		/* get map array offset */
		fread(&ofs_infos, 8, 1, input);
		fread(&num_infos, 8, 1, input);
		fseek(input, ofs_infos, SEEK_SET);
		map_array_offset = 0;
		for (x = 0; x < num_infos; x++)
		{
			char info_magic[16];
			uint64_t ofs_info_data;
			uint64_t len_info_data;

			fread(info_magic, 1, 16, input);
			fread(&ofs_info_data, 8, 1, input);
			fread(&len_info_data, 8, 1, input);

			/* this only works for RXL 2.0 */
			if (strncmp(info_magic, "MAPS", 16) == 0)
			{
				map_array_offset = ofs_info_data;
				map_array_size = len_info_data;
			}
		}

		/* couldn't find map array offset */
		if (map_array_offset == 0)
		{
			warning("Warning: Couldn't determine map array offset in \"%s\"!\n", argv[i]);
			fclose(input);
			continue;
		}

		/* allocate map array */
		map_array_buffer = malloc(map_array_size);

		/* read map array */
		fseek(input, map_array_offset, SEEK_SET);
		fread(map_array_buffer, map_array_size, 1, input);

		/* fix up map data offsets */
		for (m = 0; m < 100; m++)
		{
			uint32_t used;
			uint32_t *offsets;

			used = ((uint32_t *)map_array_buffer)[m * 16];

			if (used)
			{
				offsets = &((uint32_t *)map_array_buffer)[(m * 16) + 4];
				offsets[0] -= map_array_offset - 8;
				offsets[1] -= map_array_offset - 8;
				offsets[2] -= map_array_offset - 8;
			}
		}

		/* open output file for writing */
		output_filename = get_output_filename(argv[i]);
		output = fopen(output_filename, "wb");
		if (output == NULL)
		{
			warning("Warning: Couldn't open \"%s\" for writing!\n", output_filename);
			fclose(input);
			free(map_array_buffer);
			free(output_filename);
			continue;
		}

		/* write magic */
		if (commbat)
			fwrite(rtc_magic, 1, 4, output);
		else
			fwrite(rtl_magic, 1, 4, output);

		/* write version */
		fwrite(&rtl_version, 4, 1, output);

		/* write map data */
		fwrite(map_array_buffer, map_array_size, 1, output);

		/* clean up */
		fclose(output);
		fclose(input);
		free(map_array_buffer);

		printf("Successfully wrote \"%s\" to disk.\n", output_filename);
		free(output_filename);
	}

	return 0;
}
