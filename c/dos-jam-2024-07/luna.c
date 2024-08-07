
#include "luna.h"

/*
 *
 * appl
 *
 */

int luaopen_appl(lua_State *L)
{
	luaL_newmetatable(L, LUA_APPLLIBNAME);
	return 0;
}

/*
 *
 * luna
 *
 */

/* draw string with specified color */
static int L_drawstring(lua_State *L)
{
	const char *s = luaL_checkstring(L, 1);
	lua_Integer c = luaL_checkinteger(L, 2);
	lua_Integer x = luaL_checkinteger(L, 3);
	lua_Integer y = luaL_checkinteger(L, 4);

	vid_put_string(x, y, c, s);

	return 0;
}

/* draw background color fill */
static int L_drawfill(lua_State *L)
{
	lua_Integer c = luaL_checkinteger(L, 1);
	lua_Integer x = luaL_checkinteger(L, 2);
	lua_Integer y = luaL_checkinteger(L, 3);
	lua_Integer w = luaL_checkinteger(L, 4);
	lua_Integer h = luaL_checkinteger(L, 5);

	vid_fill_bg(x, y, w, h, c);

	return 0;
}

static luaL_Reg luna_methods[] = {
	{"drawfill", L_drawfill},
	{"drawstring", L_drawstring},
	{NULL, NULL}
};

int luaopen_luna(lua_State *L)
{
	luaL_newlib(L, luna_methods);
	return 1;
}

/*
 *
 * open all
 *
 */

void luna_openlibs(lua_State *L)
{
	luaL_requiref(L, LUA_APPLLIBNAME, luaopen_appl, 1);
	luaL_requiref(L, LUA_LUNALIBNAME, luaopen_luna, 1);
}
