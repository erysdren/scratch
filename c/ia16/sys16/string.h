
#ifndef _STRING_H_
#define _STRING_H_

#include "inttypes.h"

/* string creation macro */
#define str(s) (string){(uint8_t *)s, sizeof(s) - 1}

/* inline string structure */
typedef struct {
	uint8_t __far *data;
	uint16_t len;
} string;

#endif /* _STRING_H_ */
