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
#ifndef _MAIN_H_
#define _MAIN_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "dos.h"
#include "pixelmap.h"
#include "level.h"
#include "wad.h"

typedef struct gamestate_t {

	/* game */
	level_t *level;
	wad_t *wad;

	/* engine */
	uint64_t ticks;

	/* video */
	pixelmap_t *screen;
	pixelmap_t *color;
	pixelmap_t *depth;
	uint8_t palette[256][3];

	/* dos */
	int video_mode_old;
	int video_mode;
	_go32_dpmi_seginfo kbhandler_old;
	_go32_dpmi_seginfo kbhandler_new;
	_go32_dpmi_seginfo timerhandler_old;
	_go32_dpmi_seginfo timerhandler_new;
	char keys[256];
	char key_last;
} gamestate_t;

/* global gamestate */
extern gamestate_t gamestate;

void engine_quit(void);
void engine_init(void);

#ifdef __cplusplus
}
#endif
#endif /* _MAIN_H_ */
