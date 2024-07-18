
#include <iostream>
#include <lua.hpp>

int main(int argc, char **argv)
{
	lua_State *L;

	if (argc != 2)
	{
		std::cout << "Must provide exactly one script file on the command line" << std::endl;
		return 0;
	}

	L = luaL_newstate();
	if (!L)
	{
		std::cerr << "Failed to create Lua state" << std::endl;
		return 1;
	}

	luaL_openlibs(L);

	if (luaL_dofile(L, argv[1]) != LUA_OK)
	{
		std::cerr << lua_tostring(L, -1) << std::endl;
		return 1;
	}

	lua_close(L);

	return 0;
}
