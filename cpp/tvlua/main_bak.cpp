
#include <iostream>
#include <LuaCpp.hpp>

using namespace LuaCpp;
using namespace LuaCpp::Registry;
using namespace LuaCpp::Engine;

void add_tvision(LuaContext &lua)
{
	std::shared_ptr<LuaLibrary> lib = std::make_shared<LuaLibrary>("tv");
	lua.AddLibrary(lib);
}

int main(int argc, char **argv)
{
	// take one input script
	if (argc != 2)
	{
		std::cout << "Must provide exactly one script file on the command line." << std::endl;
		return 0;
	}

	// create lua context
	LuaContext lua;

	// add tvision library to lua context
	add_tvision(lua);

	// compile script
	try
	{
		lua.CompileFile("script", argv[1], true);
	}
	catch (std::logic_error &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	// run script
	try
	{
		lua.Run("script");
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
