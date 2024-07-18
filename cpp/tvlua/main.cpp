
#include <iostream>
#include <string>
#include <cassert>

#include <tvision/tv.h>
#include <sol/sol.hpp>

struct tv {
	int foo = 8080;

	void setter(const char *_name, sol::object _val, sol::this_state _s)
	{
		std::cout << _name << std::endl;
	}
};

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Must provide exactly one script file on the command line" << std::endl;
		return 0;
	}

	// create lua state
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::table);

	// bind usertype
	lua.new_usertype<tv>("tv",
		"foo", &tv::foo,
		sol::meta_function::new_index, &tv::setter);

	// add a static global of it
	lua["tv"] = tv{};

	try
	{
		lua.script_file(argv[1]);
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	tv &lua_tv = lua["tv"];
	assert(lua_tv.foo == 8080);

	return 0;
}
