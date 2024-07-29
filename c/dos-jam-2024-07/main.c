
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

int main(int argc, char **argv)
{
	lua_State *L;

	/* init video system and set 16 color palette */
	vid_init();
	vid_palette_set(16, (uint8_t *)palette);

	/* enable and hide mouse cursor */
	mouse_enable();
	mouse_hide();

	/* create lua state */
	L = luaL_newstate();

	/* clear screen */
	vid_framebuffer_clear(PAL_LIGHT_BLUE, PAL_WHITE);

	/* main loop */
	while (1)
	{
		int16_t x, y, b;

		/* read mouse position and button mask */
		b = mouse_read(&x, &y);

		/* update text cursor position */
		vid_cursor_set_position(x / VID_FONT_WIDTH, y / VID_FONT_HEIGHT);

		/* quit on right click */
		if (b & MOUSE_RMB)
		{
			break;
		}

		vid_vsync_wait();
	}

	/* shutdown and clean up */
	lua_close(L);
	vid_quit();

	return 0;
}
