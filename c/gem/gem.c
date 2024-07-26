
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include <i86.h>
#include <dos.h>

#include "gem.h"

/* returns 0 if gem is available, or -1 on error */
int gem_available(void)
{
	return _dos_getvect(GEM_INTERRUPT) ? 0 : -1;
}

/* run gem command */
unsigned short gem(unsigned short opcode, gem_t *g)
{
	union REGS r;
	struct SREGS s;
	void __far *gemblk[GEM_BLOCK_SIZE];

	gemblk[GEM_BLOCK_CONTROL] = &g->control;
	gemblk[GEM_BLOCK_GLOBAL] = &g->global;
	gemblk[GEM_BLOCK_INT_IN] = &g->int_in;
	gemblk[GEM_BLOCK_INT_OUT] = &g->int_out;
	gemblk[GEM_BLOCK_ADDR_IN] = &g->addr_in;
	gemblk[GEM_BLOCK_ADDR_OUT] = &g->addr_out;

	g->control[GEM_CONTROL_OPCODE] = opcode;

	segread(&s);

	r.w.cx = 0x00C8;
	s.es = FP_SEG(&gemblk);
	r.w.bx = FP_OFF(&gemblk);

	int86x(0xEF, &r, &r, &s);

	return g->int_out[0];
}
