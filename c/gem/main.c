
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
	if (gem_init() != 0)
		die("Failed to setup GEM state.");

	uint16_t appid = gem_appl_init();

	gem_appl_exit();

	gem_quit();

	return 0;
}
