
#ifndef _MEM_H_
#define _MEM_H_

#include <stdlib.h>
#include <stdint.h>

void *memset8(void *dest, uint8_t val, size_t n);
void *memset16(void *dest, uint16_t val, size_t n);
void *memset32(void *dest, uint32_t val, size_t n);

#endif /* _MEM_H_ */
