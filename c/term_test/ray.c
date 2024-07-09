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

#include "term.h"

void term_repaint(void)
{
	term_setformat(FG WHITE WITH BG BLUE);

	for (uint16_t yy = 1; yy <= term_getheight(); yy++)
	{
		term_setxy(1, yy);
		for (uint16_t xx = 1; xx <= term_getwidth(); xx++)
		{
			term_write("╫");
		}
	}

	term_setformat(PLAIN);
}

int main(int argc, char **argv)
{
	term_init();

	while (1)
	{
		char key;

		read(STDIN_FILENO, &key, 1);

		if (key == '\x1b')
			break;
	}

	term_quit();

	return 0;
}
