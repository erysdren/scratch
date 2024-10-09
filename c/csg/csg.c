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

#include <stdint.h>

#include <cglm/cglm.h>

typedef int32_t volume_t;

typedef struct plane {
	vec3 normal;
	float offset;
} plane_t;

typedef struct ray {
	vec3 origin;
	vec3 direction;
} ray_t;

typedef struct ray_hit {
	struct brush *brush;
	struct face *face;
	struct fragment *fragment;
	float parameter;
	vec3 position;
} ray_hit_t;

typedef struct box {
	vec3 min;
	vec3 max;
} box_t;

typedef struct fragment {
	face_t *face;
	brush_t *front_brush;
	brush_t *back_brush;
	vertex_t *vertices;
	size_t num_vertices;
	volume_t front_volume;
	volume_t back_volume;
	int relation;
} fragment_t;
