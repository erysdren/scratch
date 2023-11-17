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
#include <stdlib.h>

typedef struct
{
	char magic[4];
	int32_t ofs_file_table;
	int32_t len_file_table;
} pak_header_t;

typedef struct
{
	char name[120];
	int32_t ofs_file_data;
	int32_t len_file_data;
} pak_entry_t;

typedef struct
{
	pak_header_t header;
	pak_entry_t *entries;
} pak_t;

int main(int argc, char *argv[])
{
	int i;
	FILE *file;
	pak_t pak;

	// bitch at user
	if (argc < 2)
	{
		printf("useage: %s HROT.pak\n", argv[0]);
		return 0;
	}

	// open pak
	file = fopen(argv[1], "rb");
	if (!file)
	{
		printf("failed to open %s\n", argv[1]);
		return 1;
	}

	// read header
	fread(&pak.header, sizeof(pak_header_t), 1, file);

	// allocate file table
	pak.entries = malloc(pak.header.len_file_table);

	// read file table
	fseek(file, pak.header.ofs_file_table, SEEK_SET);
	fread(pak.entries, pak.header.len_file_table, 1, file);

	// write files out of table
	for (i = 0; i < pak.header.len_file_table / sizeof(pak_entry_t); i++)
	{
		FILE *outfile;
		void *outdata;

		// get output data
		outdata = malloc(pak.entries[i].len_file_data);
		fseek(file, pak.entries[i].ofs_file_data, SEEK_SET);
		fread(outdata, pak.entries[i].len_file_data, 1, file);

		// open output file
		outfile = fopen(pak.entries[i].name, "wb");

		// write output data
		fwrite(outdata, pak.entries[i].len_file_data, 1, outfile);

		// close output file
		fclose(outfile);

		// free memory
		free(outdata);

		// talk to you
		printf("successfully wrote \"%s\"\n", pak.entries[i].name);
	}

	// close pak
	fclose(file);

	// return success
	return 0;
}
