
#include "luna.h"

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

int file_exists(const char *filename)
{
	return access(filename, R_OK) == 0 ? 1 : 0;
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

void *memset8(void *dest, uint8_t val, size_t n)
{
	asm (
		"rep stosb\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}

void *memset16(void *dest, uint16_t val, size_t n)
{
	asm (
		"rep stosw\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}

void *memset32(void *dest, uint32_t val, size_t n)
{
	asm (
		"rep stosl\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);

	return dest;
}
