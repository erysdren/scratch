
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

int main(int argc, char **argv)
{
	/* create struct on the stack */
	rtl_t rtl;

	/* load rtl file data into struct */
	if (!rtl_load(argv[1], &rtl))
		printf("Failed to load \"%s\", error: \"%s\"\n", argv[1], rtl.error);
	else
		printf("Loaded %d maps from \"%s\"\n", rtl.num_maps, argv[1]);

	/* free associated data in the struct */
	rtl_free(&rtl);

	return 0;
}
