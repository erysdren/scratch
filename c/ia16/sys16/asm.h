
#ifndef _ASM_H_
#define _ASM_H_

#include "inttypes.h"
#include "regs.h"

/* fire x86 interrupt */
void int86(int n, union regs *in, union regs *out);
void int86x(int n, union regs *in, union regs *out, struct sregs *s);

/* ia16 interrupt */
void interrupt_ia16(int i, ia16_regs_t *regs);

/* inline assembly commands */
#define enable() asm("sti")
#define disable() asm("cli")

/* send byte out of port */
#define outp(p, v) \
	asm volatile( \
		"outb %1, %0" \
		:: "d"(p), "a"((uint8_t)v))

/* send word out of port */
#define outpw(p, v) \
	asm volatile( \
		"outw %1, %0" \
		:: "d"(p), "a"((uint16_t)v))

/* get byte from port */
static inline uint8_t inp(int p)
{
	uint8_t res;
	asm volatile(
		"inb %1, %0" \
		: "=a"(res) : "d"(p));
	return res;
}

/* get word from port */
static inline uint16_t inpw(int p)
{
	uint16_t res;
	asm volatile(
		"inw %1, %0" \
		: "=a"(res) : "d"(p));
	return res;
}

#endif /* _ASM_H_ */
