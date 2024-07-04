
#include <SDL2/SDL.h>

#include "vga8x16.h"

static const Uint8 palette[16][3] = {
	{0x00, 0x00, 0x00}, {0x00, 0x00, 0xab}, {0x00, 0xab, 0x00}, {0x00, 0xab, 0xab},
	{0xab, 0x00, 0x00}, {0xab, 0x00, 0xab}, {0xab, 0x57, 0x00}, {0xab, 0xab, 0xab},
	{0x57, 0x57, 0x57}, {0x57, 0x57, 0xff}, {0x57, 0xff, 0x57}, {0x57, 0xff, 0xff},
	{0xff, 0x57, 0x57}, {0xff, 0x57, 0xff}, {0xff, 0xff, 0x57}, {0xff, 0xff, 0xff}
};

static void render_cell(Uint8 *image, int pitch, Uint16 cell)
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
	Uint8 image[400][640];
	Uint32 format, rmask, gmask, bmask, amask;
	int bpp;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *surface8;
	SDL_Surface *surface24;
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
			uint8_t *imgpos = &image[y * 16][x * 8];

			render_cell(imgpos, 640, cell);
		}
	}

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(argv[1],
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, 640, 480);
	SDL_SetWindowMinimumSize(window, 640, 480);
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
	surface24 = SDL_CreateRGBSurface(0, 640, 400, bpp, rmask, gmask, bmask, amask);
	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, 640, 400);

	rect.x = 0;
	rect.y = 0;
	rect.w = 640;
	rect.h = 400;

	for (int y = 0; y < 400; y++)
	{
		SDL_memcpy(&((Uint8 *)surface8->pixels)[y * surface8->pitch], &image[y][0], 640);
	}

	SDL_BlitSurface(surface8, &rect, surface24, &rect);
	SDL_UpdateTexture(texture, NULL, surface24->pixels, surface24->pitch);

	while (!SDL_QuitRequested())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
				goto done;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

done:

	SDL_FreeSurface(surface8);
	SDL_FreeSurface(surface24);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
