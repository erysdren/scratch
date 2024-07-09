/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

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

#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "term.h"

#define UNUSED(x) ((void)(x))

static struct termios term;
static struct termios term_bak;
static char term_buffer[16384];
static char *term_buffer_ptr;
static uint16_t term_width, term_height;

static void resize_handler(int i)
{
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	term_width = ws.ws_col;
	term_height = ws.ws_row;
	term_write(ESC CLEARTERM);
	term_repaint();
	term_flush();
}

static void signal_handler(int i)
{
	exit(1);
}

void term_init(void)
{
	term_buffer_ptr = (char *)term_buffer;

	tcgetattr(STDOUT_FILENO, &term_bak);
	tcgetattr(STDOUT_FILENO, &term);

	term.c_lflag &= (~ECHO & ~ICANON);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);

	atexit(term_quit);
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, resize_handler);

	term_write(
		ESC ALTBUF HIGH
		ESC CLEARTERM
		ESC CURSOR LOW
	);

	term_flush();

	resize_handler(0);
}

void term_quit(void)
{
	term_write(
		ESC ALTBUF HIGH
		ESC CLEARTERM
		ESC CURSOR HIGH
		ESC ALTBUF LOW
	);

	term_flush();

	tcsetattr(STDOUT_FILENO, TCSANOW, &term_bak);
}

void term_write(const char *s)
{
	term_buffer_ptr += sprintf(term_buffer_ptr, s);
}

void term_printf(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	term_buffer_ptr += vsprintf(term_buffer_ptr, fmt, ap);
	va_end(ap);
}

void term_print_xy(uint16_t x, uint16_t y, const char *s)
{
	term_printf(ESC "%u" WITH "%u" JUMP "%s", y, x, s);
}

void term_setformat(const char *fmt)
{
	term_printf(ESC "%s" COLOR, fmt);
}

void term_flush(void)
{
	write(STDOUT_FILENO, term_buffer, term_buffer_ptr - term_buffer);
	term_buffer_ptr = (char *)term_buffer;
}

size_t term_textsize(const char* str)
{
	size_t sz = 0, i = 0;

	count: if (str[i] == 0) return sz;
	else if (str[i] == '\x1b') goto skip;
	else { ++i; ++sz; goto count; }

	skip: if (str[i] != 'm') {
		++i; goto skip;
	} else goto count;
}

void term_filledbox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *fill)
{
	for (uint16_t yy = 0; yy < h; yy++)
	{
		term_printf(ESC "%u" WITH "%u" JUMP, y + yy, x);
		for (uint16_t xx = 0; xx < w; xx++)
		{
			term_write(fill);
		}
	}
}

void term_messagebox(const char *message)
{
	uint16_t msgw = term_textsize(message) + 2;
	uint16_t msgh = 3;
	uint16_t msgx = (term_width / 2) - (msgw / 2);
	uint16_t msgy = (term_height / 2) - (msgh / 2);

	term_filledbox(msgx, msgy, msgw, msgh, " ");
	term_print_xy(msgx + 1, msgy + (msgh / 2), message);
}
