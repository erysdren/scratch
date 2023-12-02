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
#include "cvar.h"
#include "cmd.h"
#include "wad.h"
#include "timer.h"
#include "ray.h"

/* global gamestate */
gamestate_t gamestate;

/* main */
int main(int argc, char **argv)
{
	int key;
	int lump;
	FILE *file;
	vec2_t origin;
	fix32_t angle;
	vec2_t direction;
	uint64_t tick;

	/* zero gamestate */
	memset(&gamestate, 0, sizeof(gamestate_t));

	/* init handlers */
	kb_init();
	timer_init();

	/* set video mode */
	gamestate.video_mode_old = dos_get_mode();
	if ((gamestate.video_mode = dos_set_mode(DOS_MODE_13)) != DOS_MODE_13)
		error("couldn't init video mode");

	/* read palette */
	file = fopen("palette.dat", "rb");
	if (!file)
		error("couldn't find palette.dat");
	fread(gamestate.palette, 3, 256, file);
	fclose(file);

	/* set palette */
	dos_set_palette(gamestate.palette);

	/* allocate pixelmaps */
	gamestate.screen = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, (void *)DOS_GRAPHICS_MEMORY);
	gamestate.color = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	gamestate.depth = pixelmap_allocate(320, 200, PM_TYPE_DEPTH_16, NULL);

	/* init level */
	gamestate.level = level_load("casino.lvl");
	if (!gamestate.level)
		error("couldn't load casino.lvl");

	/* init raycaster */
	ray_init(gamestate.level);
	origin.x = FIX32(10.5);
	origin.y = FIX32(16.5);

	/* init console */
	console_init();

	/* main loop */
	for (tick = gamestate.ticks;;)
	{
		/* process misc inputs */
		if (gamestate.keys[SC_ESCAPE])
			break;

		/* poll on timer */
		for (; tick < gamestate.ticks; tick++)
		{
			/* process player look */
			if (gamestate.keys[SC_LEFT])
				angle += FIX32(0.01);
			if (gamestate.keys[SC_RIGHT])
				angle -= FIX32(0.01);
			if (angle < FIX32(0))
				angle += FIX32(360);
			if (angle > FIX32(359))
				angle -= FIX32(360);

			/* get look direction */
			direction.x = FIX32_SIN(FIX32_DEG2RAD(angle));
			direction.y = FIX32_COS(FIX32_DEG2RAD(angle));

			direction.x = FIX32_DIV(direction.x, FIX32(64));
			direction.y = FIX32_DIV(direction.y, FIX32(64));

			/* process player inputs */
			if (gamestate.keys[SC_W])
			{
				origin.x += direction.x;
				origin.y += direction.y;
			}
			if (gamestate.keys[SC_S])
			{
				origin.x -= direction.x;
				origin.y -= direction.y;
			}
			if (gamestate.keys[SC_A])
			{
				origin.x += direction.y;
				origin.y -= direction.x;
			}
			if (gamestate.keys[SC_D])
			{
				origin.x -= direction.y;
				origin.y += direction.x;
			}
		}

		/* clear screen */
		pixelmap_clear8(gamestate.color, 0);

		/* render ray */
		ray_render(gamestate.color, &origin, angle);

		/* copy to screen */
		pixelmap_copy(gamestate.screen, gamestate.color);
	}

	/* quit console */
	console_quit();

	/* quit raycaster */
	ray_quit();

	/* free memory */
	pixelmap_free(gamestate.screen);
	pixelmap_free(gamestate.color);
	pixelmap_free(gamestate.depth);
	level_free(gamestate.level);

	/* reset video mode */
	dos_set_mode(gamestate.video_mode_old);

	/* quit handlers */
	kb_quit();
	timer_quit();

	return 0;
}
