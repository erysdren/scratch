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

#define WIDTH (640)
#define HEIGHT (480)

#define RADIUS (2.0f)

typedef struct vec3 {
	float x, y, z;
} vec3_t;

typedef struct vec4 {
	float x, y, z, w;
} vec4_t;

static vec3_t camera_origin = {0, 0, 0};
static float camera_yaw = 0;
static float camera_pitch = 0;

static void get_sphere_position(float radius, float theta, float phi, vec3_t *dest)
{
	dest->x = radius * cosf(theta) * sinf(phi);
	dest->y = radius * sinf(theta) * sinf(phi);
	dest->z = radius * cosf(phi);
}

#define N (16)
static void moon_draw(SDL_Surface *surface)
{
	int i, j;

	camera_yaw += 0.001;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			vec3_t origin, world;
			float theta, phi;
			SDL_Rect rect;

			/* get position on sphere */
			theta = ((M_PI * 2) / N) * i;
			phi = (M_PI / N) * j;
			get_sphere_position(RADIUS, theta, phi, &origin);

			/* offset position by camera */
			origin.x -= camera_origin.x;
			origin.y -= camera_origin.y;
			origin.z -= camera_origin.z;

			/* project to camera space */
			world.x = origin.x * cosf(camera_yaw) - origin.y * sinf(camera_yaw);
			world.y = origin.y * cosf(camera_yaw) - origin.x * sinf(camera_yaw);
			world.z = 0.0f - camera_origin.z + ((camera_pitch * world.y) / 32.0f);
			world.z += origin.z;

			/* fill out rect */
			rect.x = world.x / world.y + (WIDTH / 2);
			rect.y = world.z / world.y + (HEIGHT / 2);
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
