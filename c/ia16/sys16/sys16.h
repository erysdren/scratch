
#ifndef _SYS16_H_
#define _SYS16_H_

#define TRUE (1)
#define FALSE (0)
#define NULL ((void *)0)

/* integer types */
#include "inttypes.h"

/* math */
#include "math.h"

/* 16-bit fixed point */
#include "fix16.h"

/* string handling */
#include "string.h"

/* memory handling */
#include "memory.h"

/* x86 register structures */
#include "regs.h"

/* x86 assembly helpers */
#include "asm.h"

/* console i/o */
#include "io.h"

/* video i/o */
#include "video.h"

/* file i/o */
#include "file.h"

#endif /* _SYS16_H_ */
