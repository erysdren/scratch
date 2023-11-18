
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

int main(int argc, char **argv)
{
	/* create struct on the stack */
	rtl_t rtl;

	/* allocate level in memory */
	if (!rtl_allocate(1, false, &rtl))
		return 1;

	/* make a "map" */
	rtl.maps[0].flags = 0x1;
	snprintf(rtl.maps[0].name, 22, "My Map!!");
	rtl_generate_crc(&rtl);

	/* save to disk */
	if (!rtl_save("test.rtl", &rtl))
		return 2;

	/* free allocated data */
	rtl_free(&rtl);

	/* reload map */
	if (!rtl_load("test.rtl", &rtl))
		return 3;

	/* free allocated data */
	rtl_free(&rtl);

	return 0;
}
