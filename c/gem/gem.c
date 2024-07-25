
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include <pc.h>
#include <dpmi.h>
#include <go32.h>

#include "gem.h"

/*
 *
 * gem state
 *
 */

static gem_t gem;

/*
 *
 * utiltiies
 *
 */

/* returns > 0 if gem is present in memory */
int gem_available(void)
{
	_go32_dpmi_seginfo vec;

	_go32_dpmi_get_real_mode_interrupt_vector(GEM_INTERRUPT, &vec);

	if (vec.rm_segment == 0 && vec.rm_offset == 0)
		return -1;

	return 0;
}

/*
 *
 * init/quit
 *
 */

/* initialize gem state */
int gem_init(void)
{
	/* check if gem interrupt is regsitered */
	if (gem_available() != 0)
		return -1;

	gem.block[GEM_BLOCK_CONTROL] = __tb + offsetof(gem_t, control);
	gem.block[GEM_BLOCK_GLOBAL] = __tb + offsetof(gem_t, global);
	gem.block[GEM_BLOCK_INT_IN] = __tb + offsetof(gem_t, int_in);
	gem.block[GEM_BLOCK_INT_OUT] = __tb + offsetof(gem_t, int_out);
	gem.block[GEM_BLOCK_ADDR_IN] = __tb + offsetof(gem_t, addr_in);
	gem.block[GEM_BLOCK_ADDR_OUT] = __tb + offsetof(gem_t, addr_out);

	return 0;
}

/* shutdown gem state */
void gem_quit(void)
{
	memset(&gem, 0, sizeof(gem_t));
}

/*
 *
 * main gem api
 *
 */

uint16_t _gem_do(uint16_t opcode)
{
	__dpmi_regs regs;

	gem.control[GEM_CONTROL_OPCODE] = opcode;

	/* put gem state into transfer buffer */
	dosmemput(&gem, sizeof(gem_t), __tb);

	/* fire interrupt */
	regs.x.cx = 0x00C8;
	regs.x.es = __tb >> 4;
	regs.x.bx = __tb & 0x0f;
	__dpmi_int(0xEF, &regs);

	/* retrieve updated gem state */
	dosmemget(__tb, sizeof(gem_t), &gem);

	return gem.int_out[0];
}

/*
 * application manager
 */

uint16_t gem_appl_init(void)
{
	return _gem_do(GEM_OPCODE_APPL_INIT);
}

uint16_t gem_appl_exit(void)
{
	return _gem_do(GEM_OPCODE_APPL_EXIT);
}

/*
 * form manager
 */

uint16_t gem_form_alert(uint16_t btn, const char *msg)
{
	return _gem_do(GEM_OPCODE_APPL_EXIT);
}
