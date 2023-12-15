
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
	double dt;
} sdl;

/*
 *
 * RAYCASTER
 *
 */

/* voxel slab */
typedef struct slab_t {
	uint8_t voxels_skipped;
	uint8_t voxels_drawn;
	uint8_t color_side;
	uint8_t color_top;
	uint8_t color_bottom;
} slab_t;

/* voxel column */
typedef struct column_t {
	int num_slabs;
	slab_t *slabs;
} column_t;

typedef struct vec2i_t {
	int x, y;
} vec2i_t;

typedef struct vec2f_t {
	float x, y;
} vec2f_t;

static column_t map[10][10];

static struct {
	struct {
		float x;
		float y;
		float z;
		float yaw;
		int shear;
		float drawdist;
	} cam;

	struct {
		int x;
		int y;
		int z;
	} map;

	float viewsin;
	float viewcos;
	int horizon;
} ray;

static uint8_t ybuffer[HEIGHT];

void draw_vertical_line(int x, int y0, int y1, uint8_t c)
{
	int y;

	if (y0 == y1)
	{
		if (ybuffer[y0])
			return;

		sdl.pixels[y0 * WIDTH + x] = c;
		ybuffer[y0] = 1;
	}
	else if (y0 < y1)
	{
		for (y = y0; y < y1; y++)
		{
			if (ybuffer[y])
				continue;

			sdl.pixels[y * WIDTH + x] = c;
			ybuffer[y] = 1;
		}
	}
	else if (y1 < y0)
	{
		for (y = y1; y < y0; y++)
		{
			if (ybuffer[y])
				continue;

			sdl.pixels[y * WIDTH + x] = c;
			ybuffer[y] = 1;
		}
	}
}

int _ray_draw_slab(int screen_x, slab_t *slab, int column_height, float dist, float dist2, float pixel_height_scale)
{
	float slab_z, slab_height, height_delta1, height_delta2;
	int line_start, line_end;
	int screen_y;

	/* z position of the slab */
	slab_z = column_height - slab->voxels_skipped;

	/* height of the slab */
	slab_height = slab->voxels_drawn;

	/* height deltas */
	height_delta1 = ray.cam.z - slab_z;
	height_delta2 = ray.cam.z - (slab_z - slab_height);

	/*
	 * draw the side of the voxel
	 */

	/* height of the line on screen to draw */
	line_start = (int)((height_delta1 / dist) * pixel_height_scale) + ray.horizon;
	line_end = (int)((height_delta2 / dist) * pixel_height_scale) + ray.horizon;

	/* clamp the line to the visible region */
	line_start = CLAMP(line_start, 0, HEIGHT);
	line_end = CLAMP(line_end, 0, HEIGHT);

	/* draw line */
	draw_vertical_line(screen_x, line_start, line_end, slab->color_side);

	/*
	 * draw the top or bottom of the voxel
	 */

	if (dist2 > (dist + 1.0f))
		dist2 = dist + 1.0f;

	/* height of the line on screen to draw */
	line_start = (int)((height_delta1 / dist2) * pixel_height_scale) + ray.horizon;
	line_end = (int)((height_delta2 / dist2) * pixel_height_scale) + ray.horizon;

	/* clamp the line to the visible region */
	line_start = CLAMP(line_start, 0, HEIGHT);
	line_end = CLAMP(line_end, 0, HEIGHT);

	/* draw line */
	draw_vertical_line(screen_x, line_start, line_end, slab->color_bottom);

	return column_height - (slab->voxels_skipped + slab->voxels_drawn);
}

void _ray_draw_column(int screen_x, column_t *column, float dist, float dist2, float pixel_height_scale)
{
	slab_t *slab;
	int column_height;

	column_height = ray.map.z;

	for (int i = 0; i < column->num_slabs; i++)
	{
		/* get slab */
		slab = &column->slabs[i];

		/* draw slab */
		column_height = _ray_draw_slab(screen_x, slab, column_height, dist, dist2, pixel_height_scale);
	}
}

