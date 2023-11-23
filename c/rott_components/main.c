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

#include "rtl.h"
#include "wad.h"
#include "tileset.h"
#include "tileset_darkwar.h"

int main(int argc, char **argv)
{
	rtl_t *rtl;
	void *walls;
	void *sprites;
	void *infos;

	rtl = rtl_open("darkwar.rtl");
	if (rtl == NULL)
		return 1;

	walls = calloc(1, RTL_MAP_PLANE_SIZE);
	sprites = calloc(1, RTL_MAP_PLANE_SIZE);
	infos = calloc(1, RTL_MAP_PLANE_SIZE);

	if (!rtl_read_map(rtl, 0, walls, sprites, infos))
		return 2;

	rtl_close(rtl);

	free(walls);
	free(sprites);
	free(infos);

	return 0;
}