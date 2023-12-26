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
 * RAY.C
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include <math.h>
#include <float.h>

#include "ray.h"

typedef struct hit_t {
	float viewsin;
	float viewcos;
	int horizon;
	vec2f_t ray_dir;
	vec2f_t delta_dist;
	vec2f_t side_dist;
	vec2i_t step;
	vec2i_t map_pos;
	int side;
} hit_t;

/* ray hit result enum */
enum {
	HIT_DONE = 0,
	HIT_SKY = 1,
	HIT_WALL = 2,
	HIT_MASK = 3
};

int remap(int value, int a1, int a2, int b1, int b2)
{
	return b1 + (value - a1) * (b2 - b1) / (a2 - a1);
}

int wrap(int value, int mod)
{
	int cmp = value < 0;
	return cmp * mod + (value % mod) - cmp;
}

uint8_t colormap_lookup(ray_t *ray, uint8_t color, int brightness)
{
	int x, y;

	x = color;
	y = CLAMP(-brightness + 31, 0, 63);

	return ((uint8_t *)ray->colormap->pixels)[y * ray->colormap->pitch + x];
}

int ray_cast(ray_t *ray, hit_t *hit)
{
	tile_t *tile = NULL;

	while (1)
	{
		if (hit->side_dist.x < hit->side_dist.y)
		{
			hit->side_dist.x += hit->delta_dist.x;
			hit->map_pos.x += hit->step.x;
			hit->side = 0;
		}
		else
		{
			hit->side_dist.y += hit->delta_dist.y;
			hit->map_pos.y += hit->step.y;
			hit->side = 1;
		}

		/* out of bounds */
		if (hit->map_pos.y < 0 || hit->map_pos.y >= ray->tilemap.height)
			return HIT_DONE;
		if (hit->map_pos.x < 0 || hit->map_pos.x >= ray->tilemap.width)
			return HIT_DONE;

		/* get tile */
		tile = &RAY_TILE_AT(ray, hit->map_pos.x, hit->map_pos.y);

		/* hit */
		if (tile->height > 0)
		{
			if (tile->texture < 0)
			{
				hit->side = tile->side;
				return HIT_MASK;
			}
			else
			{
				return HIT_WALL;
			}
		}

		if (hit->map_pos.x == 0 || hit->map_pos.x == ray->tilemap.width - 1)
			return HIT_SKY;
		if (hit->map_pos.y == 0 || hit->map_pos.y == ray->tilemap.height - 1)
			return HIT_SKY;
	}

	return HIT_DONE;
}

