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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>

#include "term.h"

#define ASIZE(a) (sizeof(a)/sizeof(a[0]))

const char *toplabels[] = {
	"File",
	"Edit",
	"View",
	"Help"
};

const char *bottomlabels[] = {
	"Q: Exit"
};

void term_repaint(void)
{
	term_setformat(BRIGHT WITH FG WHITE WITH BG BLUE);

	term_setxy(1, 1);
	term_clear_line();
	for (int i = 0; i < ASIZE(toplabels); i++)
		term_printf(" %s ", toplabels[i]);

	term_setxy(1, term_getheight());
	term_clear_line();
	for (int i = 0; i < ASIZE(bottomlabels); i++)
		term_printf(" %s ", bottomlabels[i]);

	term_setformat(PLAIN);
}

int main(int argc, char **argv)
{
	term_init();

	while (1)
	{
		char key;

		read(STDIN_FILENO, &key, 1);

		if (key == '\x1b' || tolower(key) == 'q')
			break;
	}

	term_quit();

	return 0;
}
