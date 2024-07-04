/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <SDL2/SDL.h>

#include "vga8x16.h"

#define BLINK_HZ ((1000 / 70) * 16)

static const Uint8 palette[16][3] = {
	{0x00, 0x00, 0x00}, {0x00, 0x00, 0xab}, {0x00, 0xab, 0x00}, {0x00, 0xab, 0xab},
	{0xab, 0x00, 0x00}, {0xab, 0x00, 0xab}, {0xab, 0x57, 0x00}, {0xab, 0xab, 0xab},
	{0x57, 0x57, 0x57}, {0x57, 0x57, 0xff}, {0x57, 0xff, 0x57}, {0x57, 0xff, 0xff},
	{0xff, 0x57, 0x57}, {0xff, 0x57, 0xff}, {0xff, 0xff, 0x57}, {0xff, 0xff, 0xff}
};

static void render_cell(Uint8 *image, int pitch, Uint16 cell, SDL_bool noblink)
{
	// get components
	Uint8 code = (Uint8)(cell & 0xFF);
	Uint8 attr = (Uint8)(cell >> 8);

	// break out attributes
	Uint8 blink = (attr >> 7) & 0x01;
	Uint8 bgcolor = (attr >> 4) & 0x07;
	Uint8 fgcolor = attr & 0x0F;

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			// write bgcolor
			image[y * pitch + x] = bgcolor;

			if (blink && noblink)
				continue;

			// write fgcolor
			Uint8 *bitmap = &VGA8X16[code * 16];

			if (bitmap[y] & 1 << abs(x - 7))
				image[y * pitch + x] = fgcolor;
		}
	}
}

int main(int argc, char **argv)
{
	Uint16 screen[25][80];
	Uint8 image0[400][640];
	Uint8 image1[400][640];
	Uint32 format, rmask, gmask, bmask, amask;
	int bpp;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *surface8;
	SDL_Surface *windowsurface;
	SDL_Surface *windowsurface0;
	SDL_Surface *windowsurface1;
	SDL_Color colors[16];
	SDL_Rect rect;
	FILE *input;

	if (argc < 2)
		return 0;

	input = fopen(argv[1], "rb");
	if (!input)
		return 1;

	fread(screen, 1, sizeof(screen), input);
	fclose(input);

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			uint16_t cell = screen[y][x];
			uint8_t *imgpos0 = &image0[y * 16][x * 8];
			uint8_t *imgpos1 = &image1[y * 16][x * 8];

			render_cell(imgpos0, 640, cell, SDL_FALSE);
			render_cell(imgpos1, 640, cell, SDL_TRUE);
		}
	}

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(argv[1],
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 400, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, 640, 400);
	SDL_SetWindowMinimumSize(window, 640, 400);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	surface8 = SDL_CreateRGBSurface(0, 640, 400, 8, 0, 0, 0, 0);
	SDL_FillRect(surface8, NULL, 0);

	for (int i = 0; i < 16; i++)
	{
		colors[i].r = palette[i][0];
		colors[i].g = palette[i][1];
		colors[i].b = palette[i][2];
	}

	SDL_SetPaletteColors(surface8->format->palette, colors, 0, 16);

	format = SDL_GetWindowPixelFormat(window);
	SDL_PixelFormatEnumToMasks(format, &bpp, &rmask, &gmask, &bmask, &amask);
	windowsurface0 = SDL_CreateRGBSurface(0, 640, 400, bpp, rmask, gmask, bmask, amask);
	windowsurface1 = SDL_CreateRGBSurface(0, 640, 400, bpp, rmask, gmask, bmask, amask);

	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, 640, 400);

	rect.x = 0;
	rect.y = 0;
	rect.w = 640;
	rect.h = 400;

	// make blink-off
	for (int y = 0; y < 400; y++)
		SDL_memcpy(&((Uint8 *)surface8->pixels)[y * surface8->pitch], &image0[y][0], 640);

	SDL_BlitSurface(surface8, &rect, windowsurface0, &rect);

	// make blink-on
	for (int y = 0; y < 400; y++)
		SDL_memcpy(&((Uint8 *)surface8->pixels)[y * surface8->pitch], &image1[y][0], 640);

	SDL_BlitSurface(surface8, &rect, windowsurface1, &rect);

	windowsurface = windowsurface0;

	Uint64 next = SDL_GetTicks64() + BLINK_HZ;

	// main loop
	while (!SDL_QuitRequested())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
				goto done;
		}

		Uint64 now = SDL_GetTicks64();
		if (next <= now)
		{
			if (windowsurface == windowsurface0)
				windowsurface = windowsurface1;
			else
				windowsurface = windowsurface0;

			next += BLINK_HZ;
		}

		SDL_UpdateTexture(texture, NULL, windowsurface->pixels, windowsurface->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

done:

	SDL_FreeSurface(surface8);
	SDL_FreeSurface(windowsurface0);
	SDL_FreeSurface(windowsurface1);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
