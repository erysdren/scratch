
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "luna.h"
#include "mem.h"
#include "mouse.h"
#include "palette.h"
#include "ui.h"
#include "util.h"
#include "vid.h"

enum {
	ELEMENT_TEXT
};

typedef struct element {
	int type;
	union {
		struct { char *text; uint8_t color; } text;
	};
} element_t;

typedef struct window {
	element_t **elements;
	size_t num_elements;
	char *title;
	rect_t frame;
} window_t;

window_t *window_new(const char *title)
{
	window_t *window = calloc(1, sizeof(window_t));

	window->title = strdup(title);

	return window;
}

void element_free(element_t *element)
{
	if (element->type == ELEMENT_TEXT)
		free(element->text.text);
	free(element);
}

void window_free(window_t *window)
{
	for (size_t i = 0; i < window->num_elements; i++)
		element_free(window->elements[i]);
	free(window->title);
	free(window);
}

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

	/* clear screen */
	vid_framebuffer_clear(PAL_LIGHT_BLUE, PAL_WHITE);

	/* create clock appl */
	int clock = appl_new(L, "applets/clock.lua");
	if (!clock)
		die("Failed to run \"applets/clock.lua\"");
	appl_call(L, clock, "spawn");

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

		appl_call(L, clock, "think");

		vid_vsync_wait();

		appl_draw(L, clock);
	}

	/* delete clock appl */
	appl_call(L, clock, "despawn");
	appl_delete(L, clock);

	/* shutdown and clean up */
	lua_close(L);
	vid_quit();

	return 0;
}
