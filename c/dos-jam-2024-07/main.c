
#include "luna.h"
#include "palette.h"

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
	luaL_openlibs(L);
	luna_openlibs(L);

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
