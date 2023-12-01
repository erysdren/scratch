/*/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#ifndef _MATH_H_
#define _MATH_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include "fix32.h"

/* integer math */
#define isqr(a) ((a) * (a))
#define imuldiv(a, b, c) (((a) * (b)) / c)
#define imin(a, b) ((a) < (b) ? (a) : (b))
#define imax(a, b) ((a) > (b) ? (a) : (b))

/* generic comparison functions */
#define abs(a) (((a) >= 0) ? (a) : -(a))
#define sgn(a) (((a) < 0) ? -1 : (((a) > 0) ? 1 : 0))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define clamp(a, b, c) min(max(a, b), c)

#ifdef __cplusplus
}
#endif
#endif /* _MATH_H_ */