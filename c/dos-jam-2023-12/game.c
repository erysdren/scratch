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

/* run one tick of game loop */
int game_run(void)
{
	int key;
	int state = STATE_GAME;

	/* sanity check */
	if (!engine.level)
	{
		warning("level is not loaded!");
		return STATE_CONSOLE;
	}

	/* handle queued inputs */
	while ((key = kb_getkey()) >= 0)
	{
		switch (key)
		{
			/* run console */
			case SC_TILDE:
				state = STATE_CONSOLE;
				break;

			/* just quit on esc */
			case SC_ESCAPE:
				state = STATE_EXIT;
				break;
		}
	}

	/* process player look */
	if (engine.keys[SC_LEFT])
		engine.player.yaw += FIX32_MUL(FIX32(0.002), engine.frametime);
	if (engine.keys[SC_RIGHT])
		engine.player.yaw -= FIX32_MUL(FIX32(0.002), engine.frametime);
	if (engine.player.yaw < FIX32(0))
		engine.player.yaw += FIX32(2);
	if (engine.player.yaw > FIX32(2))
		engine.player.yaw -= FIX32(2);

	/* get look direction */
	engine.player.dir.x = FIX32_SIN(engine.player.yaw);
	engine.player.dir.y = FIX32_COS(engine.player.yaw);

	engine.player.dir.x = FIX32_MUL(engine.player.dir.x, engine.frametime);
	engine.player.dir.y = FIX32_MUL(engine.player.dir.y, engine.frametime);

	/* process player inputs */
	if (engine.keys[SC_W])
	{
		engine.player.origin.x += engine.player.dir.x;
		engine.player.origin.y += engine.player.dir.y;
	}
	if (engine.keys[SC_S])
	{
		engine.player.origin.x -= engine.player.dir.x;
		engine.player.origin.y -= engine.player.dir.y;
	}
	if (engine.keys[SC_A])
	{
		engine.player.origin.x += engine.player.dir.y;
		engine.player.origin.y -= engine.player.dir.x;
	}
	if (engine.keys[SC_D])
	{
		engine.player.origin.x -= engine.player.dir.y;
		engine.player.origin.y += engine.player.dir.x;
	}

	/* render game */
	pixelmap_clear8(engine.color, 0);
	ray_render(engine.color, &engine.player, 2);
	pixelmap_copy(engine.screen, engine.color);

	return state;
}

