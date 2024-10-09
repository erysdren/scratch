
#include "erysclib.h"

void erysclib_memset8(void *dest, uint8_t val, size_t n)
{
#if HAS_STOSB
	asm (
		"rep stosb\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);
#else
	uint8_t *p = (uint8_t *)dest;
	while (n--)
		*p++ = val;
#endif
}

void erysclib_memset16(void *dest, uint16_t val, size_t n)
{
#if HAS_STOSW
	asm (
		"rep stosw\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);
#else
	uint16_t *p = (uint16_t *)dest;
	while (n--)
		*p++ = val;
#endif
}

void erysclib_memset32(void *dest, uint32_t val, size_t n)
{
#if HAS_STOSD
	asm (
		"rep stosl\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);
#else
	uint32_t *p = (uint32_t *)dest;
	while (n--)
		*p++ = val;
#endif
}

void erysclib_memset64(void *dest, uint64_t val, size_t n)
{
#if HAS_STOSQ
	asm (
		"rep stosq\n\t"
		:
		: "a" (val), "c" (n), "D" (dest)
		: "memory"
	);
#else
	uint64_t *p = (uint64_t *)dest;
	while (n--)
		*p++ = val;
#endif
}
