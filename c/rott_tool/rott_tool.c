
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

int main(int argc, char **argv)
{
	/* create struct on the stack */
	rtl_t rtl;

	/* allocate a map */
	rtl_allocate(1, false, &rtl);

	/* name */
	snprintf(rtl.maps[0].name, 22, "My Map!!");

	/* regenerate CRCs */
	rtl_generate_crc(&rtl);

	/* save to disk */
	rtl_save("test.rtl", &rtl);

	/* free associated data in the struct */
	rtl_free(&rtl);

	return 0;
}
