
#include <iostream>
#include <string>
#include <cassert>

#include <tvision/tv.h>
#include <sol/sol.hpp>

struct tv {
	bool has_initStatusLine = false;
	sol::function initStatusLine;
	void _initStatusLine()
	{
		std::cout << "_initStatusLine" << std::endl;
	}

	void setter(sol::object key, sol::object value, sol::this_state)
	{
		if (key.as<std::string>() == "initStatusLine")
		{
			this->initStatusLine = value.as<sol::protected_function>();
			this->has_initStatusLine = true;
		}
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
	lua.new_usertype<tv>("tv", sol::meta_function::new_index, &tv::setter);

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

	// call functions
	tv &lua_tv = lua["tv"];
	if (lua_tv.has_initStatusLine)
		lua_tv.initStatusLine();
	else
		lua_tv._initStatusLine();

	return 0;
}
