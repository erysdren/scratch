
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

int main(int argc, char **argv)
{
	/* create struct on the stack */
	rtl_t rtl;
	int temp;

	/* load map */
	if (!rtl_load("darkwar.rtl", &rtl))
		return 1;

	/* hack hack hack */
	temp = rtl.num_maps;
	rtl.num_maps = 1;

	/* re-save one map */
	if (!rtl_save("test01.rtl", &rtl))
		return 2;

	/* free allocated data */
	rtl.num_maps = temp;
	rtl_free(&rtl);

	/* test */
	if (!rtl_load("test01.rtl", &rtl))
		return 3;

	/* free allocated data */
	rtl_free(&rtl);

	return 0;
}
