/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "luna.h"
#include "palette.h"

static size_t num_appls = 0;
static appl_t *appls[256];
static appl_t *raised_appl = NULL;

static appl_t *spawn_appl(lua_State *L, const char *name)
{
	appl_t *appl = appl_new(L, name);
	if (!appl)
		return NULL;

	appls[num_appls++] = appl;

	appl_call(L, appl, "spawn");

	return appl;
}

static void despawn_appls(lua_State *L)
{
	for (size_t i = 0; i < num_appls; i++)
	{
		appl_call(L, appls[i], "despawn");
		appl_delete(L, &appls[i]);
	}

	num_appls = 0;
}

static int compare_appl(const void *a, const void *b)
{
	return (*(appl_t **)a)->z - (*(appl_t **)b)->z;
}

static void sort_appls(void)
{
	qsort(appls, num_appls, sizeof(appl_t *), compare_appl);
}

static void draw_appls(lua_State *L)
{
	vid_vsync_wait();

	/* draw raised appl */
	if (raised_appl != NULL)
	{
		int z = raised_appl->z;
		raised_appl->z = 255;
		appl_draw(L, raised_appl);
		raised_appl->z = z;
	}

	/* draw the rest */
	for (size_t i = num_appls; i > 0; i--)
	{
		if (appls[i - 1] != raised_appl)
			appl_draw(L, appls[i - 1]);
	}
}

static void think_appls(lua_State *L)
{
	for (size_t i = 0; i < num_appls; i++)
		appl_call(L, appls[i], "think");
}

static appl_t *raise_appl(int x, int y)
{
	rect_t m = {x, y, 1, 1};
	appl_t *appl = NULL;

	for (size_t i = num_appls; i > 0; i--)
	{
		if (rect_intersects(&appls[i - 1]->frame, &m))
		{
			appl = appls[i - 1];
			break;
		}
	}

	if (appl != raised_appl)
		raised_appl = appl;

	return appl;
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

	vid_fill_bg(0, 0, 80, 50, PAL_LIGHT_BLUE);

	appl_t *test1a = spawn_appl(L, "test1a");
	appl_t *test1b = spawn_appl(L, "test1b");
	test1a->z = 1;
	test1b->z = 2;
	test1a->frame.x = 2;
	test1a->frame.y = 2;
	test1a->frame.w = 8;
	test1a->frame.h = 3;
	test1b->frame.x = 4;
	test1b->frame.y = 4;
	test1b->frame.w = 8;
	test1b->frame.h = 3;

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

		/* left click to raise window */
		if (b & MOUSE_LMB)
		{
			raise_appl(x / VID_FONT_WIDTH, y / VID_FONT_HEIGHT);
		}

		think_appls(L);
		sort_appls();
		draw_appls(L);
	}

	/* shutdown and clean up */
	despawn_appls(L);
	lua_close(L);
	vid_quit();

	return 0;
}
