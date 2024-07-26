
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

static const char welcome[] = "welcome to luna!\r\npress rmb to exit.\r\npress lmb to create a new window.";

static int screen_dirty = 0;

void drawScreen(object_t *root)
{
	vid_vsync_wait();
	object_draw(root);
	screen_dirty = 0;
}

object_t *addWindow(object_t *root, int x, int y)
{
	/* window object */
	object_t *window = object_new(root);
	window->r = RECT(x, y, 24, 12);
	window->bg = PAL_WHITE;
	window->fg = PAL_BLACK;

	/* text object */
	object_t *text = object_new(window);
	text->text = strdup(welcome);
	text->r = RECT(1, 1, -2, -2);
	text->bg = -1;
	text->fg = -1;

	screen_dirty = 1;

	return window;
}

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
	root->fg = PAL_WHITE;

	/* add example window */
	object_t *window = addWindow(root, 2, 2);

	drawScreen(root);

	/* main loop */
	while (1)
	{
		int16_t x, y, b;

		/* read mouse position and button mask */
		b = mouse_read(&x, &y);

		/* update text cursor position */
		vid_cursor_set_position(x / VID_FONT_WIDTH, y / VID_FONT_HEIGHT);

		/* create window on left click */
		if (b & MOUSE_LMB)
		{
			window = addWindow(root, x / VID_FONT_WIDTH, y / VID_FONT_HEIGHT);
		}

		/* quit on right click */
		if (b & MOUSE_RMB)
		{
			break;
		}

		if (screen_dirty)
			drawScreen(window);
	}

	/* free root object and all children */
	object_free(root);

	vid_quit();

	return 0;
}
