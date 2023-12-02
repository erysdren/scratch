/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include "pixelmap.h"
#include "console.h"
#include "cmd.h"
#include "cvar.h"

static struct {
	pixelmap_t *font8x8;
	pixelmap_t *screen;
	char line[40];
	int line_len;
	int cursor;
} console;

static char **tokenize(char *s, int *num_args)
{
	static char *argv[32];
	int argc = 0;
	char *ptr, *end;

	ptr = s;
	for(;;)
	{
		while(*ptr && isspace(*ptr))
			ptr++;

		if(!*ptr)
			break;

		end = ptr + 1;

		while(*end && !isspace(*end))
			end++;

		if (argc < 32 - 1)
			argv[argc++] = ptr;

		if (!*end)
			break;

		*end = 0;
		ptr = end + 1;
	}

	argv[argc] = 0;
	*num_args = argc;
	return argv;
}

void console_init(void)
{
	/* zero structure */
	memset(&console, 0, sizeof(console));

	/* allocate screen */
	console.screen = pixelmap_allocate(40, 25, PM_TYPE_INDEX_8, NULL);

	/* allocate font */
	console.font8x8 = pixelmap_load("font8x8.pxl");
}

void console_quit(void)
{
	pixelmap_free(console.font8x8);
	pixelmap_free(console.screen);
}

void console_push_up(char *src)
{
	char *cur;
	char *prev;
	char *p;
	int len;
	int i;

	/* bump text up */
	for (i = 1; i < console.screen->height - 1; i++)
	{
		/* get pointers */
		cur = &pixelmap_pixel8(console.screen, 0, i);
		prev = &pixelmap_pixel8(console.screen, 0, i - 1);

		/* clear prev line and copy cur line */
		memcpy(prev, cur, console.screen->stride);
	}

	/* clear cur line */
	memset(cur, 0, console.screen->stride);

	/* sanity check */
	if (!src)
		return;

	/* get len */
	len = strlen(src) > console.screen->width ? console.screen->width : strlen(src);

	/* copy in new text (and handle newline) */
	for (p = src; *p; p++)
	{
		/* handle newline */
		if (*p == '\n')
		{
			console_push_up(p + 1);
			return;
		}

		/* copy char */
		*cur++ = *p;
	}
}

void console_printf(const char *s, ...)
{
	static char text[64];
	va_list args;

	/* do vargs */
	va_start(args, s);
	vsnprintf(text, 64, s, args);
	va_end(args);

	/* print to stdout */
	printf("%s\n", text);

	/* push up console buffer with the text */
	console_push_up(text);
}

void console_render(pixelmap_t *dst)
{
	int x, y;
	int xx, yy;
	int c;

	for (y = 0; y < console.screen->height; y++)
	{
		for (x = 0; x < console.screen->width; x++)
		{
			xx = x << 3;
			yy = y << 3;

			c = pixelmap_pixel8(console.screen, x, y) << 3;

			pixelmap_blit8(dst, xx, yy, xx + 8, yy + 8, console.font8x8, c, 0, c + 8, 8, PM_MODE_COLORKEY);
		}
	}
}

void console_eval(char *s)
{
	int argc;
	char **argv;
	cmd_t *cmd;
	cvar_t *cvar;

	argv = tokenize(s, &argc);

	if (!argv || !argc)
		return;

	/* check for cmd */
	if ((cmd = cmd_retrieve(argv[0])) != NULL)
	{
		cmd->func(argc, argv);
		return;
	}

	/* check cvar */
	if ((cvar = cvar_retrieve(argv[0])) != NULL)
	{
		/* user probably wants to set it */
		if (argv[1])
		{
			/* set value */
		}
		else
		{
			/* print value */
			switch (cvar->type)
			{
				case CVAR_TYPE_BOOL:
					if (cvar->value.b)
						console_printf("true");
					else
						console_printf("false");
					break;

				case CVAR_TYPE_INT:
					console_printf("%d", cvar->value.i);
					break;

				case CVAR_TYPE_UINT:
					console_printf("%u", cvar->value.u);
					break;

				case CVAR_TYPE_FIXED:
					console_printf("%0.4f", FIX32_TO_FLOAT(cvar->value.x));
					break;

				case CVAR_TYPE_FLOAT:
					console_printf("%0.4f", cvar->value.f);
					break;

				case CVAR_TYPE_STRING:
					console_printf("%s", cvar->value.s);
					break;
			}
		}

		return;
	}

	console_printf("no valid command or cvar entered");
}

void console_input(int c)
{
	switch (c)
	{
		/* newlines */
		case '\n':
		case '\r':
			console.line[console.line_len] = '\0';
			console.line_len = console.cursor = 0;
			console_push_up(console.line);
			memset(&pixelmap_pixel8(console.screen, 0, 24), 0, console.screen->stride);
			console_eval(console.line);
			break;

		/* backspace */
		case '\b':
			if (console.line_len)
			{
				if (console.cursor == console.line_len)
				{
					console.line[console.line_len] = '\0';
					pixelmap_pixel8(console.screen, console.line_len - 1, 24) = '\0';
					console.line_len--;
					console.cursor--;
				}
			}
			break;

		/* printable */
		default:
			if (c < 256 && isprint(c) && console.line_len < 39)
			{
				if (console.cursor == console.line_len)
				{
					console.line[console.line_len++] = c;
					pixelmap_pixel8(console.screen, console.line_len - 1, 24) = c;
					console.cursor++;
				}
			}
	}
}
