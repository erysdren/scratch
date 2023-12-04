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
#include "actor.h"
#include "cvar.h"
#include "engine.h"
#include "utils.h"
#include "console.h"

/* state */
static struct {
	int width;
	int height;
	uint16_t *walls;
} ray;

/* initialize raycaster */
bool ray_init(level_t *level)
{
	if (!level)
		return false;

	memset(&ray, 0, sizeof(ray));

	ray.width = level->width;
	ray.height = level->height;
	ray.walls = level->planes[0];

	return true;
}

/* quit raycaster */
void ray_quit(void)
{

}

/* run one frame of raycaster */
void ray_render(pixelmap_t *dst, actor_t *camera, int ceiling)
{
	/* current pixel position */
	int x, y;
	fix32_t sn, cs;

	/* lookup sin and cos of player's view */
	sn = FIX32_SIN(camera->yaw);
	cs = FIX32_COS(camera->yaw);

	/* ray sweep loop */
	for (x = 0; x < dst->width; x++)
	{
		vec2i_t map_pos, step;
		vec2_t side_dist, delta_dist, temp, raydir;
		bool hit = false, side = false, oob = false;
		fix32_t dist;
		int line_height, line_start, line_end;

		/* get map position */
		map_pos.x = FIX32_TO_INT(camera->origin.x);
		map_pos.y = FIX32_TO_INT(camera->origin.y);

		/* calculate ray direction */
		raydir.x = FIX32_MUL(FIX32_DIV(FIX32(2.0f), FIX32(dst->width)), FIX32(x)) - FIX32(1.0f);
		raydir.y = FIX32(1.0f);

		/* rotate around 0,0 by player_angle */
		temp.x = raydir.x;
		temp.y = raydir.y;
		raydir.x = FIX32_MUL(-temp.x, cs) - FIX32_MUL(-temp.y, sn);
		raydir.y = FIX32_MUL(temp.x, sn) + FIX32_MUL(temp.y, cs);

		/* prevent divide by zero */
		delta_dist.x = (raydir.x == 0) ? FIX32_MAX : abs(FIX32_DIV(FIX32(1.0f), raydir.x));
		delta_dist.y = (raydir.y == 0) ? FIX32_MAX : abs(FIX32_DIV(FIX32(1.0f), raydir.y));

		/* calculate x step and side_dist */
		if (raydir.x < 0)
		{
			step.x = -1;
			side_dist.x = FIX32_MUL((camera->origin.x - FIX32(map_pos.x)), delta_dist.x);
		}
		else
		{
			step.x = 1;
			side_dist.x = FIX32_MUL((FIX32(map_pos.x) + FIX32(1) - camera->origin.x), delta_dist.x);
		}

		/* calculate y step and side_dist */
		if (raydir.y < 0)
		{
			step.y = -1;
			side_dist.y = FIX32_MUL((camera->origin.y - FIX32(map_pos.y)), delta_dist.y);
		}
		else
		{
			step.y = 1;
			side_dist.y = FIX32_MUL((FIX32(map_pos.y) + FIX32(1.0f) - camera->origin.y), delta_dist.y);
		}

		/* perform dda */
		while (hit == false && oob == false)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map_pos.x += step.x;
				side = false;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map_pos.y += step.y;
				side = true;
			}

			/* check if the ray hit a wall */
			if (ray.walls[map_pos.y * ray.width + map_pos.x] > 0)
				hit = true;

			/* check if ray has gone out of bounds */
			if (map_pos.y >= ray.height || map_pos.y < 0 || map_pos.x >= ray.width || map_pos.x < 0)
				oob = true;
		}

		/* move to next ray if we've gone out of bounds */
		if (oob == true)
			continue;

		/* check if we've hit a side or not */
		if (side == false)
			dist = (side_dist.x - delta_dist.x);
		else
			dist = (side_dist.y - delta_dist.y);

		/* prevent divide by zero */
		if (dist <= FIX32(0))
			continue;

		/* height of line to draw on screen */
		line_height = FIX32_TO_INT(FIX32_DIV(FIX32(dst->height), dist));

		/* start and end points */
		line_start = -line_height / 2 + dst->height / 2;
		line_end = line_height / 2 + dst->height / 2;

		/* add ceiling */
		line_start -= line_height * (ceiling - 1);

		/* clamp to vertical area */
		line_start = clamp(line_start, 0, dst->height);
		line_end = clamp(line_end, 0, dst->height);

		/* draw */
		if (cvar_get_bool("r_textures"))
		{
			fix32_t wall_x;
			fix32_t step;
			fix32_t texcoord;
			int tex_x;
			int tex_y;
			int wallnum;

			/* get wall num */
			wallnum = ray.walls[map_pos.y * ray.width + map_pos.x] - 1;

			/* get x coordinate on wall */
			if (side == false)
				wall_x = camera->origin.y + FIX32_MUL(dist, raydir.y);
			else
				wall_x = camera->origin.x + FIX32_MUL(dist, raydir.x);

			/* keep past the decimal only */
			wall_x -= FIX32_FLOOR(wall_x);

			/* get x coordinate on texture */
			tex_x = FIX32_TO_INT(FIX32_MUL(wall_x, FIX32(64)));

			/* get x coordinate on wall */
			if (side == false && raydir.x > 0)
				tex_x = 64 - tex_x - 1;
			if (side == true && raydir.y < 0)
				tex_x = 64 - tex_x - 1;

			/* texcoord per screen pixel */
			step = FIX32_DIV(FIX32(64), FIX32(line_height));

			/* starting texture coord */
			texcoord = FIX32_MUL(FIX32(line_start - (dst->height / 2) + (line_height / 2)), step);

			/* draw texture */
			for (y = line_start; y < line_end; y++)
			{
				tex_x = abs(tex_x) & 63;
				tex_y = abs(FIX32_TO_INT(texcoord)) & 63;
				texcoord += step;
				pixelmap_pixel8(dst, x, y) = pixelmap_pixel8(engine.walls[wallnum], tex_x, tex_y);
			}
		}
		else
		{
			/* draw solid color */
			for (y = line_start; y < line_end; y++)
			{
				pixelmap_pixel8(dst, x, y) = 15;
			}
		}
	}
}
