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
	STRING_AT_INDEX(1, "WALL1"),
	STRING_AT_INDEX(2, "WALL2"),
	STRING_AT_INDEX(3, "WALL3"),
	STRING_AT_INDEX(4, "WALL4"),
	STRING_AT_INDEX(5, "WALL5"),
	STRING_AT_INDEX(6, "WALL6"),
	STRING_AT_INDEX(7, "WALL7"),
	STRING_AT_INDEX(8, "WALL8"),
	STRING_AT_INDEX(9, "WALL9"),
	STRING_AT_INDEX(10, "WALL10"),
	STRING_AT_INDEX(11, "WALL11"),
	STRING_AT_INDEX(12, "WALL12"),
	STRING_AT_INDEX(13, "WALL13"),
	STRING_AT_INDEX(14, "WALL14"),
	STRING_AT_INDEX(15, "WALL15"),
	STRING_AT_INDEX(16, "WALL16"),
	STRING_AT_INDEX(17, "WALL17"),
	STRING_AT_INDEX(18, "WALL18"),
	STRING_AT_INDEX(19, "WALL19"),
	STRING_AT_INDEX(20, "WALL20"),
	STRING_AT_INDEX(21, "WALL21"),
	STRING_AT_INDEX(22, "WALL22"),
	STRING_AT_INDEX(23, "WALL23"),
	STRING_AT_INDEX(24, "WALL24"),
	STRING_AT_INDEX(25, "WALL25"),
	STRING_AT_INDEX(26, "WALL26"),
	STRING_AT_INDEX(27, "WALL27"),
	STRING_AT_INDEX(28, "WALL28"),
	STRING_AT_INDEX(29, "WALL29"),
	STRING_AT_INDEX(30, "WALL30"),
	STRING_AT_INDEX(31, "WALL31"),
	STRING_AT_INDEX(32, "WALL32"),
	/* 33 */
	/* 34 */
	/* 35 */
	STRING_AT_INDEX(36, "WALL33"),
	STRING_AT_INDEX(37, "WALL34"),
	STRING_AT_INDEX(38, "WALL35"),
	STRING_AT_INDEX(39, "WALL36"),
	STRING_AT_INDEX(40, "WALL37"),
	STRING_AT_INDEX(41, "WALL38"),
	STRING_AT_INDEX(42, "WALL39"),
	STRING_AT_INDEX(43, "WALL40"),
	/* 44 */
	/* 45 */
	STRING_AT_INDEX(46, "WALL74"),
	STRING_AT_INDEX(47, "EXIT"),
	STRING_AT_INDEX(48, "ENTRANCE"),
	STRING_AT_INDEX(49, "WALL41"),
	STRING_AT_INDEX(50, "WALL42"),
	STRING_AT_INDEX(51, "WALL43"),
	STRING_AT_INDEX(52, "WALL44"),
	STRING_AT_INDEX(53, "WALL45"),
	STRING_AT_INDEX(54, "WALL46"),
	STRING_AT_INDEX(55, "WALL47"),
	STRING_AT_INDEX(56, "WALL48"),
	STRING_AT_INDEX(57, "WALL49"),
	STRING_AT_INDEX(58, "WALL50"),
	STRING_AT_INDEX(59, "WALL51"),
	STRING_AT_INDEX(60, "WALL52"),
	STRING_AT_INDEX(61, "WALL53"),
	STRING_AT_INDEX(62, "WALL54"),
	STRING_AT_INDEX(63, "WALL55"),
	STRING_AT_INDEX(64, "WALL56"),
	STRING_AT_INDEX(65, "WALL57"),
	STRING_AT_INDEX(66, "WALL58"),
	STRING_AT_INDEX(67, "WALL59"),
	STRING_AT_INDEX(68, "WALL60"),
	STRING_AT_INDEX(69, "WALL61"),
	STRING_AT_INDEX(70, "WALL62"),
	STRING_AT_INDEX(71, "WALL63"),
	STRING_AT_INDEX(72, "ELEV1"),
	STRING_AT_INDEX(73, "ELEV2"),
	STRING_AT_INDEX(74, "ELEV3"),
	STRING_AT_INDEX(75, "ELEV4"),
	STRING_AT_INDEX(76, "ELEV5"),
	STRING_AT_INDEX(77, "ELEV6"),
	STRING_AT_INDEX(78, "ELEV7"),
	STRING_AT_INDEX(79, "ELEV8"),
	STRING_AT_INDEX(80, "WALL64"),
	STRING_AT_INDEX(81, "WALL65"),
	STRING_AT_INDEX(82, "WALL66"),
	STRING_AT_INDEX(83, "WALL67"),
	STRING_AT_INDEX(84, "WALL68"),
	STRING_AT_INDEX(85, "WALL69"),
	STRING_AT_INDEX(86, "WALL70"),
	STRING_AT_INDEX(87, "WALL71"),
	STRING_AT_INDEX(88, "WALL72"),
	STRING_AT_INDEX(89, "WALL73")
};

const string_array_t darkwar_wall_tiles = {
	.entries = _darkwar_wall_tiles,
	.num_entries = 90
};
