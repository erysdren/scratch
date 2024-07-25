
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
	/* init video system and set 16 color palette */
	vid_init();
	vid_palette_set(16, (uint8_t *)palette);

	/* enable and hide mouse cursor */
	mouse_enable();
	mouse_hide();

	/* root object */
	object_t *root = object_new(NULL);
	root->r = RECT(0, 0, VID_WIDTH, VID_HEIGHT);
	root->bg = PAL_LIGHT_BLUE;
	root->fg = PAL_LIGHT_GREY;

	/* window object */
	object_t *window = object_new(root);
	window->r = RECT(2, 2, 24, 12);
	window->bg = PAL_WHITE;
	window->fg = PAL_BLACK;

	/* text object */
	object_t *text = object_new(window);
	text->text = strdup("hello world!");
	text->r = RECT(window->r.x + 1, window->r.y + 1, window->r.w - 2, window->r.h - 2);
	text->bg = window->bg;
	text->fg = window->fg;

	/* draw them */
	object_draw(root);

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

		/* wait for vertical retrace */
		vid_vsync_wait();
	}

	/* free root object and all children */
	object_free(root);

	vid_quit();

	return 0;
}
