
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mapset.h"
#include "wad.h"

int main(int argc, char **argv)
{
	mapset_t *mapset;
	void *walls;
	void *sprites;
	void *infos;

	mapset = mapset_open("darkwar.rtl");
	if (mapset == NULL)
		return 1;

	walls = calloc(1, MAP_PLANE_SIZE);
	sprites = calloc(1, MAP_PLANE_SIZE);
	infos = calloc(1, MAP_PLANE_SIZE);

	if (!mapset_read_map(mapset, 0, walls, sprites, infos))
		return 2;

	mapset_close(mapset);

	free(walls);
	free(sprites);
	free(infos);

	return 0;
}
