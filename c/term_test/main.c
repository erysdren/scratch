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
