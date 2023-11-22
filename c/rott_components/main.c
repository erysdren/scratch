
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mapset.h"

int main(int argc, char **argv)
{
	mapset_t *mapset;
	int temp;

	/* load map */
	if ((mapset = mapset_load("darkwarEX.rtlx")) == NULL)
		return 1;

	/* hack hack hack */
	temp = mapset->num_maps;
	mapset->num_maps = 1;

	/* re-save one map */
	if (!mapset_save("test01.rtl", mapset))
		return 2;

	/* free allocated data */
	mapset->num_maps = temp;
	mapset_free(mapset);

	/* test */
	if ((mapset = mapset_load("test01.rtl")) == NULL)
		return 3;

	/* free allocated data */
	mapset_free(mapset);

	return 0;
}
