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

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "renderer.h"

#define TITLE "vte"
#define FOV (90.0f)
#define NEAR (0.1f)
#define FAR (100.0f)

#ifdef __PSP__
static int WIDTH = 480;
static int HEIGHT = 272;
#else
static int WIDTH = 640;
static int HEIGHT = 480;
#endif

#define ASIZE(a) (sizeof(a)/sizeof(a[0]))

static vec3 __attribute__((aligned(16))) cube_vertices[8] = {
	{-1, -1, 1},
	{1, -1, 1},
	{1, 1, 1},
	{-1, 1, 1},
	{-1, -1, -1},
	{1, -1, -1},
	{1, 1, -1},
	{-1, 1, -1}
};

static vec3 __attribute__((aligned(16))) cube_colors[8] = {
	{1, 0, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 0, 1},
	{1, 1, 0},
	{1, 1, 0},
	{0, 1, 1},
	{0, 1, 1}
};

static vec2 __attribute__((aligned(16))) cube_texcoords[8] = {
	{0, 1},
	{1, 1},
	{1, 1},
	{0, 1},
	{0, 0},
	{1, 0},
	{1, 0},
	{0, 0}
};

static uint16_t __attribute__((aligned(16))) cube_indices[12 * 3] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 5,
	0, 5, 1,
	1, 5, 6,
	1, 6, 2,
	2, 6, 7,
	2, 7, 3,
	3, 7, 4,
	3, 4, 0,
	4, 7, 6,
	4, 6, 5
};

static model_t cube_model = {
	cube_vertices, ASIZE(cube_vertices),
	cube_colors, ASIZE(cube_colors),
	cube_texcoords, ASIZE(cube_texcoords),
	cube_indices, ASIZE(cube_indices)
};

static transform_t cube_transform = {
	{0, 0, -4},
	{0, 0, 0}
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
	R_Init("VTE", WIDTH, HEIGHT);
	R_SetViewport(0, 0, WIDTH, HEIGHT);

	R_MakeTempTexture(&cube_model.texture);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate)
{
	R_DeleteTexture(cube_model.texture);
	R_Quit();
	SDL_Quit();
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	rect_t rect = {0, 0, 64, 64};

	cube_transform.angles[1] += 0.01;

	R_StartFrame();
	R_Clear(0, 0, 0, 1);

	R_Perspective(FOV, WIDTH, HEIGHT, NEAR, FAR);
	R_DrawModel(&cube_model, &cube_transform);

	R_Ortho(0, 0, WIDTH, HEIGHT);
	R_DrawRect(&rect, 255, 0, 0, 255);

	R_EndFrame();

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, const SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	switch (event->type)
	{
		case SDL_EVENT_WINDOW_RESIZED:
			WIDTH = event->window.data1;
			HEIGHT = event->window.data2;
			R_SetViewport(0, 0, WIDTH, HEIGHT);
			R_Perspective(FOV, WIDTH, HEIGHT, NEAR, FAR);
			break;
	}

	return SDL_APP_CONTINUE;
}
