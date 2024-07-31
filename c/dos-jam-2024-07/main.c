
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

/* 255 max, so 0 means none */
#define NUM_APPLS UINT8_MAX

typedef struct appl {
	int reg;
	int z;
} appl_t;

static int num_appls = 0;
static appl_t appls[NUM_APPLS];

int spawn_appl(lua_State *L, const char *filename)
{
	if (num_appls >= NUM_APPLS)
		die("No more space for appls!");

	appls[num_appls].reg = appl_new(L, filename);
	if (!appls[num_appls].reg)
		die("Failed to load \"%s\"", filename);

	appls[num_appls].z = 0;

	appl_call(L, appls[num_appls].reg, "spawn");

	return num_appls++;
}

int compare_appl(const void *a, const void *b)
{
	return ((appl_t *)a)->z - ((appl_t *)b)->z;
}

void sort_appls(void)
{
	qsort(appls, num_appls, sizeof(appl_t), compare_appl);
}

void draw_appls(lua_State *L)
{
	vid_framebuffer_clear(PAL_LIGHT_BLUE, PAL_WHITE);
	stencil_clear(0x00);
	sort_appls();

	for (int i = num_appls; i >= 0; --i)
	{
		CURRENT_Z = appls[i].z;
		appl_draw(L, appls[i].reg);
	}
}

void think_appls(lua_State *L)
{
	for (int i = 0; i < num_appls; i++)
	{
		appl_call(L, appls[i].reg, "think");
	}
}

void delete_appls(lua_State *L)
{
	for (int i = 0; i < num_appls; i++)
	{
		appl_call(L, appls[i].reg, "despawn");
		appl_delete(L, appls[i].reg);
	}
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

	/* spawn some appls */
	int test1a = spawn_appl(L, "applets/test1a.lua");
	int test1b = spawn_appl(L, "applets/test1b.lua");
	int clock = spawn_appl(L, "applets/clock.lua");

	appls[test1a].z = 2;
	appls[test1b].z = 5;
	appls[clock].z = 1;

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

		think_appls(L);

		vid_vsync_wait();
		draw_appls(L);
	}

	/* shutdown and clean up */
	delete_appls(L);
	lua_close(L);
	vid_quit();

	return 0;
}
