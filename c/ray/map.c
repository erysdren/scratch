
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
	if (map)
	{
		if (map->walls) free(map->walls);
		if (map->entities) free(map->entities);
		free(map);
	}
}

/* load from tmj file */
map_t *map_load(const char *filename)
{
	map_t *map = NULL;
	FILE *file = NULL;
	void *file_buffer = NULL;
	size_t file_len = 0;
	cJSON *json_root = NULL;
	cJSON *json_width = NULL;
	cJSON *json_height = NULL;

	/* open file */
	file = fopen(filename, "rb");
	if (file == NULL) return NULL;

	/* get size and read it in */
	fseek(file, 0, SEEK_END);
	file_len = ftell(file);
	fseek(file, 0, SEEK_SET);
	file_buffer = calloc(1, file_len);
	fread(file_buffer, 1, file_len, file);
	fclose(file);

	/* parse */
	json_root = cJSON_ParseWithLength(file_buffer, file_len);

	/* free buffer */
	free(file_buffer);

	/* check if parsing failed */
	if (json_root == NULL) return NULL;

	/* get width and height */
	json_width = cJSON_GetObjectItemCaseSensitive(json_root, "width");
	json_height = cJSON_GetObjectItemCaseSensitive(json_root, "height");

	/* allocate map */
	map = map_allocate(json_width->valuedouble, json_height->valuedouble, 1);

	/* free json memory */
	cJSON_Delete(json_root);

	return map;
}
