
#include "luna.h"
#include "palette.h"

static size_t num_appls = 0;
static appl_t *appls[256];

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
	sort_appls();
	vid_vsync_wait();
	for (size_t i = num_appls; i > 0; i--)
		appl_draw(L, appls[i - 1]);
}

static void think_appls(lua_State *L)
{
	for (size_t i = 0; i < num_appls; i++)
		appl_call(L, appls[i], "think");
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

	appl_t *clock = spawn_appl(L, "clock");
	appl_t *hello = spawn_appl(L, "hello");
	clock->z = 4;
	hello->z = 2;

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
		draw_appls(L);
	}

	/* shutdown and clean up */
	despawn_appls(L);
	lua_close(L);
	vid_quit();

	return 0;
}
