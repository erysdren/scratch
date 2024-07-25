
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "vid.h"

__attribute__((pure)) int imin(int x, int y)
{
	return x < y ? x : y;
}

__attribute__((pure)) int imax(int x, int y)
{
	return x > y ? x : y;
}

__attribute__((pure)) int iclamp(int i, int min, int max)
{
	return imax(imin(i, max), min);
}

void die(const char *fmt, ...)
{
	static char error[2048];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(error, sizeof(error), fmt, ap);
	va_end(ap);

	vid_mode_set(0x02);

	fprintf(stderr, "%s\n", error);
	exit(1);
}
