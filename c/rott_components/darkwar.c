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

#include "darkwar.h"

/*
 *
 * tileset entries for the walls of Rise of the Triad's DARKWAR.WAD
 *
 * these indexes do NOT correspond to WAD indexes, but rather to the tile index
 * found in the Walls plane of a given map.
 *
 * TRIVIA: in the ROTT source code in RT_TED.C, any tile with the value 33, 34,
 * 35, 44, or 45 are specifically set to zero when loading a map. there is no
 * reason given.
 *
 */
static const char *_darkwar_wall_tiles[] = {
	/* 0 */
	VALUE_AT_INDEX(1, "WALL1"),
	VALUE_AT_INDEX(2, "WALL2"),
	VALUE_AT_INDEX(3, "WALL3"),
	VALUE_AT_INDEX(4, "WALL4"),
	VALUE_AT_INDEX(5, "WALL5"),
	VALUE_AT_INDEX(6, "WALL6"),
	VALUE_AT_INDEX(7, "WALL7"),
	VALUE_AT_INDEX(8, "WALL8"),
	VALUE_AT_INDEX(9, "WALL9"),
	VALUE_AT_INDEX(10, "WALL10"),
	VALUE_AT_INDEX(11, "WALL11"),
	VALUE_AT_INDEX(12, "WALL12"),
	VALUE_AT_INDEX(13, "WALL13"),
	VALUE_AT_INDEX(14, "WALL14"),
	VALUE_AT_INDEX(15, "WALL15"),
	VALUE_AT_INDEX(16, "WALL16"),
	VALUE_AT_INDEX(17, "WALL17"),
	VALUE_AT_INDEX(18, "WALL18"),
	VALUE_AT_INDEX(19, "WALL19"),
	VALUE_AT_INDEX(20, "WALL20"),
	VALUE_AT_INDEX(21, "WALL21"),
	VALUE_AT_INDEX(22, "WALL22"),
	VALUE_AT_INDEX(23, "WALL23"),
	VALUE_AT_INDEX(24, "WALL24"),
	VALUE_AT_INDEX(25, "WALL25"),
	VALUE_AT_INDEX(26, "WALL26"),
	VALUE_AT_INDEX(27, "WALL27"),
	VALUE_AT_INDEX(28, "WALL28"),
	VALUE_AT_INDEX(29, "WALL29"),
	VALUE_AT_INDEX(30, "WALL30"),
	VALUE_AT_INDEX(31, "WALL31"),
	VALUE_AT_INDEX(32, "WALL32"),
	/* 33 */
	/* 34 */
	/* 35 */
	VALUE_AT_INDEX(36, "WALL33"),
	VALUE_AT_INDEX(37, "WALL34"),
	VALUE_AT_INDEX(38, "WALL35"),
	VALUE_AT_INDEX(39, "WALL36"),
	VALUE_AT_INDEX(40, "WALL37"),
	VALUE_AT_INDEX(41, "WALL38"),
	VALUE_AT_INDEX(42, "WALL39"),
	VALUE_AT_INDEX(43, "WALL40"),
	/* 44 */
	/* 45 */
	VALUE_AT_INDEX(46, "WALL74"),
	VALUE_AT_INDEX(47, "EXIT"),
	VALUE_AT_INDEX(48, "ENTRANCE"),
	VALUE_AT_INDEX(49, "WALL41"),
	VALUE_AT_INDEX(50, "WALL42"),
	VALUE_AT_INDEX(51, "WALL43"),
	VALUE_AT_INDEX(52, "WALL44"),
	VALUE_AT_INDEX(53, "WALL45"),
	VALUE_AT_INDEX(54, "WALL46"),
	VALUE_AT_INDEX(55, "WALL47"),
	VALUE_AT_INDEX(56, "WALL48"),
	VALUE_AT_INDEX(57, "WALL49"),
	VALUE_AT_INDEX(58, "WALL50"),
	VALUE_AT_INDEX(59, "WALL51"),
	VALUE_AT_INDEX(60, "WALL52"),
	VALUE_AT_INDEX(61, "WALL53"),
	VALUE_AT_INDEX(62, "WALL54"),
	VALUE_AT_INDEX(63, "WALL55"),
	VALUE_AT_INDEX(64, "WALL56"),
	VALUE_AT_INDEX(65, "WALL57"),
	VALUE_AT_INDEX(66, "WALL58"),
	VALUE_AT_INDEX(67, "WALL59"),
	VALUE_AT_INDEX(68, "WALL60"),
	VALUE_AT_INDEX(69, "WALL61"),
	VALUE_AT_INDEX(70, "WALL62"),
	VALUE_AT_INDEX(71, "WALL63"),
	VALUE_AT_INDEX(72, "ELEV1"),
	VALUE_AT_INDEX(73, "ELEV2"),
	VALUE_AT_INDEX(74, "ELEV3"),
	VALUE_AT_INDEX(75, "ELEV4"),
	VALUE_AT_INDEX(76, "ELEV5"),
	VALUE_AT_INDEX(77, "ELEV6"),
	VALUE_AT_INDEX(78, "ELEV7"),
	VALUE_AT_INDEX(79, "ELEV8"),
	VALUE_AT_INDEX(80, "WALL64"),
	VALUE_AT_INDEX(81, "WALL65"),
	VALUE_AT_INDEX(82, "WALL66"),
	VALUE_AT_INDEX(83, "WALL67"),
	VALUE_AT_INDEX(84, "WALL68"),
	VALUE_AT_INDEX(85, "WALL69"),
	VALUE_AT_INDEX(86, "WALL70"),
	VALUE_AT_INDEX(87, "WALL71"),
	VALUE_AT_INDEX(88, "WALL72"),
	VALUE_AT_INDEX(89, "WALL73")
};

