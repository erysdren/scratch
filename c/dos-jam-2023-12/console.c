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
#include "engine.h"
#include "utils.h"
#include "keyboard.h"

#define CON_PRINTF_STDIO 0
#define CON_NUMLINES 64
#define CON_LINESIZE 64
#define CON_BUFSIZE 4096
#define CON_PREFIXSIZE 2

static struct {
	char textbuf[CON_BUFSIZE];
	char *textbuf_ptr;
	char *lines[CON_NUMLINES];
	int num_lines;
	char input[CON_LINESIZE];
	int input_len;
	int input_cursor;
} con;

void console_init(void)
{
	/* zero structure */
	memset(&con, 0, sizeof(con));

	/* set text buffer pointer */
	con.textbuf_ptr = con.textbuf;

	/* setup input buffer */
	console_clear_input();
}

void console_quit(void)
{

}

static void console_push_line(char *ptr)
{
	con.lines[con.num_lines++] = ptr;

	/* copy second half to first half if we're about to overflow */
	if (con.num_lines >= CON_NUMLINES - 1)
	{
		void *first;
		void *second;
		int len;

		/* pointer to first half */
		first = con.lines;

		/* pointer to second half */
		second = &con.lines[(CON_NUMLINES / 2) - 1];

		/* copy and set size */
		len = sizeof(char *) * (CON_NUMLINES / 2);

		/* copy second half to first half */
		memcpy(first, second, len);

		/* zero out second half (minus one for input line) */
		second = &con.lines[CON_NUMLINES / 2];
		len = sizeof(char *) * ((CON_NUMLINES / 2) - 1);
		memset(second, 0, len);

		/* set num_lines */
		con.num_lines = CON_NUMLINES / 2;
	}
}

void console_push(char *src)
{
	int i;
	int len_src = strlen(src);

	/* bounds checks */
	if (con.textbuf_ptr + len_src + 1 > con.textbuf + CON_BUFSIZE)
		con.textbuf_ptr = con.textbuf;

	/* add string to text buffer */
	sprintf(con.textbuf_ptr, "%s", src);

	/* add pointer to lines buffer */
	console_push_line(con.textbuf_ptr);

	/* advance text buffer pointer */
	con.textbuf_ptr += len_src + 1;

	/* check for newlines and push line again */
	for (i = 0; i < len_src; i++)
	{
		if (con.textbuf_ptr[i] == '\n')
		{
			con.textbuf_ptr[i] = '\0';
			console_push_line(&con.textbuf_ptr[i + 1]);
		}
	}
}

void console_printf(const char *s, ...)
{
	static char line[CON_LINESIZE];
	va_list args;

	/* do vargs */
	va_start(args, s);
	vsnprintf(line, CON_LINESIZE, s, args);
	va_end(args);

#if CON_PRINTF_STDIO
	/* print to stdout */
	printf("%s\n", line);
#endif

	/* push up console buffer with the text */
	console_push(line);
}

void console_render(pixelmap_t *dst)
{
	int x, y, xx, yy, i, c;

	/* start y position */
	y = (dst->height / 8) - 1;

	/* draw textbuf */
	for (i = con.num_lines; i >= 0; i--)
	{
		/* handle nothing on this line */
		if (con.lines[i] == NULL)
		{
			y -= 1;
			continue;
		}
		if (con.lines[i][0] == '\0')
		{
			y -= 1;
			continue;
		}

		/* gone offscreen */
		if (y < 0)
			break;

		/* plot loop */
		for (x = 0; x < strlen(con.lines[i]); x++)
		{
			/* get dest pos */
			xx = x << 3;
			yy = y << 3;

			/* get char */
			c = con.lines[i][x] << 3;

			/* blit */
			pixelmap_blit8(dst, xx, yy, xx + 8, yy + 8, engine.font8x8, c, 0, c + 8, 8, PM_MODE_COLORKEY);
		}

		/* move y down */
		y -= 1;
	}

	/* draw input line */
	y = (dst->height / 8) - 1;
	for (x = 0; x < strlen(con.input); x++)
	{
		/* get dest pos */
		xx = x << 3;
		yy = y << 3;

		/* get char */
		c = con.input[x] << 3;

		/* blit */
		pixelmap_blit8(dst, xx, yy, xx + 8, yy + 8, engine.font8x8, c, 0, c + 8, 8, PM_MODE_COLORKEY);
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
					console_printf("\"%s\"", cvar->value.s);
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
			con.input[con.input_len] = '\0';
			console_push(con.input);
			console_eval(con.input + CON_PREFIXSIZE);
			console_clear_input();
			break;

		/* backspace */
		case '\b':
			if (con.input_len > CON_PREFIXSIZE)
			{
				if (con.input_cursor == con.input_len)
				{
					/* push cursor back */
					con.input_len--;
					con.input_cursor--;

					/* remove character */
					con.input[con.input_len] = '\0';
				}
			}
			break;

		/* printable */
		default:
			if (c < 256 && isprint(c) && con.input_len < CON_LINESIZE - 1)
			{
				if (con.input_cursor == con.input_len)
				{
					/* add character */
					con.input[con.input_len] = c;

					/* push cursor forward */
					con.input_len++;
					con.input_cursor++;
				}
			}
	}
}

void console_clear(void)
{
	memset(con.textbuf, 0, CON_BUFSIZE);
	con.textbuf_ptr = con.textbuf;
	memset(con.lines, 0, CON_NUMLINES * sizeof(char *));
	console_clear_input();
}

void console_clear_input(void)
{
	/* clear buffer */
	memset(con.input, 0, CON_LINESIZE);
	con.input_len = con.input_cursor = CON_PREFIXSIZE;

	/* setup prefix */
	con.input[0] = '>';
	con.input[1] = ' ';
}

int console_run(void)
{
	int key;
	int state = STATE_CONSOLE;

	/* process queued keyboard inputs */
	while ((key = kb_getkey()) >= 0)
	{
		switch (key)
		{
			case SC_TILDE:
			case SC_ESCAPE:
				console_clear_input();
				state = STATE_GAME;
				break;

			default:
				console_input(kb_toascii(key));
				break;
		}
	}

	/* shade game screen, render console text, then copy to video memory */
	/* TODO: add redraw back */
	pixelmap_shade8(engine.console, engine.color, 2, engine.colormap);
	console_render(engine.console);
	pixelmap_copy(engine.screen, engine.console);

	return state;
}
