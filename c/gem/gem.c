
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pc.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

#include "gem.h"

/*
 *
 * gem state
 *
 */

static int gem_state_selector = -1;
static int gem_state_segment = -1;

/*
 *
 * utiltiies
 *
 */

#define PARAGRAPHS(sz) (((sz)+15)>>4)

/* returns > 0 if gem is present in memory */
int gem_available(void)
{
	_go32_dpmi_seginfo intr;

	_go32_dpmi_get_real_mode_interrupt_vector(GEM_INTERRUPT, &intr);

	if (intr.rm_segment == 0 && intr.rm_offset == 0)
		return -1;

	return 0;
}

/* initialize gem state */
int gem_init(void)
{
	if (gem_available() == -1)
		return -1;

	gem_state_selector = __dpmi_allocate_dos_memory(PARAGRAPHS(sizeof(gem_t)), &gem_state_segment);
	if (gem_state_selector == -1)
		return -1;

	return 0;
}

/* shutdown gem state */
void gem_quit(void)
{
	__dpmi_free_dos_memory(gem_state_selector);
}

/* read current gem state into structure */
int gem_state_read(gem_t *g)
{
	if (gem_state_selector == -1 || gem_state_segment == -1)
		return -1;

	movedata(gem_state_selector, 0, _my_ds(), (int)g, sizeof(gem_t));

	return 0;
}

/* write current gem state from structure */
int gem_state_write(gem_t *g)
{
	if (gem_state_selector == -1 || gem_state_segment == -1)
		return -1;

	movedata(_my_ds(), (int)g, gem_state_selector, 0, sizeof(gem_t));

	return 0;
}
