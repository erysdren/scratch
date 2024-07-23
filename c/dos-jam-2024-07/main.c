
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "mem.h"
#include "mouse.h"
#include "palette.h"
#include "ui.h"
#include "util.h"
#include "vid.h"

struct {
	int16_t x, y, b;
} mouse;

int main(int argc, char **argv)
{
	/* init video system and set 16 color palette */
	vid_init();
	vid_palette_set(16, (uint8_t *)palette);

	/* enable and hide mouse cursor */
	mouse_enable();
	mouse_hide();

	/* clear screen */
	vid_framebuffer_clear(PAL_LIGHT_BLUE, PAL_WHITE);

	/* main loop */
	while (1)
	{
		/* read mouse position and button mask */
		mouse.b = mouse_read(&mouse.x, &mouse.y);

		/* update text cursor position */
		vid_cursor_set_position(mouse.x / VID_FONT_WIDTH, mouse.y / VID_FONT_HEIGHT);

		/* place a char on left click */
		if (mouse.b & MOUSE_LMB)
		{
			vid_putc(mouse.x / VID_FONT_WIDTH, mouse.y / VID_FONT_HEIGHT, 'A');
		}

		/* quit on right click */
		if (mouse.b & MOUSE_RMB)
		{
			break;
		}

		/* wait for vertical retrace */
		vid_vsync_wait();
	}

	vid_quit();

	return 0;
}