int _ray_dda(int screen_x, vec2f_t *side_dist, vec2f_t *delta_dist, vec2i_t *step, vec2i_t *map_pos)
{
	int side;
	float dist, dist2;
	column_t *column;

	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist->x;
		map_pos->x += step->x;
		side = 1;
	}
	else
	{
		side_dist->y += delta_dist->y;
		map_pos->y += step->y;
		side = 2;
	}

	switch (side)
	{
		case 1:
			dist = side_dist->x - delta_dist->x;
			dist2 = side_dist->y;
			break;

		case 2:
			dist = side_dist->y - delta_dist->y;
			dist2 = side_dist->x;
			break;
	}

	/* if it goes beyond the draw distance, cut off the ray */
	if (dist > ray.cam.drawdist)
		return 0;

	/* if out of bounds, keep going in hopes of finding something in-bounds again */
	/* this allows rendering the map from an out of bounds location */
	if (map_pos->x >= ray.map.x || map_pos->x < 0)
		return 1;
	if (map_pos->y >= ray.map.y || map_pos->y < 0)
		return 1;

	if (dist < 1.0f || dist2 < 1.0f)
		return 1;

	/* get column */
	column = &map[map_pos->y][map_pos->x];

	/* draw column */
	_ray_draw_column(screen_x, column, dist, dist2, HEIGHT / 2);

	return 1;
}

void _ray_draw_screen_column(int screen_x)
{
	vec2f_t ray_dir, delta_dist, side_dist, temp;
	vec2i_t step, map_pos;

	/* get map pos */
	map_pos.x = (int)ray.cam.x;
	map_pos.y = (int)ray.cam.y;

	/* get ray direction */
	ray_dir.x = ((2.0f / (float)WIDTH) * (float)screen_x) - 1.0f;
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
		side_dist.x = (ray.cam.x - (float)map_pos.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = ((float)map_pos.x + 1.0f - ray.cam.x) * delta_dist.x;
	}

	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (ray.cam.y - (float)map_pos.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = ((float)map_pos.y + 1.0f - ray.cam.y) * delta_dist.y;
	}

	/* march the ray for this column */
	while (_ray_dda(screen_x, &side_dist, &delta_dist, &step, &map_pos));
}

void ray_render(void)
{
	/* get sin and cos of camera yaw */
	ray.viewsin = sinf(ray.cam.yaw);
	ray.viewcos = cosf(ray.cam.yaw);

	/* get horizon from camera shear */
	ray.horizon = -ray.cam.shear + (HEIGHT / 2);

	/* ray sweep loop */
	for (int x = 0; x < WIDTH; x++)
	{
		/* clear stencil */
		memset(ybuffer, 0, sizeof(ybuffer));

		/* draw screen column */
		_ray_draw_screen_column(x);
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
	slab_t tempslab;

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

	/* setup ray */
	memset(&ray, 0, sizeof(ray));
	ray.map.x = 10;
	ray.map.y = 10;
	ray.map.z = 10;
	ray.cam.drawdist = 25;
	ray.cam.x = 4;
	ray.cam.y = 4;
	ray.cam.z = 6;

	/* setup map */
	memset(map, 0, sizeof(map));
	tempslab.voxels_skipped = 0;
	tempslab.voxels_drawn = 1;
	tempslab.color_bottom = 0;
	tempslab.color_top = 15;
	tempslab.color_side = 31;

	map[0][0].num_slabs = 1;
	map[0][0].slabs = &tempslab;

	map[9][0].num_slabs = 1;
	map[9][0].slabs = &tempslab;

	map[7][0].num_slabs = 1;
	map[7][0].slabs = &tempslab;

	map[0][9].num_slabs = 1;
	map[0][9].slabs = &tempslab;

	map[9][9].num_slabs = 1;
	map[9][9].slabs = &tempslab;

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
					ray.cam.shear += sdl.event.motion.yrel;
					ray.cam.yaw -= sdl.event.motion.xrel * sdl.dt;
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

		/* render */
		memset(sdl.surface8->pixels, 255, sdl.surface8->h * sdl.surface8->pitch);
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
