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

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <cglm/cglm.h>

#include "renderer.h"

static SDL_GLContext context = NULL;
static SDL_Window *window = NULL;

void R_Init(const char *title, int w, int h)
{
	if (!SDL_WasInit(SDL_INIT_VIDEO))
		SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	SDL_SetWindowMinimumSize(window, w, h);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetSwapInterval(1);

	context = SDL_GL_CreateContext(window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void R_Quit(void)
{
	SDL_GL_DestroyContext(context);
	SDL_DestroyWindow(window);

	window = NULL;
	context = NULL;

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void R_MakeTempTexture(uint32_t *out)
{
	GLuint tex;
	static const uint8_t pixels[4 * 3] = {
		0, 0, 255,
		255, 0, 0,
		255, 0, 0,
		0, 0, 255,
	};

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	*out = (uint32_t)tex;
}

void R_DeleteTexture(uint32_t tex)
{
	GLuint gltex = (GLuint)gltex;
	glDeleteTextures(1, &gltex);
}

void R_SetProjectionMatrix(mat4 projection)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((GLfloat *)projection);
}

void R_SetModelViewMatrix(mat4 modelview)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat *)modelview);
}

void R_SetViewport(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
}

void R_DrawModel(model_t *model, transform_t *transform)
{
	mat4 mv;

	R_MakeModelViewMatrix(transform, mv);
	R_SetModelViewMatrix(mv);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, model->vertices);
	glColorPointer(3, GL_FLOAT, 0, model->colors);
	glTexCoordPointer(2, GL_FLOAT, 0, model->texcoords);

	glBindTexture(GL_TEXTURE_2D, (GLuint)model->texture);
	glEnable(GL_TEXTURE_2D);

	glDrawElements(GL_TRIANGLES, model->num_indices, GL_UNSIGNED_SHORT, model->indices);

	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void R_DrawRect(rect_t *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	glColor4ub(r, g, b, a);

	glBegin(GL_QUADS);
		glVertex2i(rect->x, rect->y);
		glVertex2i(rect->x + rect->w, rect->y);
		glVertex2i(rect->x + rect->w, rect->y + rect->h);
		glVertex2i(rect->x, rect->y + rect->h);
	glEnd();
}

void R_StartFrame(void)
{
	SDL_GL_MakeCurrent(window, context);
}

void R_EndFrame(void)
{
	SDL_GL_SwapWindow(window);
}

void R_Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
