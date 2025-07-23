// little tool to extract POSTAL (1997) sprite array files into transparent bmps
// it uses some code from the official POSTAL source, so this is GPLv2
// --erysdren

#include <SDL3/SDL.h>

#pragma pack(push, 1)
typedef struct vec3s {
	int16_t x, y, z;
} vec3s_t;

typedef struct vec3d {
	double x, y, z;
} vec3d_t;

typedef struct spry {
	uint32_t magic; // "SPRY"
	uint32_t version; // 1
	uint16_t num_sprites;
} spry_t;

typedef struct sprt {
	uint32_t magic; // "SPRT"
	uint32_t version; // 3
	vec3s_t position;
	int16_t rotation;
	int32_t width;
	int32_t height;
	vec3d_t fposition;
	vec3d_t facceleration;
	vec3d_t fvelocity;
	uint32_t flags;
	vec3s_t hotspot;
	uint32_t has_image;
} sprt_t;

typedef struct im {
	uint32_t magic; // "IM  "
	uint32_t version; // 5
	uint32_t type;
	uint32_t type_destination;
	uint32_t len_data;
	int16_t width;
	int16_t height;
	int16_t buffer_width;
	int16_t buffer_height;
	int16_t hotspot_x;
	int16_t hotspot_y;
	int32_t pitch;
	int16_t depth;
	uint16_t has_data;
	uint16_t has_palette;
} im_t;

typedef struct fspr8 {
	char magic[10]; // "__FSPR8__\0"
	uint16_t version; // 6
	uint16_t type;
	uint32_t len_pixels;
	uint32_t len_codes;
	uint32_t reserved[4];
} fspr8_t;
#pragma pack(pop)

int main(int argc, char **argv)
{
	SDL_Surface *basepic = NULL, *basepicrgba = NULL;

	if (argc < 3)
	{
		SDL_Log("usage: say2bmp homer.bmp homer00a.say homer00b.say <...>");
		return 0;
	}

	basepic = SDL_LoadBMP(argv[1]);
	if (!basepic)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to open %s", argv[1]);
		return 1;
	}

	basepicrgba = SDL_CreateSurface(basepic->w, basepic->h, SDL_PIXELFORMAT_RGBA32);
	SDL_FillSurfaceRect(basepicrgba, NULL, 0);

	for (int arg = 2; arg < argc; arg++)
	{
		spry_t spry;
		SDL_IOStream *io = NULL;

		io = SDL_IOFromFile(argv[arg], "rb");
		if (!io)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to open %s", argv[arg]);
			continue;
		}

		SDL_ReadIO(io, &spry, sizeof(spry));
		for (int s = 0; s < spry.num_sprites; s++)
		{
			sprt_t sprt;
			im_t im;
			SDL_ReadIO(io, &sprt, sizeof(sprt));
			if (!sprt.has_image)
				continue;
			SDL_ReadIO(io, &im, sizeof(im));
			if (im.type == 12) // FSPR8
			{
				uint8_t *pixels = NULL, *codes = NULL;
				uint32_t *line_offsets = NULL, *code_offsets = NULL;
				SDL_Surface *dst = NULL;
				fspr8_t fspr8;
				SDL_ReadIO(io, &fspr8, sizeof(fspr8));

				pixels = SDL_malloc(fspr8.len_pixels);
				codes = SDL_malloc(fspr8.len_codes);
				line_offsets = SDL_malloc((im.height + 1) * sizeof(uint32_t));
				code_offsets = SDL_malloc((im.height + 1) * sizeof(uint32_t));

				SDL_ReadIO(io, pixels, fspr8.len_pixels);
				SDL_ReadIO(io, codes, fspr8.len_codes);
				SDL_ReadIO(io, line_offsets, (im.height + 1) * sizeof(uint32_t));
				SDL_ReadIO(io, code_offsets, (im.height + 1) * sizeof(uint32_t));

				dst = SDL_CreateSurface(im.width, im.height, SDL_PIXELFORMAT_INDEX8);

				if (SDL_MUSTLOCK(dst))
					SDL_LockSurface(dst);

				uint8_t *dstline = dst->pixels;
				uint8_t code = 0;

				// https://github.com/RWS-Studios/POSTAL-SourceCode/blob/main/RSPiX/Src/GREEN/BLiT/FSPR8.cpp#L251-L274
				for (int y = 0; y < im.height; y++, dstline += dst->pitch)
				{
					uint8_t *srcptr = pixels + line_offsets[y];
					uint8_t *codeptr = codes + code_offsets[y];
					uint8_t *dstptr = dstline;

					NextCode3:

					//==============================================================
					// 1) Do the clear run:
					code = *(codeptr)++;	// Get Skip Length
					if (code == 255) continue;// End of line code
					dstptr += code;		// Skip

					//==============================================================
					// 2) Do the opaque run:
					code = *(codeptr)++;			// Get Skip Length
					if (!code) goto NextCode3;

					do	*(dstptr++) = *(srcptr++);	// Copy pixel
					while (--code);

					goto NextCode3;
				}

				if (SDL_MUSTLOCK(dst))
					SDL_UnlockSurface(dst);

				SDL_SetSurfacePalette(dst, SDL_GetSurfacePalette(basepic));
				SDL_SetSurfaceColorKey(dst, true, 0);

				char name[256];
				SDL_snprintf(name, sizeof(name), "%s.%d.bmp", argv[arg], s);

				SDL_SaveBMP(dst, name);

				SDL_Log("saved %s", name);

				SDL_BlitSurface(dst, NULL, basepicrgba, &(SDL_Rect){sprt.position.x, sprt.position.y, dst->w, dst->h});

				if (dst) SDL_DestroySurface(dst);
				if (pixels) SDL_free(pixels);
				if (codes) SDL_free(codes);
				if (line_offsets) SDL_free(line_offsets);
				if (code_offsets) SDL_free(code_offsets);
			}
		}

		if (io) SDL_CloseIO(io);
	}

	char name[256];
	SDL_snprintf(name, sizeof(name), "%s.sprites.bmp", argv[1]);
	SDL_SaveBMP(basepicrgba, name);

	if (basepic) SDL_DestroySurface(basepic);
	if (basepicrgba) SDL_DestroySurface(basepicrgba);
	return 0;
}
