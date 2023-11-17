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

// guard
#ifndef __SPR_H__
#define __SPR_H__

//
//
// headers
//
//

#include <stdint.h>
#include <stdbool.h>

//
//
// types
//
//

enum spr_type
{
	SPR_TYPE_PARALLEL_UPRIGHT = 0,
	SPR_TYPE_FACING_UPRIGHT = 1,
	SPR_TYPE_PARALLEL = 2,
	SPR_TYPE_ORIENTED = 3,
	SPR_TYPE_PARALLEL_ORIENTED = 4
};

enum spr_sync_type
{
	SPR_SYNC_SYNC = 0,
	SPR_SYNC_RAND = 1
};

enum spr_frame_type
{
	SPR_FRAME_SINGLE = 0,
	SPR_FRAME_GROUP = 1
};

// spr header
typedef struct
{
	char magic[4];
	uint32_t version;
 	uint32_t type;
	float bounding_radius;
	uint32_t width;
	uint32_t height;
	uint32_t num_frames;
	float beam_length;
	uint32_t sync_type;
} spr_header_t;

// spr subframe
typedef struct
{
	int32_t origin[2];
	uint32_t width;
	uint32_t height;
	uint8_t *pixels;
} spr_subframe_t;

// spr frame
typedef struct
{
 	uint32_t type;
 	uint32_t num_subframes;
	spr_subframe_t *subframes;
} spr_frame_t;

// spr container
typedef struct
{
	spr_header_t header;
	spr_frame_t *frames;
} spr_t;

//
//
// functions
//
//

spr_t *spr_load(char *filename);
bool spr_save(char *filename, spr_t *spr);
void spr_free(spr_t *spr);

#endif // __SPR_H__
