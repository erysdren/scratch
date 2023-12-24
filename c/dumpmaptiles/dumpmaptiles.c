
#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int clut[16][3] = {
	{0x00, 0x00, 0x00},
	{0x00, 0x00, 0xAA},
	{0x00, 0xAA, 0x00},
	{0x00, 0xAA, 0xAA},
	{0xAA, 0x00, 0x00},
	{0xAA, 0x00, 0xAA},
	{0xAA, 0x55, 0x00},
	{0xAA, 0xAA, 0xAA},
	{0x55, 0x55, 0x55},
	{0x55, 0x55, 0xFF},
	{0x55, 0xFF, 0x55},
	{0x55, 0xFF, 0xFF},
	{0xFF, 0x55, 0x55},
	{0xFF, 0x55, 0xFF},
	{0xFF, 0xFF, 0x55},
	{0xFF, 0xFF, 0xFF}
};

int main(int argc, char **argv)
{
	FILE *datfile, *deffile;
	uint16_t w, h;
	int x, y, i, b, c;
	uint8_t image[7][7][3];
	uint8_t source[30];
	char filename[32];
	char tilenum[6];
	char tilename[64];
	char *ptr;

	datfile = fopen("MAPTILES.DAT", "rb");
	deffile = fopen("MAPDATA.DEF", "rb");

	/* read files */
	while (1)
	{
		if (feof(datfile) || feof(deffile))
			break;

		/* read def file */
		fread(tilenum, 5, 1, deffile);
		tilenum[5] = '\0';

		/* get name */
		fgets(tilename, 64, deffile);
		for (ptr = tilename; *ptr; ptr++)
			if (*ptr == '\n' || *ptr == '\r')
				*ptr = '\0';

		/* get num */
		i = strtol(tilenum, NULL, 16);

		/* seek past "header" */
		fseek(datfile, i * 34 + 4, SEEK_SET);

		/* read source planes */
		fread(source, 30, 1, datfile);

		/* construct image */
		memset(image, 0, sizeof(image));
		for (y = 0; y < 7; y++)
		{
			for (x = 0; x < 7; x++)
			{
				c = 0;

				if (source[y * 4] & 1 << (x + 1))
					c |= 0x8;
				if (source[y * 4 + 1] & 1 << (x + 1))
					c |= 0x4;
				if (source[y * 4 + 2] & 1 << (x + 1))
					c |= 0x2;
				if (source[y * 4 + 3] & 1 << (x + 1))
					c |= 0x1;

				image[y][(x - 6) * -1][0] = clut[c][0];
				image[y][(x - 6) * -1][1] = clut[c][1];
				image[y][(x - 6) * -1][2] = clut[c][2];
			}
		}

		/* write tile */
		sprintf(filename, "tile%04d.png", i, tilename);
		stbi_write_png(filename, 7, 7, 3, image, 7 * 3);
	}

	fclose(datfile);

	return 0;
}
