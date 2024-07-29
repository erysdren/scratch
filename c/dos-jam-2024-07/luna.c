
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "luna.h"
#include "vid.h"

static int luna_drawstring(lua_State *L)
{
	const char *s = luaL_checkstring(L, 1);
	lua_Integer c = luaL_checkinteger(L, 2);
	lua_Integer x = luaL_checkinteger(L, 3);
	lua_Integer y = luaL_checkinteger(L, 4);
	char *ptr = (char *)s;
	lua_Integer sx = x;

	while (*ptr)
	{
		/* handle control characters */
		if (*ptr == '\n')
		{
			y += 1;
			ptr++;
			continue;
		}
		else if (*ptr == '\r')
		{
			x = sx;
			ptr++;
			continue;
		}
		else if (*ptr == '\t')
		{
			x += 4;
			ptr++;
			continue;
		}

		/* gone out of range */
		if (x >= VID_WIDTH || y >= VID_HEIGHT)
			break;

		vid_put_code(x, y, *ptr);
		vid_put_fg(x, y, c);

		x += 1;
		ptr++;
	}

	return 0;
}

static int luna_drawfill(lua_State *L)
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
	{"drawfill", luna_drawfill},
	{"drawstring", luna_drawstring},
	{NULL, NULL}
};

int luaopen_luna(lua_State *L)
{
	/* ignore input values here */
	lua_settop(L, 0);

	/* create appl table */
	luaL_newmetatable(L, "appl");

	/* create luna lib */
	luaL_newlib(L, luna_methods);

	return 1;
}

void luna_openlibs(lua_State *L)
{
	luaL_requiref(L, LUA_LUNALIBNAME, luaopen_luna, 1);
}

int appl_new(lua_State *L, const char *filename)
{
	int appl;

	/* create blank table for appl data */
	lua_newtable(L);

	/* set appl metatable */
	luaL_getmetatable(L, "appl");
	lua_setmetatable(L, -2);

	/* create absolute reference */
	appl = luaL_ref(L, LUA_REGISTRYINDEX);

	/* run setup script */
	lua_rawgeti(L, LUA_REGISTRYINDEX, appl);
	lua_setglobal(L, "appl");
	if (luaL_dofile(L, filename) != LUA_OK)
	{
		appl_delete(L, appl);
		return 0;
	}

	/* ignore return values */
	lua_settop(L, 0);

	/* return absolute reference */
	return appl;
}

void appl_delete(lua_State *L, int appl)
{
	luaL_unref(L, LUA_REGISTRYINDEX, appl);
}

int appl_call(lua_State *L, int appl, const char *func)
{
	if (lua_rawgeti(L, LUA_REGISTRYINDEX, appl))
	{
		if (lua_getfield(L, -1, func))
		{
			if (lua_isfunction(L, -1))
			{
				lua_rawgeti(L, LUA_REGISTRYINDEX, appl);
				lua_pcall(L, 1, 0, 0);
				return 1;
			}
		}
	}

	return 0;
}

int appl_draw(lua_State *L, int appl)
{
	if (lua_rawgeti(L, LUA_REGISTRYINDEX, appl))
	{
		if (lua_getfield(L, -1, "draw"))
		{
			if (lua_isfunction(L, -1))
			{
				lua_rawgeti(L, LUA_REGISTRYINDEX, appl);
				lua_pushinteger(L, VID_WIDTH);
				lua_pushinteger(L, VID_HEIGHT);
				lua_pcall(L, 3, 0, 0);
				return 1;
			}
		}
	}

	return 0;
}

