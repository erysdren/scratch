/*/*
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

#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dos.h"
#include "pixelmap.h"
#include "level.h"
#include "wad.h"
#include "actor.h"

enum {
	STATE_EXIT,
	STATE_GAME,
	STATE_CONSOLE,
	STATE_MENU
};

#define MAX_WALLS 256

typedef struct engine_t {

	/* game */
	level_t *level;
	wad_t *wad;
	actor_t player;

	/* engine */
	uint64_t ticks;
	int tickrate;
	fix32_t time;
	fix32_t frametime;
	int state;
	int argc;
	char **argv;

	/* video */
	pixelmap_t *screen;
	pixelmap_t *color;
	pixelmap_t *console;
	pixelmap_t *palette;
	pixelmap_t *colormap;
	pixelmap_t *font8x8;
	pixelmap_t *walls[MAX_WALLS];

	/* audio */
	bool adlib;

	/* dos */
	int video_mode_old;
	int video_mode;
	_go32_dpmi_seginfo kbhandler_old;
	_go32_dpmi_seginfo kbhandler_new;
	_go32_dpmi_seginfo timerhandler_old;
	_go32_dpmi_seginfo timerhandler_new;
	char keys[256];
	char key_last;
} engine_t;

/* global engine state */
extern engine_t engine;

void engine_quit(void);
void engine_init(int argc, char **argv);
bool engine_run(void);

#ifdef __cplusplus
}
#endif
#endif /* _ENGINE_H_ */
