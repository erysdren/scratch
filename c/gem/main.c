
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "gem.h"

static void die(const char *fmt, ...)
{
	static char error[2048];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(error, sizeof(error), fmt, ap);
	va_end(ap);

	fprintf(stderr, "%s\n", error);
	exit(1);
}

const char alert[] = "[1][Hello World!][ Ok ]";

int main(void)
{
	gem_t g;
	unsigned short appid;

	if (gem_available() != 0)
		die("Please load GEM to run this application.");

	memset(&g, 0, sizeof(gem_t));

	gem(GEM_OPCODE_APPL_INIT, &g);

	g.int_in[0] = 1;
	g.addr_in[0] = alert;
	gem(GEM_OPCODE_FORM_ALERT, &g);

	gem(GEM_OPCODE_APPL_EXIT, &g);

	return 0;
}
