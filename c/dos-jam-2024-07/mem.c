
#include <stdio.h>
#include "mem.h"
#include "util.h"

static size_t total_used = 0;
static size_t used = 0;
static size_t num_allocations = 0;
static size_t num_frees = 0;

static const uint32_t memblk_magic = 0xBEEF;

typedef struct memblk {
	uint32_t magic;
	size_t sz;
	void *p;
} memblk_t;

void *l_memalloc(void *ud, void *ptr, size_t osize, size_t nsize)
{
	return memrealloc(ptr, nsize);
}

void *memalloc(size_t sz)
{
	memblk_t *blk = calloc(1, sizeof(memblk_t) + sz);

	if (!blk)
		die("Memory allocation failed on %zu bytes", sz);

	blk->magic = memblk_magic;
	blk->sz = sz;
	blk->p = (uint8_t *)blk + sizeof(memblk_t);

	used += blk->sz;
	total_used = total_used < used ? used : total_used;

	num_allocations++;

	return blk->p;
}

void memfree(void *p)
{
	memblk_t *blk = (memblk_t *)((uint8_t *)p - sizeof(memblk_t));
	if (blk->magic != memblk_magic)
		die("Tried to free memory not allocated with memalloc()!");

	used -= blk->sz;
	total_used = total_used < used ? used : total_used;

	num_frees++;

	free(blk);
}

void *memrealloc(void *p, size_t sz)
{
	if (p == NULL)
	{
		return memalloc(sz);
	}

	memblk_t *blk = (memblk_t *)((uint8_t *)p - sizeof(memblk_t));
	if (blk->magic != memblk_magic)
		die("Tried to realloc memory not allocated with memalloc()!");

	if (sz == 0)
	{
		memfree(p);
		return NULL;
	}
	else
	{
		used -= blk->sz - sz;
		total_used = total_used < used ? used : total_used;

		blk->sz = sz;
		blk->p = realloc(blk->p, blk->sz);

		return blk->p;
	}
}

void memdebug(FILE *f)
{
	fprintf(f,
		"used: %zu\ntotal used: %zu\n# allocations: %zu\n# frees: %zu\n",
		used, total_used, num_allocations, num_frees
	);
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
