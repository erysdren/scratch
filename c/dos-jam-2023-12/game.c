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

/* run one tick of game loop */
void game_run(void)
{
	/* process player look */
	if (gamestate.keys[SC_LEFT])
		gamestate.player.yaw += FIX32_MUL(FIX32(0.002), gamestate.frametime);
	if (gamestate.keys[SC_RIGHT])
		gamestate.player.yaw -= FIX32_MUL(FIX32(0.002), gamestate.frametime);
	if (gamestate.player.yaw < FIX32(0))
		gamestate.player.yaw += FIX32(2);
	if (gamestate.player.yaw > FIX32(2))
		gamestate.player.yaw -= FIX32(2);

	/* get look direction */
	gamestate.player.dir.x = FIX32_SIN(gamestate.player.yaw);
	gamestate.player.dir.y = FIX32_COS(gamestate.player.yaw);

	gamestate.player.dir.x = FIX32_MUL(gamestate.player.dir.x, gamestate.frametime);
	gamestate.player.dir.y = FIX32_MUL(gamestate.player.dir.y, gamestate.frametime);

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

	/* render game */
	pixelmap_clear8(gamestate.color, 0);
	ray_render(gamestate.color, &gamestate.player, 2);
	pixelmap_copy(gamestate.screen, gamestate.color);
}

