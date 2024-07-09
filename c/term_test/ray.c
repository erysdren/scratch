
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
