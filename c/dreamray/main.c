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

/*
 *
 * MAIN.C
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <math.h>
#include <float.h>

#include "SDL.h"
#include "SDL_image.h"

#include "ray.h"

#define WIDTH 640
#define HEIGHT 480

static struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface8;
	SDL_Surface *surface32;
	SDL_Texture *texture;
	SDL_Rect rect;
	SDL_Event event;
	SDL_bool running;
	const Uint8 *keys;
	Uint64 now;
	Uint64 last;
	double dt;
} sdl;

/* ray structure */
#define MAP_WIDTH 32
#define MAP_HEIGHT 32
#define TILE_AT(x, y) tiles[(y) * MAP_WIDTH + (x)]
tile_t tiles[MAP_WIDTH * MAP_HEIGHT];
ray_t ray;

/* install palette to SDL_Surface */
SDL_bool install_palette(const char *filename, SDL_Surface *surface)
{
	FILE *file;
	int i;
	SDL_Color colors[256];

	file = fopen(filename, "rb");
	if (!file)
		return SDL_FALSE;

	for (i = 0; i < 256; i++)
	{
		colors[i].r = fgetc(file);
		colors[i].g = fgetc(file);
		colors[i].b = fgetc(file);
	}

	SDL_SetPaletteColors(surface->format->palette, colors, 0, 256);

	fclose(file);

	return SDL_TRUE;
}

/* load all walls */
void load_walls(char *palette)
{
	int i;
	char str[128];

	ray.textures.walls = calloc(64, sizeof(SDL_Surface *));

	for (i = 0; i < 64; i++)
	{
		snprintf(str, 128, "gfx/wall%d.png", i + 1);

		ray.textures.walls[i] = IMG_Load(str);

		if (ray.textures.walls[i] == NULL)
			break;

		install_palette(palette, ray.textures.walls[i]);
	}

	ray.textures.num_walls = i;
	printf("Loaded %d wall textures.\n", i);
}

/* load all maskwalls */
void load_maskwalls(char *palette)
{
	int i;
	char str[128];

	ray.textures.maskwalls = calloc(64, sizeof(SDL_Surface *));

	for (i = 0; i < 64; i++)
	{
		snprintf(str, 128, "gfx/mask%d.png", i + 1);

		ray.textures.maskwalls[i] = IMG_Load(str);

		if (ray.textures.maskwalls[i] == NULL)
			break;

		install_palette(palette, ray.textures.maskwalls[i]);
	}

	ray.textures.num_maskwalls = i;
	printf("Loaded %d mask textures.\n", i);
}

/* load all floors */
void load_floors(char *palette)
{
	int i;
	char str[128];

	ray.textures.floors = calloc(64, sizeof(SDL_Surface *));

	for (i = 0; i < 64; i++)
	{
		snprintf(str, 128, "gfx/floor%d.png", i + 1);

		ray.textures.floors[i] = IMG_Load(str);

		if (ray.textures.floors[i] == NULL)
			break;

		install_palette(palette, ray.textures.floors[i]);
	}

	ray.textures.num_floors = i;
	printf("Loaded %d floor textures.\n", i);
}

/* free all walls */
void free_walls(void)
{
	int i;

	for (i = 0; i < 64; i++)
	{
		if (ray.textures.walls[i] != NULL)
			SDL_FreeSurface(ray.textures.walls[i]);
	}

	free(ray.textures.walls);
}

/* free all maskwalls */
void free_maskwalls(void)
{
	int i;

	for (i = 0; i < 64; i++)
	{
		if (ray.textures.maskwalls[i] != NULL)
			SDL_FreeSurface(ray.textures.maskwalls[i]);
	}

	free(ray.textures.maskwalls);
}

/* free all floors */
void free_floors(void)
{
	int i;

	for (i = 0; i < 64; i++)
	{
		if (ray.textures.floors[i] != NULL)
			SDL_FreeSurface(ray.textures.floors[i]);
	}

	free(ray.textures.floors);
}

void my_cool_button(void *user)
{
	printf("button pressed!\n");
}

