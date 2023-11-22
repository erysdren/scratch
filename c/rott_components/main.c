
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mapset.h"
#include "wad.h"

int main(int argc, char **argv)
{
	wad_t *wad;
	int i;

	/* open wad */
	wad = wad_open("darkwar.wad");
	if (wad == NULL)
		return 1;

	/* close wad */
	wad_close(wad);

	return 0;
}