const array_t darkwar_wall_tiles = {
	.entries = _darkwar_wall_tiles,
	.length = sizeof(_darkwar_wall_tiles) / sizeof(const char *),
	.size = sizeof(const char *),
	.allocated = false
};

static actor_t _darkwar_sprite_tiles[] = {

	/* LOW GUARD - STAND */
	ACTOR_AT_INDEX_WITH_DIRS(108, "monster_lowguard", AI_STAND, AF_NONE),

	/* LOW GUARD - PATROL */
	ACTOR_AT_INDEX_WITH_DIRS(112, "monster_lowguard", AI_PATROL, AF_NONE),

	/* LOW GUARD - STAND, AMBUSH */
	ACTOR_AT_INDEX_WITH_DIRS(116, "monster_lowguard", AI_STAND, AF_AMBUSH),

	/* LOW GUARD - SNEAKY */
	ACTOR_AT_INDEX(120, "monster_lowguard", AI_SNEAKY, DIR_EAST, AF_NONE),

	/* LOW GUARD - STAND, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(126, "monster_lowguard", AI_STAND, AF_HARD),

	/* LOW GUARD - PATROL, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(130, "monster_lowguard", AI_PATROL, AF_HARD),

	/* LOW GUARD - STAND, AMBUSH, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(134, "monster_lowguard", AI_STAND, AF_HARD | AF_AMBUSH),

	/* LOW GUARD - SNEAKY, HARD */
	ACTOR_AT_INDEX(138, "monster_lowguard", AI_SNEAKY, DIR_EAST, AF_HARD),

	/* HIGH GUARD - STAND */
	ACTOR_AT_INDEX_WITH_DIRS(144, "monster_highguard", AI_STAND, AF_NONE),

	/* HIGH GUARD - PATROL */
	ACTOR_AT_INDEX_WITH_DIRS(148, "monster_highguard", AI_PATROL, AF_NONE),

	/* HIGH GUARD - STAND, AMBUSH */
	ACTOR_AT_INDEX_WITH_DIRS(152, "monster_highguard", AI_STAND, AF_AMBUSH),

	/* ROBO GUARD - PATROL */
	ACTOR_AT_INDEX_WITH_DIRS(158, "monster_roboguard", AI_PATROL, AF_NONE),

	/* HIGH GUARD - STAND, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(162, "monster_highguard", AI_STAND, AF_HARD),

	/* HIGH GUARD - PATROL, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(166, "monster_highguard", AI_PATROL, AF_HARD),

	/* HIGH GUARD - STAND, AMBUSH, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(170, "monster_highguard", AI_STAND, AF_HARD | AF_AMBUSH),

	/* ROBO GUARD - PATROL, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(176, "monster_roboguard", AI_PATROL, AF_HARD),

	/* STRIKE GUARD - STAND */
	ACTOR_AT_INDEX_WITH_DIRS(180, "monster_strikeguard", AI_STAND, AF_NONE),

	/* STRIKE GUARD - PATROL */
	ACTOR_AT_INDEX_WITH_DIRS(184, "monster_strikeguard", AI_PATROL, AF_AMBUSH),

	/* STRIKE GUARD - STAND, AMBUSH */
	ACTOR_AT_INDEX_WITH_DIRS(188, "monster_strikeguard", AI_STAND, AF_AMBUSH),

	/* PATROL GUN */
	ACTOR_AT_INDEX_WITH_DIRS(194, "monster_patrolgun", AI_NONE, AF_NONE),

	/* STRIKE GUARD - STAND, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(198, "monster_strikeguard", AI_STAND, AF_HARD),

	/* STRIKE GUARD - STAND, AMBUSH, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(206, "monster_strikeguard", AI_STAND, AF_HARD | AF_AMBUSH),

	/* PATROL GUN - HARD */
	ACTOR_AT_INDEX_WITH_DIRS(212, "monster_patrolgun", AI_NONE, AF_HARD),

	/* OVER PATROL - STAND */
	ACTOR_AT_INDEX_WITH_DIRS(216, "monster_overpatrol", AI_STAND, AF_NONE),

	/* OVER PATROL - STAND, AMBUSH */
	ACTOR_AT_INDEX_WITH_DIRS(224, "monster_overpatrol", AI_STAND, AF_AMBUSH),

	/* OVER PATROL - STAND, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(234, "monster_overpatrol", AI_STAND, AF_HARD),

	/* OVER PATROL - STAND, AMBUSH, HARD */
	ACTOR_AT_INDEX_WITH_DIRS(242, "monster_overpatrol", AI_STAND, AF_HARD | AF_AMBUSH),
};

const array_t darkwar_sprite_tiles = {
	.entries = _darkwar_sprite_tiles,
	.length = sizeof(_darkwar_sprite_tiles) / sizeof(actor_t),
	.size = sizeof(actor_t),
	.allocated = false
};

const array_t darkwar_info_tiles = {
	.entries = NULL,
	.length = 0,
	.size = 0,
	.allocated = false
};
