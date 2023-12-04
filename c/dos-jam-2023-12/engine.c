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

#include "engine.h"
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

/* global engine state */
engine_t engine;

/* init everything */
void engine_init(int argc, char **argv)
{
	/* zero engine struct */
	memset(&engine, 0, sizeof(engine_t));

	/* init dos handlers */
	kb_init();
	timer_init(120);

	/* assign argv and argc */
	engine.argc = argc;
	engine.argv = argv;

	/* set video mode */
	engine.video_mode_old = dos_get_mode();
	if ((engine.video_mode = dos_set_mode(DOS_MODE_13)) != DOS_MODE_13)
		error("couldn't set video mode");

	/* allocate pixelmaps */
	engine.screen = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, (void *)DOS_GRAPHICS_MEMORY);
	engine.color = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	engine.console = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	if (!engine.screen || !engine.color || !engine.console)
		error("couldn't allocate pixelmaps");

	/* get palette */
	engine.palette = pixelmap_load("palette.pxl");
	if (!engine.palette)
		error("couldn't load palette.pxl");

	/* set palette */
	dos_set_palette(engine.palette->pixels);

	/* get colormap */
	engine.colormap = pixelmap_load("colormap.pxl");
	if (!engine.colormap)
		error("couldn't load colormap.pxl");

	/* get font */
	engine.font8x8 = pixelmap_load("font8x8.pxl");
	if (!engine.font8x8)
		error("couldn't load font8x8.pxl");

	/* init console */
	console_init();
	cmdlib_init();
	cvarlib_init();
	console_printf("console initialized");

	/* load wall textures */
	for (int i = 0; i < MAX_WALLS; i++)
	{
		char filename[16];
		snprintf(filename, 16, "wall%003d.pxl", i + 1);
		if ((engine.walls[i] = pixelmap_load(filename)) == NULL)
		{
			console_printf("loaded %d wall textures", i);
			break;
		}
	}

	/* detect adlib card */
	if ((engine.adlib = adlib_detect()) == true)
		console_printf("adlib card detected");
	else
		warning("adlib card support disabled");

	/* load level */
	if (argv[1])
	{
		if ((engine.level = level_load(argv[1])) == NULL)
			error("couldn't load %s", argv[1]);

		/* init raycaster */
		ray_init(engine.level);

		/* set state */
		engine.state = STATE_GAME;
	}
	else
	{
		/* set state */
		engine.state = STATE_CONSOLE;
	}
}

/* quit everything */
void engine_quit(void)
{
	/* first thing we do on quit is reset dos interrupts */
	kb_quit();
	timer_quit();

	/* and reset video mode */
	dos_set_mode(engine.video_mode_old);

	/* quit raycaster */
	ray_quit();

	/* quit console */
	console_quit();
	cmdlib_quit();
	cvarlib_quit();

	/* free pixelmap memory */
	pixelmap_free(engine.screen);
	pixelmap_free(engine.color);
	pixelmap_free(engine.colormap);
	pixelmap_free(engine.console);
	pixelmap_free(engine.palette);
	pixelmap_free(engine.font8x8);

	/* free wall memory */
	for (int i = 0; i < MAX_WALLS; i++)
		pixelmap_free(engine.walls[i]);

	/* free level memory */
	level_free(engine.level);
}

bool engine_run(void)
{
	/* handle engine state */
	switch (engine.state)
	{
		/* exiting */
		case STATE_EXIT:
			engine_quit();
			exit(0);
			return false;

		/* game */
		case STATE_GAME:
			engine.state = game_run();
			return true;

		/* console */
		case STATE_CONSOLE:
			engine.state = console_run();
			return true;

		/* menu */
		case STATE_MENU:
			error("menu state not implemented yet");
			return false;

		/* error */
		default:
			error("unknown engine state %d", engine.state);
			return false;
	}
}
