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

#ifndef _RENDERER_H_
#define _RENDERER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include <cglm/types.h>

typedef struct transform {
	vec3 origin;
	vec3 angles;
} transform_t;

typedef struct camera {
	float fov;
	float near;
	float far;
	int32_t width;
	int32_t height;
	transform_t transform;
} camera_t;

typedef struct model {
	vec3 *vertices;
	size_t num_vertices;
	vec3 *colors;
	size_t num_colors;
	vec2 *texcoords;
	size_t num_texcoords;
	uint16_t *indices;
	size_t num_indices;
	uint32_t texture;
} model_t;

typedef struct rect {
	int x, y, w, h;
} rect_t;

/*
 *
 * backend-agnostic
 *
 */

void R_MakeModelViewMatrix(transform_t *transform, mat4 dest);

void R_Perspective(float fov, int w, int h, float near, float far);
void R_Ortho(int x, int y, int w, int h);

model_t *R_AllocModel(size_t num_vertices, size_t num_faces);
void R_FreeModel(model_t *model);

/*
 *
 * backend-specific
 *
 */

void R_Init(const char *title, int w, int h);
void R_Quit(void);

void R_MakeTempTexture(uint32_t *out);
void R_DeleteTexture(uint32_t tex);

void R_SetProjectionMatrix(mat4 projection);
void R_SetModelViewMatrix(mat4 modelview);
void R_SetViewport(int x, int y, int w, int h);

void R_DrawModel(model_t *model, transform_t *transform);
void R_DrawRect(rect_t *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void R_StartFrame(void);
void R_EndFrame(void);

void R_Clear(float r, float g, float b, float a);

#ifdef __cplusplus
}
#endif
#endif /* _RENDERER_H_ */
