
/*
 * http://advsys.net/ken/voxlap.htm
 * https://lodev.org/cgtutor/raycasting.html
 * https://github.com/s-macke/VoxelSpace/
 */

#include <math.h>
#include <float.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"

#define WIDTH 640
#define HEIGHT 480

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef CLAMP
#define CLAMP(a, min, max) MIN(MAX(a, min), max)
#endif

#ifndef DEG2RAD
#define DEG2RAD(a) ((a) * M_PI / 180.0f)
#endif

#ifndef RAD2DEG
#define RAD2DEG(a) ((a) * 180.0f / M_PI)
#endif

static struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface8;
	SDL_Surface *surface32;
	SDL_Texture *texture;
	SDL_Rect rect;
	SDL_Event event;
	SDL_bool running;
	Uint8 *pixels;
	const Uint8 *keys;
	Uint64 now;
	Uint64 last;
	float dt;
} sdl;

/*
 *
 * RAYCASTER
 *
 */

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
uint8_t map[MAP_HEIGHT][MAP_WIDTH]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct vec2i_t {
	int x, y;
} vec2i_t;

typedef struct vec2f_t {
	float x, y;
} vec2f_t;

static struct {
	float x;
	float y;
	float z;
	float yaw;
	float draw_distance;
	int shear;
} camera;

static struct {
	float viewsin;
	float viewcos;
	int horizon;
} ray;

int _ray_cast(vec2f_t *side_dist, vec2f_t *delta_dist, vec2i_t *map_pos, vec2i_t *step)
{
	int side;

	while (1)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist->x;
			map_pos->x += step->x;
			side = 0;
		}
		else
		{
			side_dist->y += delta_dist->y;
			map_pos->y += step->y;
			side = 1;
		}

		/* out of bounds */
		if (map_pos->y < 0 || map_pos->y >= MAP_HEIGHT || map_pos->x < 0 || map_pos->x >= MAP_WIDTH)
			break;

		/* hit */
		if (map[map_pos->y][map_pos->x] > 0)
			break;
	}

	return side;
}

void _ray_draw_column(int column)
{
	vec2f_t ray_dir, delta_dist, side_dist, temp;
	vec2i_t step, map_pos;
	int side;
	float perp_wall_dist;
	int line_start;
	int line_end;
	int line_height;
	int y;

	/* get map pos */
	map_pos.x = (int)camera.x;
	map_pos.y = (int)camera.y;

	/* get ray direction */
	ray_dir.x = ((2.0f / (float)WIDTH) * (float)column) - 1.0f;
	ray_dir.y = 1.0f;

	/* rotate around (0, 0) by camera yaw */
	temp = ray_dir;
	ray_dir.x = (-temp.x * ray.viewcos) - (-temp.y * ray.viewsin);
	ray_dir.y = (temp.x * ray.viewsin) + (temp.y * ray.viewcos);

	/* get delta of ray (prevent divide by 0) */
	delta_dist.x = (ray_dir.x == 0.0f) ? FLT_MAX : fabs(1.0f / ray_dir.x);
	delta_dist.y = (ray_dir.y == 0.0f) ? FLT_MAX : fabs(1.0f / ray_dir.y);

	/* get step and initial side_dist */
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (camera.x - (float)map_pos.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = ((float)map_pos.x + 1.0f - camera.x) * delta_dist.x;
	}

	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (camera.y - (float)map_pos.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = ((float)map_pos.y + 1.0f - camera.y) * delta_dist.y;
	}

	/* do dda */
	side = _ray_cast(&side_dist, &delta_dist, &map_pos, &step);

	/* get perp_wall_dist */
	if (!side)
		perp_wall_dist = side_dist.x - delta_dist.x;
	else
		perp_wall_dist = side_dist.y - delta_dist.y;

	/* calculate line height */
	line_height = HEIGHT / perp_wall_dist;

	/* line start and end */
	line_start = (-line_height / 2 + HEIGHT / 2) + ray.horizon;
	line_end = (line_height / 2 + HEIGHT / 2) + ray.horizon;

	/* clamp to screen resolution */
	line_start = CLAMP(line_start, 0, HEIGHT);
	line_end = CLAMP(line_end, 0, HEIGHT);

	/* draw line */
	for (y = line_start; y < line_end; y++)
	{
		sdl.pixels[y * WIDTH + column] = 31;
	}
}

void ray_render(void)
{
	int x;

	/* get sin and cos of camera yaw */
	ray.viewsin = sinf(DEG2RAD(camera.yaw));
	ray.viewcos = cosf(DEG2RAD(camera.yaw));

	/* calculate camera horizon */
	ray.horizon = -camera.shear + (HEIGHT / 2);

	/* ray sweep loop */
	for (x = 0; x < WIDTH; x++)
	{
		_ray_draw_column(x);
	}
}

/*
 *
 * MAIN
 *
 */

SDL_bool install_palette(const char *filename)
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

	SDL_SetPaletteColors(sdl.surface8->format->palette, colors, 0, 256);

	fclose(file);

	return SDL_TRUE;
}

int main(int argc, char **argv)
{
	uint32_t pixel_format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	sdl.window = SDL_CreateWindow("sdlray",
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

	SDL_SetRelativeMouseMode(SDL_TRUE);

	install_palette("palette.dat");

	sdl.pixels = sdl.surface8->pixels;

	sdl.now = SDL_GetPerformanceCounter();
	sdl.last = 0;
	sdl.dt = 0;

	/* setup raycaster */
	camera.x = MAP_WIDTH / 2;
	camera.y = MAP_HEIGHT / 2;
	camera.z = 0.5;
	camera.shear = HEIGHT / 2;
	camera.draw_distance = MAP_WIDTH * 2;

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
					camera.shear += sdl.event.motion.yrel;
					camera.yaw -= sdl.event.motion.xrel;
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
		sdl.dt = ((float)(sdl.now - sdl.last) / (float)SDL_GetPerformanceFrequency());

		/* render */
		memset(sdl.surface8->pixels, 0, sdl.surface8->h * sdl.surface8->pitch);
		ray_render();

		/* blit to screen */
		SDL_BlitSurface(sdl.surface8, &sdl.rect, sdl.surface32, &sdl.rect);
		SDL_UpdateTexture(sdl.texture, NULL, sdl.surface32->pixels, sdl.surface32->pitch);
		SDL_RenderClear(sdl.renderer);
		SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
		SDL_RenderPresent(sdl.renderer);
	}

	/* quit */
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_DestroyWindow(sdl.window);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyTexture(sdl.texture);
	SDL_FreeSurface(sdl.surface8);
	SDL_FreeSurface(sdl.surface32);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