/* main */
int main(int argc, char **argv)
{
	uint32_t pixel_format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;
	int x, y;
	vec2f_t dir;
	bool test_value = true;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	sdl.window = SDL_CreateWindow("dreamray",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MAXIMIZED
	);

	SDL_SetWindowMinimumSize(sdl.window, WIDTH, HEIGHT);

	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(sdl.renderer, WIDTH, HEIGHT);
	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl.renderer);
	SDL_RenderPresent(sdl.renderer);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	sdl.surface8 = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 8, 0, 0, 0, 0);
	SDL_FillRect(sdl.surface8, NULL, 0);

	pixel_format = SDL_GetWindowPixelFormat(sdl.window);
	SDL_PixelFormatEnumToMasks(pixel_format, &bpp, &rmask, &gmask, &bmask, &amask);

	sdl.surface32 = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, bpp, rmask, gmask, bmask, amask);
	sdl.texture = SDL_CreateTexture(sdl.renderer, pixel_format, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

	sdl.rect.x = 0;
	sdl.rect.y = 0;
	sdl.rect.w = WIDTH;
	sdl.rect.h = HEIGHT;

	sdl.now = SDL_GetPerformanceCounter();
	sdl.last = 0;
	sdl.dt = 0;

	SDL_SetRelativeMouseMode(SDL_TRUE);

	/* init raycaster */
	ray_init(&ray);

	/* setup tiles */
	memset(tiles, 0, sizeof(tiles));
	TILE_AT(5, 10).height = 8;
	TILE_AT(5, 10).texture = 17;
	TILE_AT(6, 10).height = 8;
	TILE_AT(6, 10).texture = 17;
	TILE_AT(7, 10).height = 8;
	TILE_AT(7, 10).texture = 17;
	TILE_AT(8, 10).height = 8;
	TILE_AT(8, 10).texture = 18;
	TILE_AT(9, 10).height = 8;
	TILE_AT(9, 10).texture = 17;
	TILE_AT(10, 10).height = 8;
	TILE_AT(10, 10).texture = 19;
	TILE_AT(11, 10).height = 7;
	TILE_AT(11, 10).texture = 17;
	TILE_AT(12, 10).height = 6;
	TILE_AT(12, 10).texture = 17;
	TILE_AT(13, 10).height = 5;
	TILE_AT(13, 10).texture = 17;
	TILE_AT(14, 10).height = 4;
	TILE_AT(14, 10).texture = 17;
	TILE_AT(15, 10).height = 3;
	TILE_AT(15, 10).texture = 17;
	TILE_AT(16, 10).height = 2;
	TILE_AT(16, 10).texture = 17;
	TILE_AT(17, 10).height = 1;
	TILE_AT(17, 10).texture = 17;

	/* setup tilemap */
	ray.tilemap.width = MAP_WIDTH;
	ray.tilemap.height = MAP_HEIGHT;
	ray.tilemap.tiles = tiles;
	ray.tilemap.light_scale = 2;
	ray.tilemap.light_level = 0;
	ray.tilemap.ceiling = 8;

	/* setup camera */
	ray.camera.origin.x = MAP_WIDTH / 2;
	ray.camera.origin.y = MAP_HEIGHT / 2;
	ray.camera.origin.z = 0.5;
	ray.camera.yaw = 0;
	ray.camera.pitch = 0;

	/* setup config */
	ray.config.draw_sky = true;
	ray.config.draw_wall_textures = true;
	ray.config.stretch_wall_textures = false;
	ray.config.draw_floor_textures = true;
	ray.config.draw_ceiling_textures = true;

	/* load textures */
	load_walls("gfx/palette.dat");
	load_maskwalls("gfx/palette.dat");
	load_floors("gfx/palette.dat");
	ray.textures.sky = IMG_Load("gfx/sky.png");
	ray.colormap = IMG_Load("gfx/colormap.png");
	ray.font = IMG_Load("gfx/font8x8.png");
	SDL_SetColorKey(ray.font, SDL_TRUE, 0xFF);
	ray.crosshair = IMG_Load("gfx/crosshair.png");
	SDL_SetColorKey(ray.crosshair, SDL_TRUE, 0xFF);

	/* install palettes */
	install_palette("gfx/palette.dat", ray.textures.sky);
	install_palette("gfx/palette.dat", sdl.surface8);
	install_palette("gfx/palette.dat", ray.colormap);
	install_palette("gfx/palette.dat", ray.font);

	/* set render destination */
	ray.dest = sdl.surface8;

	/* main loop */
	sdl.running = SDL_TRUE;
	while (sdl.running)
	{
		sdl.keys = SDL_GetKeyboardState(NULL);

		while (SDL_PollEvent(&sdl.event))
		{
			switch (sdl.event.type)
			{
				case SDL_QUIT:
					sdl.running = SDL_FALSE;
					break;

				case SDL_MOUSEMOTION:
					ray.camera.pitch += sdl.event.motion.yrel;
					ray.camera.yaw -= sdl.event.motion.xrel;
					break;

				default:
					break;
			}
		}

		if (sdl.keys[SDL_SCANCODE_ESCAPE])
			sdl.running = SDL_FALSE;

		/* deltatime */
		sdl.last = sdl.now;
		sdl.now = SDL_GetPerformanceCounter();
		sdl.dt = ((double)(sdl.now - sdl.last) / (double)SDL_GetPerformanceFrequency());

		/* get look direction */
		dir.x = sinf(DEG2RAD(ray.camera.yaw)) * sdl.dt * 2;
		dir.y = cosf(DEG2RAD(ray.camera.yaw)) * sdl.dt * 2;

		/* movement controls */
		if (sdl.keys[SDL_SCANCODE_W] || sdl.keys[SDL_SCANCODE_UP])
		{
			ray.camera.origin.x += dir.x;
			ray.camera.origin.y += dir.y;
		}
		if (sdl.keys[SDL_SCANCODE_S] || sdl.keys[SDL_SCANCODE_DOWN])
		{
			ray.camera.origin.x -= dir.x;
			ray.camera.origin.y -= dir.y;
		}
		if (sdl.keys[SDL_SCANCODE_A])
		{
			ray.camera.origin.x += dir.y;
			ray.camera.origin.y -= dir.x;
		}
		if (sdl.keys[SDL_SCANCODE_D])
		{
			ray.camera.origin.x -= dir.y;
			ray.camera.origin.y += dir.x;
		}

		/* look controls */
		if (sdl.keys[SDL_SCANCODE_LEFT])
		{
			ray.camera.yaw += 1;
		}
		if (sdl.keys[SDL_SCANCODE_RIGHT])
		{
			ray.camera.yaw -= 1;
		}
		if (sdl.keys[SDL_SCANCODE_PAGEUP])
		{
			ray.camera.pitch -= 2;
		}
		if (sdl.keys[SDL_SCANCODE_PAGEDOWN])
		{
			ray.camera.pitch += 2;
		}
		if (sdl.keys[SDL_SCANCODE_HOME])
		{
			ray.camera.pitch = 0;
		}

		/* light controls */
		if (sdl.keys[SDL_SCANCODE_KP_PLUS])
		{
			ray.tilemap.light_level += 1;
		}
		if (sdl.keys[SDL_SCANCODE_KP_MINUS])
		{
			ray.tilemap.light_level -= 1;
		}

		/* draw */
		ray_draw(&ray);

		/* blit to screen */
		SDL_BlitSurface(sdl.surface8, &sdl.rect, sdl.surface32, &sdl.rect);
		SDL_UpdateTexture(sdl.texture, NULL, sdl.surface32->pixels, sdl.surface32->pitch);
		SDL_RenderClear(sdl.renderer);
		SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
		SDL_RenderPresent(sdl.renderer);
	}

	SDL_SaveBMP(sdl.surface8, "untracked/screenshot.bmp");

	/* quit */
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_DestroyWindow(sdl.window);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyTexture(sdl.texture);
	free_walls();
	free_maskwalls();
	free_floors();
	SDL_FreeSurface(ray.colormap);
	SDL_FreeSurface(ray.textures.sky);
	SDL_FreeSurface(sdl.surface8);
	SDL_FreeSurface(sdl.surface32);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
