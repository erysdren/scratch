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

#pragma once
#ifndef _RAY_H_
#define _RAY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "SDL.h"

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

typedef struct vec2i_t {
	int x, y;
} vec2i_t;

typedef struct vec2f_t {
	float x, y;
} vec2f_t;

typedef struct vec3f_t {
	float x, y, z;
} vec3f_t;

/* tile */
typedef struct tile_t {
	uint8_t height;
	int8_t texture;
	int8_t floor_texture;
	int8_t light;
	int8_t side;
} tile_t;

/* ray state and configuration */
typedef struct ray_t {
	struct {
		bool draw_sky;
		bool draw_wall_textures;
		bool stretch_wall_textures;
		bool draw_floor_textures;
		bool draw_ceiling_textures;
	} config;
	struct {
		uint8_t width;
		uint8_t height;
		tile_t *tiles;
		int8_t light_scale;
		int8_t light_level;
		uint8_t ceiling;
	} tilemap;
	struct {
		vec3f_t origin;
		int pitch;
		int yaw;
	} camera;
	struct {
		int num_floors;
		SDL_Surface **floors;
		int num_walls;
		SDL_Surface **walls;
		int num_maskwalls;
		SDL_Surface **maskwalls;
		SDL_Surface *sky;
	} textures;
	SDL_Surface *dest;
	SDL_Surface *colormap;
	SDL_Surface *font;
	SDL_Surface *crosshair;
} ray_t;

/* get tile at x,y */
#define RAY_TILE_AT(r, x, y) (r)->tilemap.tiles[(y) * (r)->tilemap.width + (x)]

/* draw ray */
void ray_draw(ray_t *ray);

/* print text to screen */
void ray_print(ray_t *ray, int x, int y, char *s);

/* print formatted text to screen */
void ray_printf(ray_t *ray, int x, int y, char *s, ...);

/* fill area with color */
void ray_fill(ray_t *ray, int x, int y, int w, int h, uint8_t c);

/* init ray structure */
void ray_init(ray_t *ray);

#ifdef __cplusplus
}
#endif
#endif /* _RAY_H_ */
