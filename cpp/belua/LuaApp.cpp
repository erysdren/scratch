#include <Application.h>
#include <Window.h>
#include <Button.h>
#include <View.h>
#include <String.h>
#include <Alert.h>

#include <sol/sol.hpp>

class LuaApp : public BApplication
{
public:
	LuaApp() : BApplication("application/x-vnd.LuaApp")
	{
		lua.open_libraries(sol::lib::base);
		
		// BRect
		lua.new_usertype<BRect>("BRect",
			sol::constructors<BRect(), BRect(float, float, float, float)>(),
			"left", &BRect::left, "right", &BRect::right,
			"top", &BRect::top, "bottom", &BRect::bottom
		);
	}
	
	void doFile(const char *filename)
	{
		program = lua.load_file(filename);
		program();	
	}

private:
	sol::state lua;
	sol::load_result program;
};

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	LuaApp *app = new LuaApp();
	app->doFile(argv[1]);
	app->PostMessage(B_QUIT_REQUESTED);
	delete app;

	return 0;
}
