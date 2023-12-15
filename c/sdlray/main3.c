
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
	double dt;
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
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,2,0,5,0,2,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,4,0,3,0,0,0,1},
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

typedef struct tile_t {
	uint8_t texture;
	uint8_t height;
} tile_t;

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
	vec2f_t dir;
} camera;

static struct {
	float viewsin;
	float viewcos;
	int horizon;
} ray;

static int ybuffer[WIDTH];

SDL_Surface *wall_textures[4];
SDL_Surface *sky_texture;

bool r_sky = true;
bool r_textures = true;
bool r_texture_stretch = false;

int remap(int value, int a1, int a2, int b1, int b2)
{
	return b1 + (value - a1) * (b2 - b1) / (a2 - a1);
}

int wrap(int value, int mod)
{
	int cmp = value < 0;
	return cmp * mod + (value % mod) - cmp;
}

void draw_vertical_line(int x, int y0, int y1, uint8_t c)
{
	int y;

	if (y0 < y1)
	{
		for (y = y0; y < y1; y++)
		{
			sdl.pixels[y * WIDTH + x] = c;
		}

		ybuffer[x] = y0;
	}
	else if (y1 < y0)
	{
		for (y = y1; y < y0; y++)
		{
			sdl.pixels[y * WIDTH + x] = c;
		}

		ybuffer[x] = y1;
	}
}

int _ray_cast(vec2f_t *side_dist, vec2f_t *delta_dist, vec2i_t *map_pos, vec2i_t *step, int *side)
{
	while (1)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist->x;
			map_pos->x += step->x;
			*side = 0;
		}
		else
		{
			side_dist->y += delta_dist->y;
			map_pos->y += step->y;
			*side = 1;
		}

		/* out of bounds */
		if (map_pos->y < 0 || map_pos->y >= MAP_HEIGHT)
			return 0;
		if (map_pos->x < 0 || map_pos->x >= MAP_WIDTH)
			return 0;

		/* hit */
		if (map[map_pos->y][map_pos->x] > 0)
			return 1;
	}

	return 0;
}

void _ray_draw_column(int x)
{
	vec2f_t ray_dir, delta_dist, side_dist, temp;
	vec2i_t step, map_pos;
	int side;
	float dist;
	int line_start, line_end;
	int line_start_c, line_end_c;
	int y;
	float block_top, block_bottom;
	float pixel_height_scale = HEIGHT / 1.5;

	/* get map pos */
	map_pos.x = (int)camera.x;
	map_pos.y = (int)camera.y;

	/* get ray direction */
	ray_dir.x = ((2.0f / (float)WIDTH) * (float)x) - 1.0f;
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
	while (_ray_cast(&side_dist, &delta_dist, &map_pos, &step, &side))
	{
		/* early out */
		if (!ybuffer[x])
			break;

		/* get dist */
		if (!side)
			dist = side_dist.x - delta_dist.x;
		else
			dist = side_dist.y - delta_dist.y;

		/* line heights */
		block_top = camera.z - map[map_pos.y][map_pos.x];
		block_bottom = camera.z;

		/* line start and end */
		line_start = ((block_top / dist) * pixel_height_scale) + ray.horizon;
		line_end = ((block_bottom / dist) * pixel_height_scale) + ray.horizon;

		/* clamp to screen resolution */
		line_start_c = CLAMP(line_start, 0, ybuffer[x]);
		line_end_c = CLAMP(line_end, 0, ybuffer[x]);

		if (r_sky)
		{
			int tex_x;
			int tex_y;

			tex_x = x - camera.yaw * 4;
			tex_x = wrap(tex_x / 2, sky_texture->w);

			for (y = 0; y < line_start_c; y++)
			{
				tex_y = y - ray.horizon;

				tex_y = wrap(tex_y / 2, sky_texture->h);

				sdl.pixels[y * WIDTH + x] = ((Uint8 *)sky_texture->pixels)[tex_y * sky_texture->w + tex_x];
			}
		}

		if (r_textures)
		{
			/* draw textured line */
			float wall_x;
			int tex_x;
			SDL_Surface *wall_texture;

			/* get texture */
			wall_texture = wall_textures[map[map_pos.y][map_pos.x] & 3];

			/* get wall impact point */
			if (!side)
				wall_x = camera.y + dist * ray_dir.y;
			else
				wall_x = camera.x + dist * ray_dir.x;

			wall_x -= floorf(wall_x);

			/* get texture x coord */
			tex_x = wall_x * wall_texture->w;
			if ((side == 0 && ray_dir.x > 0) || (side == 1 && ray_dir.y < 0))
				tex_x = wall_texture->w - tex_x - 1;

			ybuffer[x] = line_start_c;
			for (y = line_start_c; y < line_end_c; y++)
			{
				int tex_y;

				if (r_texture_stretch)
				{
					tex_y = remap(y, line_start, line_end, 0, wall_texture->h);
				}
				else
				{
					tex_y = remap(y, line_start, line_end, 0, wall_texture->h * map[map_pos.y][map_pos.x]);
					tex_y = wrap(tex_y, wall_texture->h);
				}

				sdl.pixels[y * WIDTH + x] = ((Uint8 *)wall_texture->pixels)[tex_y * wall_texture->w + tex_x];
			}
		}
		else
		{
			/* draw colored line */
			draw_vertical_line(x, line_start, line_end, map[map_pos.y][map_pos.x]);
		}
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
		ybuffer[x] = HEIGHT;
		_ray_draw_column(x);
	}
}

