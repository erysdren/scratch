
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "vid.h"

void die(const char *fmt, ...)
{
	static char error[80 * 25];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(error, sizeof(error), fmt, ap);
	va_end(ap);

	vid_mode_set(0x02);

	fprintf(stderr, "%s\n", error);
	exit(1);
}
