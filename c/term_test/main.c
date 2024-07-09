
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
