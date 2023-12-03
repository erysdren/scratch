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
#include "game.h"

/* global gamestate */
gamestate_t gamestate;

/* init everything */
void engine_init(void)
{
	/* zero gamestate struct */
	memset(&gamestate, 0, sizeof(gamestate_t));

	/* init dos handlers */
	kb_init();
	timer_init(120);

	/* set video mode */
	gamestate.video_mode_old = dos_get_mode();
	if ((gamestate.video_mode = dos_set_mode(DOS_MODE_13)) != DOS_MODE_13)
		error("couldn't set video mode");

	/* allocate pixelmaps */
	gamestate.screen = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, (void *)DOS_GRAPHICS_MEMORY);
	gamestate.color = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	gamestate.console = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	if (!gamestate.screen || !gamestate.color || !gamestate.console)
		error("couldn't allocate pixelmaps");

	/* get palette */
	gamestate.palette = pixelmap_load("palette.pxl");
	if (!gamestate.palette)
		error("couldn't load palette.pxl");

	/* set palette */
	dos_set_palette(gamestate.palette->pixels);

	/* get colormap */
	gamestate.colormap = pixelmap_load("colormap.pxl");
	if (!gamestate.colormap)
		error("couldn't load colormap.pxl");

	/* get font */
	gamestate.font8x8 = pixelmap_load("font8x8.pxl");
	if (!gamestate.font8x8)
		error("couldn't load font8x8.pxl");

	/* init console */
	console_init();
	cmdlib_init();
	cvarlib_init();

	/* detect adlib card */
	if ((gamestate.adlib = adlib_detect()) == true)
		console_printf("adlib card detected");
	else
		console_printf("adlib card support disabled");

	/* load level */
	if ((gamestate.level = level_load("test1.lvl")) == NULL)
		error("couldn't load test1.lvl");

	/* init raycaster */
	ray_init(gamestate.level);
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
	pixelmap_free(gamestate.colormap);
	pixelmap_free(gamestate.console);
	pixelmap_free(gamestate.palette);
	pixelmap_free(gamestate.font8x8);
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
	gamestate.player.origin.x = FIX32(16.5);
	gamestate.player.origin.y = FIX32(18.5);

	/* main loop */
	for (tick = gamestate.ticks;;)
	{
		/* handle queued inputs */
		while ((key = kb_getkey()) >= 0)
		{
			switch (key)
			{
				/* run console */
				case SC_TILDE:
					console_run();
					break;

				/* just quit on esc */
				case SC_ESCAPE:
					engine_quit();
					exit(0);
					break;
			}
		}

		/* run game ticks */
		game_run();
	}

	/* shutdown everything */
	engine_quit();

	return 0;
}