void ray_draw_floor(ray_t *ray, hit_t *hit, int x, int y, int pixel_height_scale)
{
	float rowdist;
	vec2f_t floorpos;
	tile_t *tile;
	vec2i_t texpos;
	uint8_t color;
	SDL_Surface *texture;
	int light;

	rowdist = (ray->camera.origin.z * pixel_height_scale) / (y - hit->horizon);

	floorpos.x = ray->camera.origin.x + rowdist * hit->ray_dir.x;
	floorpos.y = ray->camera.origin.y + rowdist * hit->ray_dir.y;

	if (floorpos.y < 0 || floorpos.y >= ray->tilemap.height)
		return;
	if (floorpos.x < 0 || floorpos.x >= ray->tilemap.width)
		return;

	tile = &RAY_TILE_AT(ray, (int)floorpos.x, (int)floorpos.y);

	texture = ray->textures.floors[tile->floor_texture];

	texpos.x = wrap(floorpos.x * texture->w, texture->w);
	texpos.y = wrap(floorpos.y * texture->h, texture->h);

	color = ((Uint8 *)texture->pixels)[texpos.y * texture->pitch + texpos.x];

	light = rowdist * ray->tilemap.light_scale + ray->tilemap.light_level + tile->light;

	((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = colormap_lookup(ray, color, light);
}

void ray_draw_column(int x, ray_t *ray, hit_t *hit)
{
	vec2f_t temp;
	float dist, dist2;
	int line_start, line_end;
	int line_start_c, line_end_c;
	int y;
	float block_top, block_bottom;
	float pixel_height_scale = ray->dest->h / 1.5;
	int ystart = ray->dest->h;
	int floorstart = 0;
	int hittype;
	uint8_t stencil[ray->dest->h];
	int light;
	tile_t *tile;

	/* reset stencil buffer */
	memset(stencil, 0, sizeof(stencil));

	/* get map pos */
	hit->map_pos.x = (int)ray->camera.origin.x;
	hit->map_pos.y = (int)ray->camera.origin.y;

	/* get ray direction */
	hit->ray_dir.x = ((2.0f / (float)ray->dest->w) * (float)x) - 1.0f;
	hit->ray_dir.y = 1.0f;

	/* rotate around (0, 0) by camera yaw */
	temp = hit->ray_dir;
	hit->ray_dir.x = (-temp.x * hit->viewcos) - (-temp.y * hit->viewsin);
	hit->ray_dir.y = (temp.x * hit->viewsin) + (temp.y * hit->viewcos);

	/* get delta of ray (prevent divide by 0) */
	hit->delta_dist.x = (hit->ray_dir.x == 0.0f) ? FLT_MAX : fabs(1.0f / hit->ray_dir.x);
	hit->delta_dist.y = (hit->ray_dir.y == 0.0f) ? FLT_MAX : fabs(1.0f / hit->ray_dir.y);

	/* get step and initial side_dist */
	if (hit->ray_dir.x < 0)
	{
		hit->step.x = -1;
		hit->side_dist.x = (ray->camera.origin.x - (float)hit->map_pos.x) * hit->delta_dist.x;
	}
	else
	{
		hit->step.x = 1;
		hit->side_dist.x = ((float)hit->map_pos.x + 1.0f - ray->camera.origin.x) * hit->delta_dist.x;
	}

	if (hit->ray_dir.y < 0)
	{
		hit->step.y = -1;
		hit->side_dist.y = (ray->camera.origin.y - (float)hit->map_pos.y) * hit->delta_dist.y;
	}
	else
	{
		hit->step.y = 1;
		hit->side_dist.y = ((float)hit->map_pos.y + 1.0f - ray->camera.origin.y) * hit->delta_dist.y;
	}

	/* do cast */
	while ((hittype = ray_cast(ray, hit)) != HIT_DONE)
	{
		/* early out */
		if (!ystart)
			break;

		/* get dist */
		if (!hit->side)
		{
			dist = hit->side_dist.x - hit->delta_dist.x;
			dist2 = CLAMP(hit->side_dist.y, dist, dist + hit->delta_dist.x);

			if (hittype == HIT_MASK)
			{
				if (dist + (hit->delta_dist.x / 2) < hit->side_dist.y - hit->delta_dist.y)
					continue;
				else if (dist + (hit->delta_dist.x / 2) > dist2)
					continue;
				else
					dist += hit->delta_dist.x / 2;
			}
			else if (hittype == HIT_SKY)
			{
				dist = hit->side_dist.x;
			}
		}
		else
		{
			dist = hit->side_dist.y - hit->delta_dist.y;
			dist2 = CLAMP(hit->side_dist.x, dist, dist + hit->delta_dist.y);

			if (hittype == HIT_MASK)
			{
				if (dist + (hit->delta_dist.y / 2) < hit->side_dist.x - hit->delta_dist.x)
					continue;
				else if (dist + (hit->delta_dist.y / 2) > dist2)
					continue;
				else
					dist += hit->delta_dist.y / 2;
			}
			else if (hittype == HIT_SKY)
			{
				dist = hit->side_dist.y;
			}
		}

		/* get tile */
		tile = &RAY_TILE_AT(ray, hit->map_pos.x, hit->map_pos.y);

		/* line heights */
		block_top = ray->camera.origin.z - tile->height * 0.125f;
		block_bottom = ray->camera.origin.z;

		/* line start and end */
		line_start = ((block_top / dist) * pixel_height_scale) + hit->horizon;
		line_end = ((block_bottom / dist) * pixel_height_scale) + hit->horizon;

		/* clamp to screen resolution */
		line_start_c = CLAMP(line_start, 0, ystart);
		line_end_c = CLAMP(line_end, 0, ystart);

		/* set floorstart */
		if (floorstart < line_end_c && hittype == HIT_WALL)
			floorstart = line_end_c;

		/* draw floors */
		if (ray->config.draw_floor_textures)
		{
			/* upper floor */
			for (y = line_end_c; y < ystart; y++)
			{
				if (!stencil[y])
				{
					ray_draw_floor(ray, hit, x, y, pixel_height_scale);
				}
			}

			/* lower floor */
			for (y = floorstart; y < ray->dest->h; y++)
			{
				if (!stencil[y])
				{
					ray_draw_floor(ray, hit, x, y, pixel_height_scale);
				}
			}
		}
		else
		{
			/* upper floor */
			for (y = line_end_c; y < ystart; y++)
			{
				if (!stencil[y])
					((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = 0;
			}

			/* lower floor */
			for (y = floorstart; y < ray->dest->h; y++)
			{
				if (!stencil[y])
					((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = 0;
			}
		}

		/* draw walls */
		if (ray->config.draw_wall_textures && tile->height > 0)
		{
			float wall_x;
			int tex_x;
			SDL_Surface *tex;

			/* get texture */
			if (hittype == HIT_MASK)
				tex = ray->textures.maskwalls[(tile->texture * -1) - 1];
			else
				tex = ray->textures.walls[tile->texture - 1];

			/* get wall impact point */
			if (!hit->side)
				wall_x = ray->camera.origin.y + dist * hit->ray_dir.y;
			else
				wall_x = ray->camera.origin.x + dist * hit->ray_dir.x;

			wall_x -= floorf(wall_x);

			/* get texture x coord */
			tex_x = wall_x * tex->w;
			if ((hit->side == 0 && hit->ray_dir.x > 0) || (hit->side == 1 && hit->ray_dir.y < 0))
				tex_x = tex->w - tex_x - 1;

			/* flip x coord */
			tex_x = (tex_x - tex->w) * -1;

			light = dist * ray->tilemap.light_scale + ray->tilemap.light_level + tile->light;

			/* draw textured line */
			for (y = line_start_c; y < line_end_c; y++)
			{
				int tex_y;
				uint8_t c;

				if (ray->config.stretch_wall_textures)
				{
					tex_y = remap(y, line_start, line_end, 0, tex->h);
				}
				else
				{
					tex_y = remap(y, line_start, line_end, 0, tex->h * tile->height * 0.125f);
					tex_y = wrap(tex_y, tex->h);
				}

				/* texture color at pixel */
				c = ((Uint8 *)tex->pixels)[tex_y * tex->pitch + tex_x];

				if (!stencil[y])
				{
					if (hittype == HIT_MASK && c != 255)
					{
						/* draw masked texture */
						((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = colormap_lookup(ray, c, light);
						stencil[y] = 1;
					}
					else
					{
						/* draw wall texture */
						((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = colormap_lookup(ray, c, light);
					}
				}
			}

			/* set ystart for next cast */
			if (hittype == HIT_WALL)
				ystart = line_start_c;
		}
		else
		{
			/* draw colored line */
			for (y = line_start_c; y < line_end_c; y++)
			{
				((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = 255;
			}

			/* set ystart for next cast */
			ystart = line_start_c;
		}

		/* draw top slab */
		if (hittype == HIT_WALL)
		{
			float oldz;

			/* line start and end */
			line_start = ((block_top / dist2) * pixel_height_scale) + hit->horizon;
			line_end = ystart;

			/* clamp to screen resolution */
			line_start_c = CLAMP(line_start, 0, ystart);
			line_end_c = CLAMP(line_end, 0, ystart);

			oldz = ray->camera.origin.z;
			ray->camera.origin.z = block_top;

			/* draw colored line */
			for (y = line_start_c; y < line_end_c; y++)
			{
				if (!stencil[y])
				{
					if (ray->config.draw_floor_textures)
					{
						ray_draw_floor(ray, hit, x, y, pixel_height_scale);
					}
					else
					{
						((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = 0;
					}
				}
			}

			ray->camera.origin.z = oldz;

			/* set ystart for next cast */
			ystart = line_start_c;
		}

		/* draw sky */
		if (ray->config.draw_sky)
		{
			int tex_x;
			int tex_y;

			tex_x = x - ray->camera.yaw * 4;
			tex_x = wrap(tex_x / 2, ray->textures.sky->w);

			for (y = 0; y < line_start_c; y++)
			{
				tex_y = y - hit->horizon + (ray->textures.sky->h / 2) * 2;

				tex_y = wrap(tex_y / 2, ray->textures.sky->h);

				if (!stencil[y])
					((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = ((Uint8 *)ray->textures.sky->pixels)[tex_y * ray->textures.sky->pitch + tex_x];
			}
		}
		else
		{
			/* draw ceiling */
			float oldz;
			float ceilingz;

			ceilingz = ray->camera.origin.z - ray->tilemap.ceiling * 0.125f;

			oldz = ray->camera.origin.z;
			ray->camera.origin.z = ceilingz;

			/* draw colored line */
			for (y = 0; y < line_start_c; y++)
			{
				if (!stencil[y])
				{
					if (ray->config.draw_ceiling_textures)
					{
						ray_draw_floor(ray, hit, x, y, pixel_height_scale);
					}
					else
					{
						((Uint8 *)ray->dest->pixels)[y * ray->dest->pitch + x] = 0;
					}
				}
			}

			ray->camera.origin.z = oldz;

			/* set ystart for next cast */
			ystart = line_start_c;
		}
	}
}

/* draw ray */
void ray_draw(ray_t *ray)
{
	int x, y;
	hit_t hit;

	/* get sin and cos of camera yaw */
	hit.viewsin = sinf(DEG2RAD(ray->camera.yaw));
	hit.viewcos = cosf(DEG2RAD(ray->camera.yaw));

	/* clamp camera pitch */
	ray->camera.pitch = CLAMP(ray->camera.pitch, -ray->textures.sky->h / 4, ray->textures.sky->h / 4);

	/* calculate camera horizon */
	hit.horizon = -ray->camera.pitch + (ray->dest->h / 2);

	/* draw walls, floors, and sky */
	for (x = 0; x < ray->dest->w; x++)
	{
		ray_draw_column(x, ray, &hit);
	}
}

/* print text to screen */
void ray_print(ray_t *ray, int x, int y, char *s)
{
	SDL_Rect srcrect, dstrect;
	char c;
	int startx, starty;

	startx = x;
	starty = y;
	while ((c = *s++))
	{
		if (c == '\n')
		{
			y += 8;
			x = startx;
			continue;
		}

		srcrect.x = c * 8;
		srcrect.y = 0;
		srcrect.w = 8;
		srcrect.h = 8;

		dstrect.x = x;
		dstrect.y = y;
		dstrect.w = 8;
		dstrect.h = 8;

		SDL_BlitSurface(ray->font, &srcrect, ray->dest, &dstrect);

		x += 8;
	}
}

/* print formatted text to screen */
void ray_printf(ray_t *ray, int x, int y, char *s, ...)
{
	static char strbuf[1024];
	va_list args;

	va_start(args, s);
	vsnprintf(strbuf, sizeof(strbuf), s, args);
	va_end(args);

	ray_print(ray, x, y, strbuf);
}

/* fill area with color */
void ray_fill(ray_t *ray, int x, int y, int w, int h, uint8_t c)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_FillRect(ray->dest, &rect, c);
}

/* init ray structure */
void ray_init(ray_t *ray)
{
	memset(ray, 0, sizeof(ray_t));
}
