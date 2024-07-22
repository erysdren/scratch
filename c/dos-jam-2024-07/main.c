
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <dos.h>
#include <io.h>
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

#include "ui.h"

static void die(const char *fmt, ...);

/*
 * video
 */

#define SCREENBYTES (2)
#define SCREENWIDTH (80)
#define SCREENHEIGHT (50)
#define FONTWIDTH (8)
#define FONTHEIGHT (8)
#define SCREENPITCH (SCREENWIDTH * SCREENBYTES)
#define SCREENSIZE (SCREENWIDTH * SCREENHEIGHT * SCREENBYTES)
#define SCREEN_AT(x, y) (screen + (y) * SCREENPITCH + (x) * SCREENBYTES)

static uint8_t *TEXTMEM = (uint8_t *)0xB8000;
static uint8_t *screen = NULL;
static uint16_t vid_old_mode = 0x02;

static void vid_mode_set(uint16_t mode)
{
	union REGS r;
	r.w.ax = mode;
	int86(0x10, &r, &r);
}

static uint16_t vid_mode_get(void)
{
	union REGS r;
	r.h.ah = 0x0f;
	int86(0x10, &r, &r);
	return r.h.al;
}

static void waitvbl(void)
{
	while(inp(0x3da) & 0x8);
	while(!(inp(0x3da) & 0x8));
}

/*
 * microsoft mouse
 */

#define MOUSE_LMB 0x1
#define MOUSE_RMB 0x2

static void mouse_read(int16_t *x, int16_t *y, int16_t *b)
{
	union REGS r;
	r.w.ax = 0x03;
	int86(0x33, &r, &r);
	if (b) *b = r.w.bx;
	if (x) *x = r.w.cx;
	if (y) *y = r.w.dx;
}

/*
 * vga text mode
 */

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

/*
 * video
 */

static uint8_t vid_bg_color = VGA_COLOR_BLACK;
static uint8_t vid_fg_color = VGA_COLOR_LIGHT_GREY;

static void vid_init(void)
{
	union REGS r;

	/* enable near pointers */
	__djgpp_nearptr_enable();

	/* save current video mode */
	vid_old_mode = vid_mode_get();

	/* add base to video memory ptr */
	TEXTMEM += __djgpp_conventional_base;

	/* set mode to 0x03 */
	r.w.ax = 0x0003;
	int86(0x10, &r, &r);

	/* change font with a reset */
	r.w.ax = 0x1112;
	r.h.bl = 0;
	int86(0x10, &r, &r);

	/* hide text mode cursor */
	r.h.ah = 0x01;
	r.w.cx = 0x2000;
	int86(0x10, &r, &r);

	/* TODO: is this redundant? */

	/* enable mouse */
	r.w.ax = 0x00;
	int86(0x33, &r, &r);

	/* show mouse */
	r.w.ax = 0x01;
	int86(0x33, &r, &r);

	/* allocate screen */
	screen = malloc(SCREENSIZE);
	if (!screen)
		die("Failed on allocation of %d bytes", SCREENSIZE);
}

static void vid_quit(void)
{
	/* free screen buffer */
	if (screen)
	{
		free(screen);
		screen = NULL;
	}

	/* reset this for good measure */
	TEXTMEM = (uint8_t *)0xB8000;

	/* reset video mode */
	vid_mode_set(vid_old_mode);

	/* disable near pointer access */
	__djgpp_nearptr_disable();
}

static void vid_plane_set(uint8_t plane)
{
	union REGS r;
	r.h.ah = 0x05;
	r.h.al = plane;
	int86(0x10, &r, &r);
}

