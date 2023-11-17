
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"
#include "cJSON.h"

/* allocate */
map_t *map_allocate(int width, int height, int ceiling_height)
{
	map_t *map;

	map = calloc(1, sizeof(map_t));
	map->walls = calloc(width * height, sizeof(uint8_t));
	map->entities = calloc(width * height, sizeof(uint8_t));

	map->width = width;
	map->height = height;
	map->ceiling_height = ceiling_height;

	return map;
}

/* free */
void map_free(map_t *map)
{
	free(map->walls);
	free(map->entities);
	free(map);
}

/* load from tmj file */
map_t *map_load(const char *filename)
{
	map_t *map;
	FILE *file;

	file = fopen(filename, "rb");
	if (!file) return NULL;

	fclose(file);

	return map;
}
