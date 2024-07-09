/*
 Copyright (C) 2022  Lexi Summer Hale
 Copyright (C) 2024  erysdren(it/she/they)

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
static char term_buffer[0xF000];
static char *term_buffer_end = (char *)term_buffer + sizeof(term_buffer);
static char *term_buffer_ptr = (char *)term_buffer;
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
	tcgetattr(STDOUT_FILENO, &term_bak);
	tcgetattr(STDOUT_FILENO, &term);

	term.c_lflag &= (~ECHO & ~ICANON);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);

	atexit(term_quit);
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
#ifndef __MSDOS__
	signal(SIGWINCH, resize_handler);
#endif

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
	term_buffer_ptr += snprintf(term_buffer_ptr, term_buffer_end - term_buffer_ptr, s);
}

void term_printf(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	term_buffer_ptr += vsnprintf(term_buffer_ptr, term_buffer_end - term_buffer_ptr, fmt, ap);
	va_end(ap);
}

void term_printf_xy(uint16_t x, uint16_t y, const char *fmt, ...)
{
	va_list ap;

	term_setxy(x, y);

	va_start(ap, fmt);
	term_buffer_ptr += vsnprintf(term_buffer_ptr, term_buffer_end - term_buffer_ptr, fmt, ap);
	va_end(ap);
}

void term_setxy(uint16_t x, uint16_t y)
{
	term_printf(ESC "%u" WITH "%u" JUMP, y, x);
}

void term_setformat(const char *fmt)
{
	term_printf(ESC "%s" COLOR, fmt);
}

void term_clear(void)
{
	term_write(ESC CLEARTERM);
}

void term_clear_line(void)
{
	term_write(ESC CLEARLINE);
}

uint16_t term_getwidth(void)
{
	return term_width;
}

uint16_t term_getheight(void)
{
	return term_height;
}

void term_flush(void)
{
	write(STDOUT_FILENO, term_buffer, term_buffer_ptr - term_buffer);
	term_buffer_ptr = (char *)term_buffer;
}

size_t term_textsize(const char *str)
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
		term_setxy(x, y + yy);
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
	term_printf_xy(msgx + 1, msgy + (msgh / 2), message);
}
