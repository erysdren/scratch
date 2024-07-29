
#ifndef _MEM_H_
#define _MEM_H_

#include <stdlib.h>
#include <stdint.h>

void *l_memalloc(void *ud, void *ptr, size_t osize, size_t nsize);

void *memalloc(size_t sz);
void memfree(void *p);
void *memrealloc(void *p, size_t sz);

void memdebug(FILE *f);

void *memset8(void *dest, uint8_t val, size_t n);
void *memset16(void *dest, uint16_t val, size_t n);
void *memset32(void *dest, uint32_t val, size_t n);

#endif /* _MEM_H_ */
