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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "pixelmap.h"
#include "dos.h"
#include "utils.h"
#include "console.h"
#include "keyboard.h"
#include "level.h"

#define RCL_PIXEL_FUNCTION pixel_at
#define RCL_USE_COS_LUT 2
#define RCL_COMPUTE_FLOOR_DEPTH 0
#define RCL_COMPUTE_CEILING_DEPTH 0
#define RCL_TEXTURE_VERTICAL_STRETCH 0
#define RCL_USE_DIST_APPROX 1
#define RCL_UNIT(x) (int32_t)((x) * RCL_UNITS_PER_SQUARE)
#include "raycastlib.h"

/* global gamestate */
gamestate_t gamestate;

bool load_palette(const char *filename)
{
	FILE *file;
	int i;

	/* open file */
	file = fopen(filename, "rb");
	if (!file)
		return false;

	/* read palette */
	fread(gamestate.palette, 768, 1, file);

	/* close file */
	fclose(file);

	/* set palette */
	for (i = 0; i < 256; i++)
	{
		uint8_t r = gamestate.palette[i][0];
		uint8_t g = gamestate.palette[i][1];
		uint8_t b = gamestate.palette[i][2];
		dos_set_palette_color(i, r, g, b);
	}

	return true;
}

void pixel_at(RCL_PixelInfo *pixel)
{
	if (pixel->isWall)
		pixelmap_pixel8(gamestate.color, pixel->position.x, pixel->position.y) = 31;
	else if (pixel->isFloor)
		pixelmap_pixel8(gamestate.color, pixel->position.x, pixel->position.y) = 15;
	else if (pixel->isHorizon)
		pixelmap_pixel8(gamestate.color, pixel->position.x, pixel->position.y) = 0;
}

RCL_Unit texture_at(int16_t x, int16_t y)
{
	if (x >= 0 && x < gamestate.level->width && y >= 0 && y < gamestate.level->height)
		return gamestate.level->planes[1][y * gamestate.level->width + x];

	return 0;
}

RCL_Unit floor_at(int16_t x, int16_t y)
{
	if (x >= 0 && x < gamestate.level->width && y >= 0 && y < gamestate.level->height)
	{
		if (gamestate.level->planes[1][y * gamestate.level->width + x])
			return RCL_UNIT(1);
	}

	return 0;
}

RCL_Unit ceiling_at(int16_t x, int16_t y)
{
	if (x >= 0 && x < gamestate.level->width && y >= 0 && y < gamestate.level->height)
		return RCL_UNIT(1);

	return 0;
}

/* main */
int main(int argc, char **argv)
{
	int key;
	RCL_RayConstraints ray;
	RCL_Camera camera;

	/* zero gamestate */
	memset(&gamestate, 0, sizeof(gamestate_t));

	/* init kbhandler */
	kb_init();

	/* set video mode */
	gamestate.video_mode_old = dos_get_mode();
	if ((gamestate.video_mode = dos_set_mode(DOS_MODE_13)) != DOS_MODE_13)
		error("couldn't init video mode");

	/* load palette */
	if (!load_palette("palette.dat"))
		error("couldn't load palette.dat");

	/* allocate pixelmaps */
	gamestate.screen = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, (void *)DOS_GRAPHICS_MEMORY);
	gamestate.color = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	gamestate.depth = pixelmap_allocate(320, 200, PM_TYPE_DEPTH_16, NULL);

	/* init console */
	console_init();

	/* prepare raycaster */
	RCL_initCamera(&camera);
	RCL_initRayConstraints(&ray);
	gamestate.level = level_load("casino.lvl");
	ray.maxHits = 32;
	ray.maxSteps = 32;
	camera.direction = 0;
	camera.position.x = RCL_UNIT(10.5);
	camera.position.y = RCL_UNIT(16.5);
	camera.height = RCL_UNIT(0.5);
	camera.resolution.x = gamestate.color->width;
	camera.resolution.y = gamestate.color->height;

	/* main loop */
	while (true)
	{
		/* process inputs */
		if (gamestate.keys[SC_ESCAPE])
			break;

		if (gamestate.keys[SC_A])
			camera.direction -= 1;
		else if (gamestate.keys[SC_D])
			camera.direction += 1;

		RCL_Vector2D direction = RCL_angleToDirection(camera.direction);

		direction.x /= 10;
		direction.y /= 10;

		if (gamestate.keys[SC_W])
		{
			camera.position.x += direction.x;
			camera.position.y += direction.y;
		}
		else if (gamestate.keys[SC_S])
		{
			camera.position.x -= direction.x;
			camera.position.y -= direction.y;
		}

		/* render */
		RCL_renderSimple(camera, floor_at, texture_at, NULL, ray);

		/* copy to screen */
		pixelmap_copy(gamestate.screen, gamestate.color);
	}

	/* quit console */
	console_quit();

	/* free pixelmaps */
	pixelmap_free(gamestate.screen);
	pixelmap_free(gamestate.color);
	pixelmap_free(gamestate.depth);
	level_free(gamestate.level);

	/* reset video mode */
	dos_set_mode(gamestate.video_mode_old);

	/* quit kbhandler */
	kb_quit();

	return 0;
}
