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

//
//
// headers
//
//

// std
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// spr
#include "spr.h"

//
//
// globals
//
//

const char spr_magic[4] = "IDSP";

//
//
// functions
//
//

//
// spr_load
//

spr_t *spr_load(char *filename)
{
	// variables
	spr_t *spr;
	FILE *file;
	int i, s;

	// open file
	file = fopen(filename, "rb");
	if (!file) return NULL;

	// alloc
	spr = calloc(1, sizeof(spr_t));
	if (!spr) return NULL;

	// read header
	fread(&spr->header, sizeof(spr_header_t), 1, file);

	// check magic
	if (memcmp(&spr->header.magic, spr_magic, 4) != 0)
		return NULL;

	// alloc
	spr->frames = calloc(spr->header.num_frames, sizeof(spr_frame_t));
	if (!spr->frames) return NULL;

	// read frames
	for (i = 0; i < spr->header.num_frames; i++)
	{
		// read type
		fread(&spr->frames[i].type, sizeof(uint32_t), 1, file);

		// determine number of subframes
		if (spr->frames[i].type == SPR_FRAME_GROUP)
			fread(&spr->frames[i].num_subframes, sizeof(uint32_t), 1, file);
		else
			spr->frames[i].num_subframes = 1;

		// read subframes
		for (s = 0; s < spr->frames[i].num_subframes; s++)
		{
			// read subframe data
			fread(&spr->frames[i].subframes[s].origin[0], sizeof(int32_t), 1, file);
			fread(&spr->frames[i].subframes[s].origin[1], sizeof(int32_t), 1, file);
			fread(&spr->frames[i].subframes[s].width, sizeof(uint32_t), 1, file);
			fread(&spr->frames[i].subframes[s].height, sizeof(uint32_t), 1, file);

			// allocate pixels
			spr->frames[i].subframes[s].pixels = calloc(spr->frames[i].subframes[s].width * spr->frames[i].subframes[s].height, sizeof(uint8_t));
			if (!spr->frames[i].subframes[s].pixels) return NULL;

			// read pixels
			fread(spr->frames[i].subframes[s].pixels, spr->frames[i].subframes[s].width * spr->frames[i].subframes[s].height, sizeof(uint8_t), file);
		}
	}

	// close file and return ptr
	fclose(file);
	return spr;
}

//
// _write_subframe
//

void _write_subframe(FILE *stream, spr_subframe_t *subframe)
{
	// write origin
	fwrite(&subframe->origin[0], sizeof(int32_t), 1, stream);
	fwrite(&subframe->origin[1], sizeof(int32_t), 1, stream);

	// write size
	fwrite(&subframe->width, sizeof(uint32_t), 1, stream);
	fwrite(&subframe->height, sizeof(uint32_t), 1, stream);

	// write pixels
	fwrite(subframe->pixels, subframe->width * subframe->height, sizeof(uint8_t), stream);
}

//
// _write_frame
//

void _write_frame(FILE *stream, spr_frame_t *frame)
{
	// variables
	int i;

	// write type
	fwrite(&frame->type, sizeof(uint32_t), 1, stream);

	// write number of subframes
	if (frame->type == SPR_FRAME_GROUP)
		fwrite(&frame->num_subframes, sizeof(uint32_t), 1, stream);

	// write subframes
	for (i = 0; i < frame->num_subframes; i++)
		_write_subframe(stream, &frame->subframes[i]);
}

//
// spr_save
//

bool spr_save(char *filename, spr_t *spr)
{
	// variables
	FILE *file;
	int i, s;

	// open file
	file = fopen(filename, "wb");
	if (!file) return false;

	// write header
	fwrite(&spr->header, sizeof(spr_header_t), 1, file);

	// write frames
	for (i = 0; i < spr->header.num_frames; i++)
		_write_frame(file, &spr->frames[i]);

	// return success
	fclose(file);
	return true;
}

//
// spr_free
//

void spr_free(spr_t *spr)
{
	int i, f;

	// free sprite
	if (spr)
	{
		// free frames
		if (spr->frames)
		{
			for (i = 0; i < spr->header.num_frames; i++)
			{
				// free subframes
				if (spr->frames[i].subframes)
				{
					for (f = 0; f < spr->frames[i].num_subframes; f++)
					{
						// free subframe pixels
						if (spr->frames[i].subframes[f].pixels)
							free(spr->frames[i].subframes[f].pixels);
					}

					free(spr->frames[i].subframes);
				}
			}

			free(spr->frames);
		}

		free(spr);
	}
}
