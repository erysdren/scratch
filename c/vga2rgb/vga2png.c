
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <ctype.h>

#include "vga8x16.h"
#include "vga9x16.h"

#define FONTWIDTH (8)
#define FONTHEIGHT (16)
#define FONTPITCH (FONTWIDTH * 256)

#define SCREENWIDTH (80)
#define SCREENHEIGHT (25)
#define SCREENPITCH SCREENWIDTH

#define IMAGEWIDTH (640)
#define IMAGEHEIGHT (400)
#define IMAGECOMP (3)
#define IMAGEPITCH (IMAGEWIDTH * IMAGECOMP)

void warning(const char *fmt, ...)
{
	static char buffer[1024];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, ap);
	va_end(ap);

	fprintf(stderr, "%s\n", buffer);
}

void die(const char *fmt, ...)
{
	static char buffer[1024];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, ap);
	va_end(ap);

	fprintf(stderr, "%s\n", buffer);

	exit(1);
}

void render_cell(uint8_t *image, int pitch, uint16_t cell)
{
	static const uint8_t palette[16][3] = {
		{0x00, 0x00, 0x00}, {0x00, 0x00, 0xab}, {0x00, 0xab, 0x00}, {0x00, 0xab, 0xab},
		{0xab, 0x00, 0x00}, {0xab, 0x00, 0xab}, {0xab, 0x57, 0x00}, {0xab, 0xab, 0xab},
		{0x57, 0x57, 0x57}, {0x57, 0x57, 0xff}, {0x57, 0xff, 0x57}, {0x57, 0xff, 0xff},
		{0xff, 0x57, 0x57}, {0xff, 0x57, 0xff}, {0xff, 0xff, 0x57}, {0xff, 0xff, 0xff}
	};

	// get components
	uint8_t code = (uint8_t)(cell & 0xFF);
	uint8_t attr = (uint8_t)(cell >> 8);

	// break out attributes
	uint8_t blink = (attr >> 7) & 0x01;
	uint8_t bgcolor = (attr >> 4) & 0x07;
	uint8_t fgcolor = attr & 0x0F;

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				// write bgcolor
				image[y * pitch + x * 3 + c] = palette[bgcolor][c];

				// write fgcolor
				uint8_t *bitmap = &VGA8X16[code * 16];

				if (bitmap[y] & 1 << abs(x - 7))
					image[y * pitch + x * 3 + c] = palette[fgcolor][c];
			}
		}
	}
}

int main(int argc, char **argv)
{
	static uint8_t image[IMAGEHEIGHT][IMAGEWIDTH][IMAGECOMP];
	static uint16_t screen[SCREENHEIGHT][SCREENWIDTH];
	static char filename[1024];

	if (argc < 2)
		die("Usage: vga2png <FILE.BIN> <FILE2.BIN> <FILE3.BIN>");

	for (int i = 1; i < argc; i++)
	{
		FILE *input = fopen(argv[i], "rb");

		if (!input)
		{
			warning("Couldn't open \"%s\"", argv[i]);
			continue;
		}

		printf("Opened \"%s\"\n", argv[i]);

		// read binary screen dump
		fread(screen, 1, sizeof(screen), input);

		fclose(input);

		// render image
		memset(image, 0, sizeof(image));
		for (int y = 0; y < SCREENHEIGHT; y++)
		{
			for (int x = 0; x < SCREENWIDTH; x++)
			{
				uint16_t cell = screen[y][x];
				uint8_t *imgpos = &image[y * 16][x * 8][0];

				render_cell(imgpos, IMAGEPITCH, cell);
			}
		}

		// get filename
		strncpy(filename, argv[i], sizeof(filename));
		strcat(filename, ".png");

		// save image
		stbi_write_png(filename, IMAGEWIDTH, IMAGEHEIGHT, IMAGECOMP, image, IMAGEPITCH);

		printf("Wrote \"%s\"\n", filename);
	}

	return 0;
}
