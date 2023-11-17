
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "inttypes.h"

/* far pointer manipulation */
#define FP_OFS(x) ((uint16_t)((uint32_t)(x) & 0xFFFF))
#define FP_SEG(x) ((uint16_t)((uint32_t)(x) >> 16))
#define MK_FP(s, o) (void __far*)(((uint32_t)(s) << 16) | (uint32_t)(o))

/* helper macros */
#define BYTES_TO_PARAGRAPHS(a) ((a) % 16 != 0 ? ((a) / 16) + 1 : (a) / 16)

/*
 * memalloc
 */

/* allocate a block of far memory of size bytes */
void __far *memalloc(uint16_t size);

/*
 * memrealloc
 */

/* reallocate block of far memory previously allocated by memalloc() */
void __far *memrealloc(void __far *ptr, uint16_t size);

/*
 * memfree
 */

/* free block of far memory previously allocated by memalloc() */
void memfree(void __far *ptr);

/*
 * memset
 */

/* 8-bit memset on near pointer */
void *memset8(void *dest, uint8_t val, uint16_t n);

/* 16-bit memset on near pointer */
void *memset16(void *dest, uint16_t val, uint16_t n);

/* 8-bit memset on far pointer */
void __far *fmemset8(void __far *dest, uint8_t val, uint16_t n);

/* 16-bit memset on far pointer */
void __far *fmemset16(void __far *dest, uint16_t val, uint16_t n);

/*
 * memcpy
 */

/* 8-bit memcpy on near pointers */
void *memcpy8(void *dest, void *src, uint16_t n);

/* 16-bit memcpy on near pointers */
void *memcpy16(void *dest, void *src, uint16_t n);

/* 8-bit memcpy on far pointers */
void __far *fmemcpy8(void __far *dest, void __far *src, uint16_t n);

/* 16-bit memcpy on far pointers */
void __far *fmemcpy16(void __far *dest, void __far *src, uint16_t n);

#endif /* _MEMORY_H_ */
