
#ifndef _FIX16_H_
#define _FIX16_H_

#include "inttypes.h"

/* fixed types */
typedef int16_t fix16_t; /* 16-bit signed fixed (7.8) */
typedef uint16_t ufix16_t; /* 16-bit unsigned fixed (8.8) */

typedef int8_t frac16_t; /* 16-bit signed fraction (0.7) */
typedef uint8_t ufrac16_t; /* 16-bit unsigned fraction (0.8) */

/* min/max values */
#define FIX16_MAX INT16_MAX
#define FIX16_MIN INT16_MIN
#define UFIX16_MAX UINT16_MAX
#define UFIX16_MIN UINT16_MIN

/* representations of one */
#define FIX16_ONE (1 << 8)
#define UFIX16_ONE (1 << 8)
#define FRAC16_ONE (1 << 7)
#define UFRAC16_ONE (1 << 8)

/* masks */
#define FIX16_MASK (0xFF00)
#define UFIX16_MASK (0xFF00)
#define FRAC16_MASK (0x00FF)
#define UFRAC16_MASK (0x00FF)

/* static initialization macros */
#define FIX16(a) ((fix16_t)(FIX16_ONE * (a)))
#define UFIX16(a) ((ufix16_t)(FIX16_ONE * (a)))
#define FRAC16(a) ((frac16_t)((FRAC16_ONE * (a)) >= FRAC16_ONE ? FRAC16_ONE - 1 : FRAC16_ONE * (a)))
#define UFRAC16(a) ((ufrac16_t)((UFRAC16_ONE * (a)) >= UFRAC16_ONE ? UFRAC16_ONE - 1 : UFRAC16_ONE * (a)))

/* math macros */
#define FIX16_MUL(a, b) (((int32_t)(a) * (b)) >> 8)
#define FIX16_DIV(a, b) (((int32_t)(a) << 8) / (b))
#define FIX16_INV(a) (FIX16_DIV(FIX16(1), (a)))
#define FIX16_FLOOR(a) ((a)&FIX16_MASK)
#define FIX16_CEIL(a) ((((a)&FRAC16_MASK) == 0) ? (a) : FIX16_FLOOR((a) + FIX16_ONE))
#define FIX16_FRAC(a) ((a)&FRAC16_MASK)
#define FIX16_ROUND(a) (((a)&FRAC16_MASK) > FIX16(0.5f) ? FIX16_FLOOR(a) : FIX16_CEIL(a))
#define FIX16_SIN(a) fix16_sin_table[(a) & 359]
#define FIX16_COS(a) fix16_cos_table[(a) & 359]

/* fixed to int */
#define FIX16_TO_INT(a) ((a) >> 8)

/* fixed to float */
#define FIX16_TO_FLOAT(a) ((a) * (1.0f / (float)FIX16_ONE))

/* fixed to double */
#define FIX16_TO_DOUBLE(a) ((a) * (1.0f / (double)FIX16_ONE))

/* fixed to fraction */
#define FIX16_TO_FRAC16(a) ((frac16_t)((a) / 2))

/* fraction to float */
#define FRAC16_TO_FLOAT(a) ((a) * (1.0f / (float)FRAC16_ONE))

/* fraction to double */
#define FRAC16_TO_DOUBLE(a) ((a) * (1.0f / (double)FRAC16_ONE))

/* fraction to fixed */
#define FRAC16_TO_FIX16(a) ((fix16_t)((a)*2))

/* tables */
extern const fix16_t fix16_sin_table[360];
extern const fix16_t fix16_cos_table[360];

#endif /* _FIX16_H_ */
