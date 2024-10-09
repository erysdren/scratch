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

#include <SDL2/SDL.h>
#include <cglm/cglm.h>

#define WIDTH (640)
#define HEIGHT (480)

#define RADIUS (2.0f)

static mat4 projection = GLM_MAT4_IDENTITY_INIT;
static mat4 modelview = GLM_MAT4_IDENTITY_INIT;
static vec4 viewport = {0, 0, WIDTH, HEIGHT};

static void moon_init(void)
{
	glm_perspective(glm_rad(90.0f), (float)WIDTH / (float)HEIGHT, 0.1, 1000, projection);
}

static void get_sphere_position(float radius, float theta, float phi, vec3 dest)
{
	dest[0] = radius * cosf(theta) * sinf(phi);
	dest[1] = radius * sinf(theta) * sinf(phi);
	dest[2] = radius * cosf(phi);
}

#define N (16)
static void moon_draw(SDL_Surface *surface)
{
	static float ang = 0;
	int i, j;
	SDL_Rect rect;
	vec3 pos, dest;
	mat4 final = GLM_MAT4_IDENTITY_INIT;

	glm_mat4_identity(modelview);

	glm_rotate_x(modelview, ang*2, modelview);
	glm_rotate_z(modelview, ang/2, modelview);

	glm_translated_z(modelview, -4);

	glm_mat4_mul(projection, modelview, final);

	ang += 0.001;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			float theta;
			float phi;

			theta = ((M_PI * 2) / N) * i;
			phi = (M_PI / N) * j;

			/* get position on sphere */
			get_sphere_position(RADIUS, theta, phi, pos);

			/* project position */
			glm_project(pos, final, viewport, dest);

			/* fill out rect */
			rect.x = (int)dest[0];
			rect.y = (int)dest[1];
			rect.w = 1;
			rect.h = 1;

			/* do draw */
			SDL_FillRect(surface, &rect, 0xFFFFFFFF);
		}
	}

	SDL_Delay(10);
}
#undef N

int main(int argc, char **argv)
{
	SDL_Window *window;
	SDL_Surface *surface;

	SDL_Init(SDL_INIT_VIDEO);

	/* create draw surface */
	window = SDL_CreateWindow("moon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);

	moon_init();

	/* main loop */
	while (!SDL_QuitRequested())
	{
		SDL_FillRect(surface, NULL, 0);
		moon_draw(surface);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
