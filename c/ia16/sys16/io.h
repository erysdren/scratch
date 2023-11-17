
#ifndef _IO_H_
#define _IO_H_

#include "inttypes.h"
#include "string.h"

/* write n bytes from buffer to stdout */
void write(void __far *data, uint16_t size);

/* write string to stdout */
void print(string s);

#endif /* _IO_H_ */
