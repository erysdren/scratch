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

/*
 *
 * appl
 *
 */

/* register new appl and get handle (or -1 for error) */
int appl_register(lua_State *L, const char *name)
{
	static char script[256];
	int reg = -1;

	/* make full script filename */
	snprintf(script, sizeof(script), "appls/%s.lua", name);
	if (!file_exists(script))
	{
		luaL_error(L, "Appl \"%s\" does not exist or is not readable", name);
		goto fail;
	}

	/* create blank table for appl data */
	lua_newtable(L);

	/* set appl metatable */
	luaL_getmetatable(L, LUA_APPLLIBNAME);
	lua_setmetatable(L, -2);

	/* create absolute reference */
	reg = luaL_ref(L, LUA_REGISTRYINDEX);

	/* run setup script */
	lua_rawgeti(L, LUA_REGISTRYINDEX, reg);
	lua_setglobal(L, LUA_APPLLIBNAME);
	if (luaL_loadfile(L, script) != LUA_OK)
		goto fail;
	if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		goto fail;

	goto done;

fail:
	appl_unregister(L, reg);
done:
	return reg;
}

/* unregister appl by handle */
void appl_unregister(lua_State *L, int reg)
{
	luaL_unref(L, LUA_REGISTRYINDEX, reg);
}

/* create new appl and get structure */
appl_t *appl_new(lua_State *L, const char *name)
{
	appl_t *appl = NULL;
	int reg = appl_register(L, name);
	if (reg == -1)
		goto fail;

	appl = calloc(1, sizeof(appl_t));
	if (!appl)
	{
		luaL_error(L, "Memory allocation failed on %zu bytes", sizeof(appl_t));
		goto fail;
	}

	appl->name = strdup(name);
	appl->reg = reg;

	goto done;

fail:
	if (appl) free(appl);
	appl = NULL;
done:
	return appl;
}

/* delete appl and free memory */
void appl_delete(lua_State *L, appl_t **appl)
{
	appl_unregister(L, (*appl)->reg);
	free((*appl)->name);
	free(*appl);
	*appl = NULL;
}

/* call function on appl */
int appl_call(lua_State *L, appl_t *appl, const char *func)
{
	if (lua_rawgeti(L, LUA_REGISTRYINDEX, appl->reg))
	{
		if (lua_getfield(L, -1, func))
		{
			if (lua_isfunction(L, -1))
			{
				lua_rawgeti(L, LUA_REGISTRYINDEX, appl->reg);
				if (lua_pcall(L, 1, 0, 0) != LUA_OK)
					return -1;
				else
					return 0;
			}
		}
	}

	return -1;
}

/* call draw function on appl */
int appl_draw(lua_State *L, appl_t *appl)
{
	if (lua_rawgeti(L, LUA_REGISTRYINDEX, appl->reg))
	{
		if (lua_getfield(L, -1, "draw"))
		{
			if (lua_isfunction(L, -1))
			{
				vid_zbuffer_set(appl->z);
				vid_offset_set(appl->frame.x, appl->frame.y);
				vid_stencil_set(appl->frame.x, appl->frame.y, appl->frame.w, appl->frame.h);
				lua_rawgeti(L, LUA_REGISTRYINDEX, appl->reg);
				lua_pushinteger(L, appl->frame.w);
				lua_pushinteger(L, appl->frame.h);
				if (lua_pcall(L, 3, 0, 0) != LUA_OK)
					return -1;
				else
					return 0;
			}
		}
	}

	return -1;
}

/* open appl lib */
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
	lua_Integer x = luaL_checkinteger(L, 1);
	lua_Integer y = luaL_checkinteger(L, 2);
	lua_Integer c = luaL_checkinteger(L, 3);
	const char *s = luaL_checkstring(L, 4);

	vid_put_string(x, y, c, s);

	return 0;
}

/* draw background color fill */
static int L_drawfill(lua_State *L)
{
	lua_Integer x = luaL_checkinteger(L, 1);
	lua_Integer y = luaL_checkinteger(L, 2);
	lua_Integer w = luaL_checkinteger(L, 3);
	lua_Integer h = luaL_checkinteger(L, 4);
	lua_Integer c = luaL_checkinteger(L, 5);

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
