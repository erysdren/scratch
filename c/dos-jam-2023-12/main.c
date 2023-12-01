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

/* main */
int main(int argc, char **argv)
{
	int key;

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

	console_push_up("hello world 1!");
	console_push_up("oh no dear");
	console_push_up("ffffffffffffffffffff");
	console_push_up("excessive\nnewline\ntest\n2023");

	/* main loop */
	while (true)
	{
		pixelmap_clear8(gamestate.color, 0);
		console_render(gamestate.color);
		pixelmap_copy(gamestate.screen, gamestate.color);

		if (gamestate.keys[SC_ESCAPE])
			break;

		while ((key = kb_getkey()) >= 0)
		{
			console_input(key);
		}
	}

	/* quit console */
	console_quit();

	/* free pixelmaps */
	pixelmap_free(gamestate.screen);
	pixelmap_free(gamestate.color);
	pixelmap_free(gamestate.depth);

	/* reset video mode */
	dos_set_mode(gamestate.video_mode_old);

	/* quit kbhandler */
	kb_quit();

	return 0;
}
