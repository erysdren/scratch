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

/* global gamestate */
gamestate_t gamestate;

/* main */
int main(int argc, char **argv)
{
	int key;
	int lump;

	/* zero gamestate */
	memset(&gamestate, 0, sizeof(gamestate_t));

	/* init kbhandler */
	kb_init();

	/* set video mode */
	gamestate.video_mode_old = dos_get_mode();
	if ((gamestate.video_mode = dos_set_mode(DOS_MODE_13)) != DOS_MODE_13)
		error("couldn't init video mode");

	/* load game assets */
	if ((gamestate.wad = wad_open("game.wad")) == NULL)
		error("couldn't find game.wad");

	/* set palette */
	lump = wad_get_index_from_name(gamestate.wad, "PALETTE");
	wad_read_lump(gamestate.wad, lump, gamestate.palette);
	dos_set_palette(gamestate.palette);

	/* allocate pixelmaps */
	gamestate.screen = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, (void *)DOS_GRAPHICS_MEMORY);
	gamestate.color = pixelmap_allocate(320, 200, PM_TYPE_INDEX_8, NULL);
	gamestate.depth = pixelmap_allocate(320, 200, PM_TYPE_DEPTH_16, NULL);

	/* init console */
	console_init();

	/* main loop */
	while (true)
	{
		/* process inputs */
		if (gamestate.keys[SC_ESCAPE])
			break;

		/* handle console */
		while ((key = kb_getkey()) >= 0)
		{
			console_input(key);
		}

		/* clear screen */
		pixelmap_clear8(gamestate.color, 0);

		/* render console */
		console_render(gamestate.color);

		/* copy to screen */
		pixelmap_copy(gamestate.screen, gamestate.color);
	}

	/* quit console */
	console_quit();

	/* free pixelmaps */
	pixelmap_free(gamestate.screen);
	pixelmap_free(gamestate.color);
	pixelmap_free(gamestate.depth);
	wad_close(gamestate.wad);

	/* reset video mode */
	dos_set_mode(gamestate.video_mode_old);

	/* quit kbhandler */
	kb_quit();

	return 0;
}