/*
 *
 * MAIN
 *
 */

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

	wall_textures[0] = IMG_Load("gfx/wall1.png");
	wall_textures[1] = IMG_Load("gfx/wall2.png");
	wall_textures[2] = IMG_Load("gfx/wall3.png");
	wall_textures[3] = IMG_Load("gfx/wall4.png");
	sky_texture = IMG_Load("gfx/sky.png");
	install_palette("gfx/palette.dat", wall_textures[0]);
	install_palette("gfx/palette.dat", wall_textures[1]);
	install_palette("gfx/palette.dat", wall_textures[2]);
	install_palette("gfx/palette.dat", wall_textures[3]);
	install_palette("gfx/palette.dat", sky_texture);
	install_palette("gfx/palette.dat", sdl.surface8);

	sdl.pixels = sdl.surface8->pixels;

	sdl.now = SDL_GetPerformanceCounter();
	sdl.last = 0;
	sdl.dt = 0;

	/* setup raycaster */
	camera.x = MAP_WIDTH / 2;
	camera.y = MAP_HEIGHT / 2;
	camera.z = 0.5;
	camera.shear = 0;
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
		sdl.dt = ((double)(sdl.now - sdl.last) / (double)SDL_GetPerformanceFrequency());

		/* get look direction */
		camera.dir.x = ray.viewsin * sdl.dt * 2;
		camera.dir.y = ray.viewcos * sdl.dt * 2;

		/* process player inputs */
		if (sdl.keys[SDL_SCANCODE_W])
		{
			camera.x += camera.dir.x;
			camera.y += camera.dir.y;
		}
		if (sdl.keys[SDL_SCANCODE_S])
		{
			camera.x -= camera.dir.x;
			camera.y -= camera.dir.y;
		}
		if (sdl.keys[SDL_SCANCODE_A])
		{
			camera.x += camera.dir.y;
			camera.y -= camera.dir.x;
		}
		if (sdl.keys[SDL_SCANCODE_D])
		{
			camera.x -= camera.dir.y;
			camera.y += camera.dir.x;
		}

		/* render */
		memset(sdl.surface8->pixels, 0, sdl.surface8->h * sdl.surface8->pitch);
		camera.shear = CLAMP(camera.shear, -150, 150);
		ray_render();

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
	SDL_FreeSurface(wall_textures[0]);
	SDL_FreeSurface(wall_textures[1]);
	SDL_FreeSurface(wall_textures[2]);
	SDL_FreeSurface(wall_textures[3]);
	SDL_FreeSurface(sky_texture);
	SDL_FreeSurface(sdl.surface8);
	SDL_FreeSurface(sdl.surface32);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
