
#include "mem.h"

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
