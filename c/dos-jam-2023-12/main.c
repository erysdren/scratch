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
#include "cmdlib.h"
#include "cvarlib.h"
#include "adlib.h"
#include "actor.h"

/* global gamestate */
gamestate_t gamestate;

#define CONSOLE 1

/* init everything */
void engine_init(void)
{
	FILE *palette;

	/* zero gamestate struct */
	memset(&gamestate, 0, sizeof(gamestate_t));

	/* init dos handlers */
	kb_init();
	timer_init(120);

	/* set video mode */
	gamestate.video_mode_old = dos_get_mode();
	if ((gamestate.video_mode = dos_set_mode(DOS_MODE_13)) != DOS_MODE_13)
		error("couldn't set video mode");

	/* read palette */
	palette = fopen("palette.dat", "rb");
	if (!palette)
		error("couldn't find palette.dat");
	fread(gamestate.palette, 3, 256, palette);
	fclose(palette);

	/* set palette */
	dos_set_palette(gamestate.palette);

	/* allocate pixelmaps */
	gamestate.screen = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, (void *)DOS_GRAPHICS_MEMORY);
	gamestate.color = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	if (!gamestate.screen || !gamestate.color)
		error("couldn't allocate pixelmaps");

	/* init console */
	console_init();
	cmdlib_init();
	cvarlib_init();

	/* detect adlib card */
	if ((gamestate.adlib = adlib_detect()) == true)
		console_printf("adlib card detected");
	else
		console_printf("adlib card support disabled");
}

/* quit everything */
void engine_quit(void)
{
	/* first thing we do on quit is reset dos interrupts */
	kb_quit();
	timer_quit();

	/* and reset video mode */
	dos_set_mode(gamestate.video_mode_old);

	/* quit raycaster */
	ray_quit();

	/* quit console */
	console_quit();
	cmdlib_quit();
	cvarlib_quit();

	/* free memory */
	pixelmap_free(gamestate.screen);
	pixelmap_free(gamestate.color);
	level_free(gamestate.level);
}

/* main */
int main(int argc, char **argv)
{
	uint64_t tick;
	int key;

	/* init everything */
	engine_init();

	/* setup player */
	gamestate.player.origin.x = FIX32(10.5);
	gamestate.player.origin.y = FIX32(16.5);

	/* main loop */
	for (tick = gamestate.ticks;;)
	{
		/* process misc inputs */
		if (gamestate.keys[SC_ESCAPE])
			break;

#if CONSOLE
		/* handle console input */
		while ((key = kb_getkey()) >= 0)
			console_input(key);
#else
		/* poll on timer */
		for (; tick < gamestate.ticks; tick++)
		{
			/* process player look */
			if (gamestate.keys[SC_LEFT])
				gamestate.player.yaw += FIX32(0.0001);
			if (gamestate.keys[SC_RIGHT])
				gamestate.player.yaw -= FIX32(0.0001);
			if (gamestate.player.yaw < FIX32(0))
				gamestate.player.yaw += FIX32(2);
			if (gamestate.player.yaw > FIX32(2))
				gamestate.player.yaw -= FIX32(2);

			/* get look direction */
			gamestate.player.dir.x = FIX32_SIN(gamestate.player.yaw);
			gamestate.player.dir.y = FIX32_COS(gamestate.player.yaw);

			gamestate.player.dir.x = FIX32_DIV(gamestate.player.dir.x, FIX32(64));
			gamestate.player.dir.y = FIX32_DIV(gamestate.player.dir.y, FIX32(64));

			/* process player inputs */
			if (gamestate.keys[SC_W])
			{
				gamestate.player.origin.x += gamestate.player.dir.x;
				gamestate.player.origin.y += gamestate.player.dir.y;
			}
			if (gamestate.keys[SC_S])
			{
				gamestate.player.origin.x -= gamestate.player.dir.x;
				gamestate.player.origin.y -= gamestate.player.dir.y;
			}
			if (gamestate.keys[SC_A])
			{
				gamestate.player.origin.x += gamestate.player.dir.y;
				gamestate.player.origin.y -= gamestate.player.dir.x;
			}
			if (gamestate.keys[SC_D])
			{
				gamestate.player.origin.x -= gamestate.player.dir.y;
				gamestate.player.origin.y += gamestate.player.dir.x;
			}
		}
#endif

		/* clear screen */
		pixelmap_clear8(gamestate.color, 0);

#if CONSOLE
		/* render console */
		console_render(gamestate.color);
#else
		/* render ray */
		ray_render(gamestate.color, &gamestate.player, 2);
#endif

		/* copy to screen */
		pixelmap_copy(gamestate.screen, gamestate.color);
	}

	/* shutdown everything */
	engine_quit();

	return 0;
}
