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

#pragma once
#ifndef _DARKWAR_H_
#define _DARKWAR_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "array.h"

/* actor movement directions */
enum {
	DIR_EAST,
	DIR_NORTHEAST,
	DIR_NORTH,
	DIR_NORTHWEST,
	DIR_WEST,
	DIR_SOUTHWEST,
	DIR_SOUTH,
	DIR_SOUTHEAST,
	DIR_NONE
};

/* actor flags */
enum {
	FLAG_NONE = 0,
	FLAG_HARD = 1 << 0,
	FLAG_AMBUSH = 1 << 1
};

/* actor ai behaviours */
enum {
	AI_STAND,
	AI_PATROL,
	AI_SNEAKY,
	AI_EMPLACEMENT
};

/* actor classes */
enum {
	CLASS_LOWGUARD,
	CLASS_HIGHGUARD,
	CLASS_ROBOGUARD,
	CLASS_BALLISTIKRAFT,
	CLASS_STRIKEGUARD,
	CLASS_PATROLGUN,
	CLASS_OVERPATROL,
	CLASS_BLITZGUARD,
	CLASS_TRIADENFORCER,
	CLASS_DEATHMONK,
	CLASS_DEATHFIREMONK,
	CLASS_DARIAN,
	CLASS_HEINRICH,
	CLASS_NME,
	CLASS_OSCUROMONK,
	CLASS_OSCUROSNAKE
};

/* actor */
typedef struct actor_t {
	int class;
	int ai;
	int dir;
	int flags;
} actor_t;

/* define actor in array with all values */
#define ACTOR_AT_INDEX_WITH_DIR(_i, _class, _ai, _dir, _flags) \
	[_i] = {.class = _class, .ai = _ai, .dir = _dir, .flags = _flags}

/* define actor in array, with dir automatically set to DIR_EAST */
#define ACTOR_AT_INDEX(_i, _class, _ai, _flags) \
	ACTOR_AT_INDEX_WITH_DIR(_i, _class, _ai, DIR_EAST, _flags)

/* define actor in array and automatically create one for each direction */
#define ACTOR_AT_INDEX_DIRECTIONAL(_i, _class, _ai, _flags) \
	ACTOR_AT_INDEX_WITH_DIR(_i + 0, _class, _ai, DIR_EAST, _flags), \
	ACTOR_AT_INDEX_WITH_DIR(_i + 1, _class, _ai, DIR_NORTH, _flags), \
	ACTOR_AT_INDEX_WITH_DIR(_i + 2, _class, _ai, DIR_WEST, _flags), \
	ACTOR_AT_INDEX_WITH_DIR(_i + 3, _class, _ai, DIR_SOUTH, _flags)

extern const array_t darkwar_wall_tiles;
extern const array_t darkwar_sprite_tiles;
extern const array_t darkwar_info_tiles;

#ifdef __cplusplus
}
#endif
#endif /* _DARKWAR_H_ */
