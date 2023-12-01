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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "math.h"

/* dotproduct */
fix32_t vec2_dotproduct(vec2_t *v1, vec2_t *v2)
{
	fix32_t r = FIX32(0);
	r += FIX32_MUL(v1->x, v2->x);
	r += FIX32_MUL(v1->y, v2->y);
	return r;
}

fix32_t vec3_dotproduct(vec3_t *v1, vec3_t *v2)
{
	fix32_t r = FIX32(0);
	r += FIX32_MUL(v1->x, v2->x);
	r += FIX32_MUL(v1->y, v2->y);
	r += FIX32_MUL(v1->z, v2->z);
	return r;
}

fix32_t vec4_dotproduct(vec4_t *v1, vec4_t *v2)
{
	fix32_t r = FIX32(0);
	r += FIX32_MUL(v1->x, v2->x);
	r += FIX32_MUL(v1->y, v2->y);
	r += FIX32_MUL(v1->z, v2->z);
	r += FIX32_MUL(v1->w, v2->w);
	return r;
}

/* crossproduct */
vec3_t vec3_crossproduct(vec3_t *v1, vec3_t *v2)
{
	vec3_t r;
	r.x = FIX32_MUL(v1->y, v2->z) - FIX32_MUL(v1->z, v2->y);
	r.y = FIX32_MUL(v1->x, v2->z) - FIX32_MUL(v1->z, v2->x);
	r.z = FIX32_MUL(v1->x, v2->y) - FIX32_MUL(v1->y, v2->x);
	return r;
}
