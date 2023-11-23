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

#include "tileset_darkwar.h"

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
tileset_entry_t _tileset_darkwar_walls[] = {
	/* 0 */
	TILESET_ENTRY(1, "WALL1"),
	TILESET_ENTRY(2, "WALL2"),
	TILESET_ENTRY(3, "WALL3"),
	TILESET_ENTRY(4, "WALL4"),
	TILESET_ENTRY(5, "WALL5"),
	TILESET_ENTRY(6, "WALL6"),
	TILESET_ENTRY(7, "WALL7"),
	TILESET_ENTRY(8, "WALL8"),
	TILESET_ENTRY(9, "WALL9"),
	TILESET_ENTRY(10, "WALL10"),
	TILESET_ENTRY(11, "WALL11"),
	TILESET_ENTRY(12, "WALL12"),
	TILESET_ENTRY(13, "WALL13"),
	TILESET_ENTRY(14, "WALL14"),
	TILESET_ENTRY(15, "WALL15"),
	TILESET_ENTRY(16, "WALL16"),
	TILESET_ENTRY(17, "WALL17"),
	TILESET_ENTRY(18, "WALL18"),
	TILESET_ENTRY(19, "WALL19"),
	TILESET_ENTRY(20, "WALL20"),
	TILESET_ENTRY(21, "WALL21"),
	TILESET_ENTRY(22, "WALL22"),
	TILESET_ENTRY(23, "WALL23"),
	TILESET_ENTRY(24, "WALL24"),
	TILESET_ENTRY(25, "WALL25"),
	TILESET_ENTRY(26, "WALL26"),
	TILESET_ENTRY(27, "WALL27"),
	TILESET_ENTRY(28, "WALL28"),
	TILESET_ENTRY(29, "WALL29"),
	TILESET_ENTRY(30, "WALL30"),
	TILESET_ENTRY(31, "WALL31"),
	TILESET_ENTRY(32, "WALL32"),
	/* 33 */
	/* 34 */
	/* 35 */
	TILESET_ENTRY(36, "WALL33"),
	TILESET_ENTRY(37, "WALL34"),
	TILESET_ENTRY(38, "WALL35"),
	TILESET_ENTRY(39, "WALL36"),
	TILESET_ENTRY(40, "WALL37"),
	TILESET_ENTRY(41, "WALL38"),
	TILESET_ENTRY(42, "WALL39"),
	TILESET_ENTRY(43, "WALL40"),
	/* 44 */
	/* 45 */
	TILESET_ENTRY(46, "WALL74"),
	TILESET_ENTRY(47, "EXIT"),
	TILESET_ENTRY(48, "ENTRANCE"),
	TILESET_ENTRY(49, "WALL41"),
	TILESET_ENTRY(50, "WALL42"),
	TILESET_ENTRY(51, "WALL43"),
	TILESET_ENTRY(52, "WALL44"),
	TILESET_ENTRY(53, "WALL45"),
	TILESET_ENTRY(54, "WALL46"),
	TILESET_ENTRY(55, "WALL47"),
	TILESET_ENTRY(56, "WALL48"),
	TILESET_ENTRY(57, "WALL49"),
	TILESET_ENTRY(58, "WALL50"),
	TILESET_ENTRY(59, "WALL51"),
	TILESET_ENTRY(60, "WALL52"),
	TILESET_ENTRY(61, "WALL53"),
	TILESET_ENTRY(62, "WALL54"),
	TILESET_ENTRY(63, "WALL55"),
	TILESET_ENTRY(64, "WALL56"),
	TILESET_ENTRY(65, "WALL57"),
	TILESET_ENTRY(66, "WALL58"),
	TILESET_ENTRY(67, "WALL59"),
	TILESET_ENTRY(68, "WALL60"),
	TILESET_ENTRY(69, "WALL61"),
	TILESET_ENTRY(70, "WALL62"),
	TILESET_ENTRY(71, "WALL63"),
	TILESET_ENTRY(72, "ELEV1"),
	TILESET_ENTRY(73, "ELEV2"),
	TILESET_ENTRY(74, "ELEV3"),
	TILESET_ENTRY(75, "ELEV4"),
	TILESET_ENTRY(76, "ELEV5"),
	TILESET_ENTRY(77, "ELEV6"),
	TILESET_ENTRY(78, "ELEV7"),
	TILESET_ENTRY(79, "ELEV8"),
	TILESET_ENTRY(80, "WALL64"),
	TILESET_ENTRY(81, "WALL65"),
	TILESET_ENTRY(82, "WALL66"),
	TILESET_ENTRY(83, "WALL67"),
	TILESET_ENTRY(84, "WALL68"),
	TILESET_ENTRY(85, "WALL69"),
	TILESET_ENTRY(86, "WALL70"),
	TILESET_ENTRY(87, "WALL71"),
	TILESET_ENTRY(88, "WALL72"),
	TILESET_ENTRY(89, "WALL73")
};
const tileset_t tileset_darkwar_walls = {
	.entries = _tileset_darkwar_walls,
	.num_entries = 90
};
