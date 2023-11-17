
#ifndef _MAP_H_
#define _MAP_H_

#include <stdint.h>

typedef struct map_t {
	int width; 			/* width of map */
	int height;			/* height of map */
	uint8_t *walls;		/* walls buffer */
	uint8_t *entities;	/* entities buffer */
	int ceiling_height;	/* ceiling height */
} map_t;

/* allocate */
map_t *map_allocate(int width, int height, int ceiling_height);

/* free */
void map_free(map_t *map);

/* load from tmj file */
map_t *map_load(const char *filename);

#endif /* _MAP_H_ */
