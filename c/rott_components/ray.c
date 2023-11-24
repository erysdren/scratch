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

#include <stdio.h>
#include <string.h>

#include "math.h"
#include "fix32.h"
#include "pixelmap.h"
#include "ray.h"

/* basic map */
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
static uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {
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

/* state */
static struct {
	int width;
	int height;
	int len_wall;
	void *walls;
	fix32_t player_origin_x;
	fix32_t player_origin_y;
	int player_angle;
} ray;

/* initialize raycaster */
bool ray_init(int width, int height, int len_wall, void *walls)
{
	if (!width || !height || !len_wall || !walls)
		return false;

	memset(&ray, 0, sizeof(ray));

	ray.width = width;
	ray.height = height;
	ray.len_wall = len_wall;
	ray.walls = walls;

	return true;
}

/* quit raycaster */
void ray_quit(void)
{

}

/* run one frame of raycaster */
void ray_render(pixelmap_t *dst)
{
	/* some constants for mode 02h */
	int draw_w = dst->width;
	int draw_h = dst->height;

	/* current pixel position */
	int x, y;

	ray.player_origin_x = FIX32(12);
	ray.player_origin_y = FIX32(12);

	/* lookup sin and cos of player's view */
	fix32_t sn = FIX32_SIN(ray.player_angle);
	fix32_t cs = FIX32_COS(ray.player_angle);

	/* ray sweep loop */
	for (x = 0; x < draw_w; x++)
	{
		int step_x, step_y;
		fix32_t side_dist_x, side_dist_y;
		bool hit = false, side = false, oob = false;
		fix32_t dist;

		/* get map position */
		int16_t map_pos_x = FIX32_TO_INT(ray.player_origin_x);
		int16_t map_pos_y = FIX32_TO_INT(ray.player_origin_y);

		/* calculate ray direction */
		fix32_t raydir_x = FIX32_MUL(FIX32_DIV(FIX32(2.0f), FIX32(draw_w)), FIX32(x)) - FIX32(1.0f);
		fix32_t raydir_y = FIX32(1.0f);

		/* rotate around 0,0 by player_angle */
		fix32_t temp_x = raydir_x;
		fix32_t temp_y = raydir_y;
		raydir_x = FIX32_MUL(-temp_x, cs) - FIX32_MUL(-temp_y, sn);
		raydir_y = FIX32_MUL(temp_x, sn) + FIX32_MUL(temp_y, cs);

		/* prevent divide by zero */
		fix32_t delta_dist_x = (raydir_x == 0) ? FIX32_MAX : abs(FIX32_DIV(FIX32(1.0f), raydir_x));
		fix32_t delta_dist_y = (raydir_y == 0) ? FIX32_MAX : abs(FIX32_DIV(FIX32(1.0f), raydir_y));

		/* calculate x step and side_dist */
		if (raydir_x < 0)
		{
			step_x = -1;
			side_dist_x = FIX32_MUL((ray.player_origin_x - FIX32(map_pos_x)), delta_dist_x);
		}
		else
		{
			step_x = 1;
			side_dist_x = FIX32_MUL((FIX32(map_pos_x) + FIX32(1) - ray.player_origin_x), delta_dist_x);
		}

		/* calculate y step and side_dist */
		if (raydir_y < 0)
		{
			step_y = -1;
			side_dist_y = FIX32_MUL((ray.player_origin_y - FIX32(map_pos_y)), delta_dist_y);
		}
		else
		{
			step_y = 1;
			side_dist_y = FIX32_MUL((FIX32(map_pos_y) + FIX32(1.0f) - ray.player_origin_y), delta_dist_y);
		}

		/* perform dda */
		while (hit == false && oob == false)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_pos_x += step_x;
				side = false;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_pos_y += step_y;
				side = true;
			}

			/* check if the ray hit a wall */
			if (map[map_pos_y][map_pos_x] > 0)
				hit = true;

			/* check if ray has gone out of bounds */
			if (map_pos_y >= MAP_HEIGHT || map_pos_y < 0 || map_pos_x >= MAP_WIDTH || map_pos_x < 0)
				oob = true;
		}

		/* move to next ray if we've gone out of bounds */
		if (oob == true)
			continue;

		/* check if we've hit a side or not */
		if (side == false)
			dist = (side_dist_x - delta_dist_x);
		else
			dist = (side_dist_y - delta_dist_y);

		/* prevent divide by zero */
		if (dist <= FIX32(0))
			continue;

		/* height of line to draw on screen */
		int line_height = FIX32_TO_INT(FIX32_DIV(FIX32(draw_h), dist));

		int line_start = -line_height / 2 + draw_h / 2;
		int line_end = line_height / 2 + draw_h / 2;

		/* clamp to vertical area */
		line_start = clamp(line_start, 0, draw_h);
		line_end = clamp(line_end, 0, draw_h);

		/* draw */
		for (y = line_start; y < line_end; y++)
		{
			pixelmap_pixel8(dst, x, y) = map[map_pos_y][map_pos_x];
		}
	}
}
