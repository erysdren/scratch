
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

static const char msg[] = "[1][Hello World from DPMI!][Ok]";

int main(void)
{
	gem_t g;

	if (gem_init() != 0)
		die("Failed to setup GEM state.");

	memset(&g, 0xFF, sizeof(gem_t));
	gem_state_write(&g);
	memset(&g, 0x00, sizeof(gem_t));
	gem_state_read(&g);

	printf("%d\n", g.control[0]);

	gem_quit();

	return 0;
}
