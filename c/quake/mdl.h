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
#ifndef __MDL_H__
#define __MDL_H__

//
//
// types
//
//

// MDL version enumerations
enum mdl_versions
{
	MDL_VERSION_QTEST = 3,
	MDL_VERSION_QUAKE = 6,
	MDL_VERSION_QUAKE2 = 7,
};

// MDL header
typedef struct
{
	char magic[4];
	uint32_t version;
	float scale[3];
	float translation[3];
	float bounding_radius;
	float eye_position[3];
	uint32_t num_skins;
	uint32_t skin_width;
	uint32_t skin_height;
	uint32_t num_vertices;
	uint32_t num_faces;
	uint32_t num_frames;
	uint32_t sync_type;
	uint32_t flags;
	float size;
} mdl_header_t;

// MDL skin
typedef struct
{
	uint32_t skin_type;
	void *skin_pixels;
} mdl_skin_t;

// MDL texcoord
typedef struct
{
	int32_t onseam;
	int32_t s;
	int32_t t;
} mdl_texcoord_t;

// MDL face
typedef struct
{
	uint32_t face_type;
	uint32_t vertex_indicies[3];
} mdl_face_t;

// MDL vertex
typedef struct
{
	uint8_t coordinates[3];
	uint8_t normal_index;
} mdl_vertex_t;

// MDL frame
typedef struct
{
	uint32_t frame_type;
	mdl_vertex_t min;
	mdl_vertex_t max;
	char name[16];
	mdl_vertex_t *vertices;
} mdl_frame_t;

// MDL container
typedef struct
{
	mdl_header_t header;
	mdl_skin_t *skins;
	mdl_texcoord_t *texcoords;
	mdl_face_t *faces;
	mdl_frame_t *frames;
} mdl_t;

//
//
// functions
//
//

mdl_t *mdl_load(char *filename);
void mdl_free(mdl_t *mdl);

#endif // __MDL_H__
