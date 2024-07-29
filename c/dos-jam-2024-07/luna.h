
#ifndef _LUNA_H_
#define _LUNA_H_

#include <lua.h>

int appl_new(lua_State *L, const char *filename);
void appl_delete(lua_State *L, int appl);
int appl_call(lua_State *L, int appl, const char *func);
int appl_draw(lua_State *L, int appl);

#define LUA_LUNALIBNAME "luna"
int luaopen_luna(lua_State *L);

void luna_openlibs(lua_State *L);

#endif /* _LUNA_H_ */
