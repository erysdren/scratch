
#include "sys16.h"

/*
 * memalloc
 */

/* allocate a block of memory of size bytes */
void __far *memalloc(uint16_t size)
{
	uint16_t seg = 0x0000;

	/* convert size from bytes to paragraphs */
	size = BYTES_TO_PARAGRAPHS(size);

	/* do int 21h */
	asm (
		"int $0x21\n\t"
		"mov %%ax, %0\n\t"
		: "=rm"(seg)
		: "a" (0x4800), "b" (size)
		: "memory"
	);

	/* return far pointer */
	return MK_FP(seg, 0x0000);
}

/*
 * memrealloc
 */

/* reallocate block of far memory previously allocated by memalloc() */
void __far *memrealloc(void __far *ptr, uint16_t size)
{
	/* convert size from bytes to paragraphs */
	size = BYTES_TO_PARAGRAPHS(size);

	/* do int 21h */
	asm (
		"int $0x21\n\t"
		:
		: "a" (0x4900), "b" (size), "e" (FP_SEG(ptr))
		: "memory"
	);

	/* return ptr */
	return ptr;
}

/*
 * memfree
 */

/* free block of far memory previously allocated by memalloc() */
void memfree(void __far *ptr)
{
	memrealloc(ptr, 0x0000);
}

/*
 * memset
 */

/* 8-bit memset on near pointer */
void *memset8(void *dest, uint8_t val, uint16_t n)
{
	asm (
		"rep stosb\n\t"
		:
		: "a" (val), "c" (n), "e" (0x0000), "D" (dest)
		: "memory"
	);

	return dest;
}

/* 16-bit memset on near pointer */
void *memset16(void *dest, uint16_t val, uint16_t n)
{
	asm (
		"rep stosw\n\t"
		:
		: "a" (val), "c" (n), "e" (0x0000), "D" (dest)
		: "memory"
	);

	return dest;
}

/* 8-bit memset on far pointer */
void __far *fmemset8(void __far *dest, uint8_t val, uint16_t n)
{
	asm (
		"rep stosb\n\t"
		:
		: "a" (val), "c" (n), "e" (FP_SEG(dest)), "D" (FP_OFS(dest))
		: "memory"
	);

	return dest;
}

/* 16-bit memset on far pointer */
void __far *fmemset16(void __far *dest, uint16_t val, uint16_t n)
{
	asm (
		"rep stosw\n\t"
		:
		: "a" (val), "c" (n), "e" (FP_SEG(dest)), "D" (FP_OFS(dest))
		: "memory"
	);

	return dest;
}

/*
 * memcpy
 */

/* 8-bit memcpy on near pointers */
void *memcpy8(void *dest, void *src, uint16_t n)
{
	asm (
		"rep movsb\n\t"
		:
		: "c" (n), "e" (0x0000), "D" (dest), "Rds" (0x0000), "S" (src)
		: "memory"
	);

	return dest;
}

/* 16-bit memcpy on near pointers */
void *memcpy16(void *dest, void *src, uint16_t n)
{
	asm (
		"rep movsw\n\t"
		:
		: "c" (n), "e" (0x0000), "D" (dest), "Rds" (0x0000), "S" (src)
		: "memory"
	);

	return dest;
}

/* 8-bit memcpy on far pointers */
void __far *fmemcpy8(void __far *dest, void __far *src, uint16_t n)
{
	asm (
		"rep movsb\n\t"
		:
		: "c" (n), "e" (FP_SEG(dest)), "D" (FP_OFS(dest)), "Rds" (FP_SEG(src)), "S" (FP_OFS(src))
		: "memory"
	);

	return dest;
}

/* 16-bit memcpy on far pointers */
void __far *fmemcpy16(void __far *dest, void __far *src, uint16_t n)
{
	asm (
		"rep movsw\n\t"
		:
		: "c" (n), "e" (FP_SEG(dest)), "D" (FP_OFS(dest)), "Rds" (FP_SEG(src)), "S" (FP_OFS(src))
		: "memory"
	);

	return dest;
}
