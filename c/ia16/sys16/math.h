
#ifndef _MATH_H_
#define _MATH_H_

#include "inttypes.h"

#define ABS(a) (((a) < 0) ? -(a) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define CLAMP(a, min, max) MIN(MAX(a, min), max)

#endif /* _MATH_H_ */
