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

#include <cglm/cglm.h>

#include "renderer.h"

void R_MakeModelViewMatrix(transform_t *transform, mat4 dest)
{
	mat4 origin, angle;

	glm_translate_make(origin, transform->origin);
	glm_euler(transform->angles, angle);
	glm_mat4_mul(origin, angle, dest);
}

void R_Perspective(float fov, int w, int h, float near, float far)
{
	mat4 projection;

	glm_perspective(glm_rad(fov), (float)w / (float)h, near, far, projection);

	R_SetProjectionMatrix(projection);
}

void R_Ortho(int x, int y, int w, int h)
{
	mat4 m;

	glm_ortho(x, w, y, h, -1, 1, m);

	R_SetProjectionMatrix(m);

	glm_mat4_identity(m);

	R_SetModelViewMatrix(m);
}

#if 0
model_t *R_AllocModel(size_t num_vertices, size_t num_faces)
{
	model_t *model;

	model = SDL_malloc(sizeof(model_t));

	model->vertices = SDL_aligned_alloc(16, sizeof(vec3) * num_vertices);
	model->colors = SDL_aligned_alloc(16, sizeof(vec3) * num_vertices);
	model->texcoords = SDL_aligned_alloc(16, sizeof(vec2) * num_vertices);
	model->indices = SDL_aligned_alloc(16, sizeof(uint32_t) * num_faces * 3);

	model->num_vertices = num_vertices;
	model->num_colors = num_vertices;
	model->num_texcoords = num_vertices;
	model->num_indices = num_faces * 3;
	model->texture = 0;

	return model;
}

void R_FreeModel(model_t *model)
{
	R_DeleteTexture(model->texture);

	SDL_aligned_free(model->vertices);
	SDL_aligned_free(model->colors);
	SDL_aligned_free(model->texcoords);
	SDL_aligned_free(model->indices);

	SDL_free(model);
}
#endif
