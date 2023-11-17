
#ifndef _REGS_H_
#define _REGS_H_

#include "inttypes.h"

/* 16-bit registers */
struct wordregs {
	uint16_t ax, bx, cx, dx;
	uint16_t si, di, cflag;
} __attribute__((packed));

/* 8-bit registers */
struct byteregs {
	uint8_t al, ah;
	uint8_t bl, bh;
	uint8_t cl, ch;
	uint8_t dl, dh;
} __attribute__((packed));

/* segment registers */
struct sregs {
	uint16_t es;
	uint16_t ds;
	uint16_t fs;
	uint16_t gs;
	uint16_t cs;
	uint16_t ss;
} __attribute__((packed));

/* registers */
union regs {
	struct wordregs w;
	struct byteregs h;
};

/* ia16 registers */
typedef struct {

	/* main registers */
	union {

		/* 16-bit registers */
		struct {
			uint16_t ax;
			uint16_t bx;
			uint16_t cx;
			uint16_t dx;
		};

		/* 8-bit registers */
		struct {
			uint8_t al, ah;
			uint8_t bl, bh;
			uint8_t cl, ch;
			uint8_t dl, dh;
		};

	} m;

	/* index registers */
	struct {
		uint16_t si;
		uint16_t di;
		uint16_t bp;
		uint16_t sp;
	} i;

	/* segment registers */
	struct {
		uint16_t cs;
		uint16_t ds;
		uint16_t es;
		uint16_t ss;
	} s;

	/* flags */
	uint16_t flags;

} ia16_regs_t;

/* read all registers into ia16_regs_t structure */
#define ia16_regs_read(r) \
	asm volatile("mov %%ax, %0\n\t" : "=m" ((r)->m.ax)); \
	asm volatile("mov %%bx, %0\n\t" : "=m" ((r)->m.bx)); \
	asm volatile("mov %%cx, %0\n\t" : "=m" ((r)->m.cx)); \
	asm volatile("mov %%dx, %0\n\t" : "=m" ((r)->m.dx)); \
	asm volatile("mov %%si, %0\n\t" : "=m" ((r)->i.si)); \
	asm volatile("mov %%di, %0\n\t" : "=m" ((r)->i.di)); \
	asm volatile("mov %%bp, %0\n\t" : "=m" ((r)->i.bp)); \
	asm volatile("mov %%sp, %0\n\t" : "=m" ((r)->i.sp)); \
	asm volatile("mov %%cs, %0\n\t" : "=m" ((r)->s.cs)); \
	asm volatile("mov %%ds, %0\n\t" : "=m" ((r)->s.ds)); \
	asm volatile("mov %%es, %0\n\t" : "=m" ((r)->s.es)); \
	asm volatile("mov %%ss, %0\n\t" : "=m" ((r)->s.ss));

#endif /* _REGS_H_ */
