/*
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
#ifndef _FIX32_H_
#define _FIX32_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* 32-bit signed fixed (15.16) */
typedef int32_t fix32_t;

/* 32-bit unsigned fixed (16.16) */
typedef uint32_t ufix32_t;

/* 32-bit signed fraction (0.15) */
typedef int16_t frac32_t;

/* 32-bit unsigned fraction (0.16) */
typedef uint16_t ufrac32_t;

/* mins and maxs */
#define FIX32_MAX INT32_MAX
#define FIX32_MIN INT32_MIN
#define UFIX32_MAX UINT32_MAX
#define UFIX32_MIN UINT32_MIN
#define FRAC32_MAX INT16_MAX
#define FRAC32_MIN INT16_MIN
#define UFRAC32_MAX UINT16_MAX
#define UFRAC32_MIN UINT16_MIN

/* representations of one */
#define FIX32_ONE (1 << 16)
#define UFIX32_ONE (1 << 16)
#define FRAC32_ONE (1 << 15)
#define UFRAC32_ONE (1 << 16)

/* masks */
#define FIX32_MASK (0xFFFF)
#define UFIX32_MASK (0xFFFF)
#define FRAC32_MASK (0xFFFF << 16)
#define UFRAC32_MASK (0xFFFF << 16)

/* static initialization macros */
#define FIX32(a) ((fix32_t)(FIX32_ONE * (a)))
#define UFIX32(a) ((ufix32_t)(FIX32_ONE * (a)))
#define FRAC32(a) ((frac32_t)((FRAC32_ONE * (a)) >= FRAC32_ONE ? FRAC32_ONE - 1 : FRAC32_ONE * (a)))
#define UFRAC32(a) ((ufrac32_t)((UFRAC32_ONE * (a)) >= UFRAC32_ONE ? UFRAC32_ONE - 1 : UFRAC32_ONE * (a)))

/* math macros */
#define FIX32_MUL(a, b) (((int64_t)(a) * (b)) >> 16)
#define FIX32_DIV(a, b) (((int64_t)(a) << 16) / (b))
#define FIX32_INV(a) (FIX32_DIV(FIX32(1), (a)))
#define FIX32_FLOOR(a) ((a)&FRAC32_MASK)
#define FIX32_CEIL(a) ((((a)&FIX32_MASK) == 0) ? (a) : FIX32_FLOOR((a) + FIX32_ONE))
#define FIX32_FRAC(a) ((a)&FIX32_MASK)
#define FIX32_ROUND(a) (((a)&FIX32_MASK) < FIX32(0.5f) ? FIX32_FLOOR(a) : FIX32_CEIL(a))
#define FIX32_SIN(a) fix32_sintable[(a)&2047]
#define FIX32_COS(a) fix32_sintable[((a) + 512) & 2047]

/* fixed to int */
#define FIX32_TO_INT(a) ((a) >> 16)

/* fixed to float */
#define FIX32_TO_FLOAT(a) ((a) * (1.0f / (float)FIX32_ONE))

/* fixed to double */
#define FIX32_TO_DOUBLE(a) ((a) * (1.0f / (double)FIX32_ONE))

/* fixed to fraction */
#define FIX32_TO_FRAC32(a) ((frac32_t)((a) / 2))

/* fraction to float */
#define FRAC32_TO_FLOAT(a) ((a) * (1.0f / (float)FRAC32_ONE))

/* fraction to double */
#define FRAC32_TO_DOUBLE(a) ((a) * (1.0f / (double)FRAC32_ONE))

/* fraction to fixed */
#define FRAC32_TO_FIX32(a) ((fix32_t)((a) * 2))

/* tables */
extern fix32_t fix32_sintable[];

/* guards */
#ifdef __cplusplus
}
#endif
#endif /* _FIX32_H_ */