static void vid_printf(uint16_t x, uint16_t y, const char *fmt, ...)
{
	static char message[SCREENWIDTH * SCREENHEIGHT];
	va_list ap;
	uint16_t *ofs;
	uint16_t startx = x;

	va_start(ap, fmt);
	vsnprintf(message, sizeof(message), fmt, ap);
	va_end(ap);

	for (int i = 0; i < strlen(message); i++)
	{
		if (message[i] == '\n')
		{
			y += 1;
			continue;
		}
		else if (message[i] == '\r')
		{
			x = startx;
			continue;
		}
		else if (message[i] == '\t')
		{
			x += 4;
			continue;
		}

		if (x < 0 || y < 0)
			continue;
		else if (x >= SCREENWIDTH || y >= SCREENHEIGHT)
			break;

		ofs = (uint16_t *)SCREEN_AT(x, y);
		*ofs = vga_entry(message[i], vga_entry_color(vid_fg_color, vid_bg_color));

		x += 1;
	}
}

/*
 * utils
 */

static void die(const char *fmt, ...)
{
	static char error[512];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(error, sizeof(error), fmt, ap);
	va_end(ap);

	vid_quit();

	fprintf(stderr, "%s\n", error);
	exit(1);
}

/*
 * memory
 */

static void *memset8(void *dest, uint8_t val, size_t n)
{
	asm (
		"rep stosb\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}

static void *memset16(void *dest, uint16_t val, size_t n)
{
	asm (
		"rep stosw\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}

static void *memset32(void *dest, uint32_t val, size_t n)
{
	asm (
		"rep stosl\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}

/*
 * main
 */

static void drawfill(rect_t *r, uint16_t c)
{
	rect_t clipped;

	if (r->x >= SCREENWIDTH || r->y >= SCREENHEIGHT || !r->w || !r->h)
		return;

	clipped.x = imax(r->x, 0);
	clipped.y = imax(r->y, 0);
	clipped.w = imin(r->x + r->w, SCREENWIDTH) - clipped.x;
	clipped.h = imin(r->y + r->h, SCREENHEIGHT) - clipped.y;

	for (int y = clipped.y; y < clipped.y + clipped.h; y++)
	{
		uint16_t *ofs = (uint16_t *)SCREEN_AT(clipped.x, y);
		memset16(ofs, c, clipped.w);
	}
}

static int drawscreen(void)
{
	element_t *e = NULL;
	int drawn = 0;

	while ((e = ui_next()) != NULL)
	{
		if (e->dirty)
		{
			/* draw borders */
			rect_t r = e->r;
			drawfill(&r, vga_entry(0xDB, vga_entry_color(e->fg, e->bg)));

			/* draw fill */
			r.x += 1;
			r.y += 1;
			r.w -= 2;
			r.h -= 2;
			drawfill(&r, vga_entry(' ', vga_entry_color(e->fg, e->bg)));

			/* draw label */
			if (e->label)
			{
				vid_printf(e->r.x + 1, e->r.y + 1, e->label);
			}

			drawn++;
		}
	}

	return drawn;
}

static void flipscreen(void)
{
	waitvbl();
	memcpy(TEXTMEM, screen, SCREENSIZE);
}

static void flushscreen(void)
{
	rect_t r = {0, 0, SCREENWIDTH, SCREENHEIGHT};
	ui_sort();
	ui_mark(&r);
	drawfill(&r, vga_entry(' ', vga_entry_color(vid_fg_color, vid_bg_color)));
	drawscreen();
	flipscreen();
}

int main(int argc, char **argv)
{
	rect_t r = {1, 1, 16, 12};
	int z = 0;

	/* init systems */
	vid_init();
	ui_reset();

	/* flush and redraw screen */
	flushscreen();

	/* main loop */
	while (1)
	{
		int16_t x, y, b;
		mouse_read(&x, &y, &b);
		if (b == MOUSE_LMB)
		{
			r.x = x / FONTWIDTH;
			r.y = y / FONTHEIGHT;
			ui_push("<title>\r\n<body>", &r, z, VGA_COLOR_BLUE, VGA_COLOR_RED);
			z += 1;
			ui_sort();
			ui_mark(&r);
			drawfill(&r, vga_entry_color(vid_fg_color, vid_bg_color));
		}
		else if (b == MOUSE_RMB)
		{
			break;
		}

		/* if elements were drawn, flip the screen */
		if (drawscreen())
			flipscreen();
	}

	/* shutdown */
	ui_reset();
	vid_quit();

	return 0;
}
