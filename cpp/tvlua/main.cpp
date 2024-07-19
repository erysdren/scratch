
#include <iostream>
#include <string>
#include <string_view>
#include <cassert>

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TPoint
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_TStringView
#include <tvision/tv.h>

#include <sol/sol.hpp>

void registerTVisionTypes(sol::state &lua)
{
	// TPoint
	lua.new_usertype<TPoint>("TPoint",
		sol::constructors<TPoint()>(),
		"x", &TPoint::x, "y", &TPoint::y
	);

	// TRect
	lua.new_usertype<TRect>("TRect",
		sol::constructors<TRect(), TRect(int, int, int, int), TRect(TPoint&, TPoint&)>(),
		"a", &TRect::a, "b", &TRect::b, "move", &TRect::move, "grow", &TRect::grow,
		"intersect", &TRect::intersect, "Union", &TRect::Union,
		"contains", &TRect::contains, "isEmpty", &TRect::isEmpty
	);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Must provide exactly one script file on the command line" << std::endl;
		return 0;
	}

	// create lua state
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::string);

	// register tvision types
	registerTVisionTypes(lua);

	// run script
	try
	{
		lua.script_file(argv[1]);
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

#if 0
// lua <--> cpp intertop struct
struct TLua {
	sol::function initStatusLine_lua;
	void initStatusLine_native()
	{
		std::cout << "initStatusLine_native" << std::endl;
	}

	void setter(sol::object key, sol::object value, sol::this_state)
	{
		if (key.as<std::string>() == "initStatusLine")
			this->initStatusLine_lua = value.as<sol::protected_function>();
	}
};

// register tkeys table
sol::table makeTKeysTable(sol::state &lua)
{
	return lua.create_table_with(
		"CtrlA", 0x0001, "CtrlB", 0x0002, "CtrlC", 0x0003,
		"CtrlD", 0x0004, "CtrlE", 0x0005, "CtrlF", 0x0006,
		"CtrlG", 0x0007, "CtrlH", 0x0008, "CtrlI", 0x0009,
		"CtrlJ", 0x000a, "CtrlK", 0x000b, "CtrlL", 0x000c,
		"CtrlM", 0x000d, "CtrlN", 0x000e, "CtrlO", 0x000f,
		"CtrlP", 0x0010, "CtrlQ", 0x0011, "CtrlR", 0x0012,
		"CtrlS", 0x0013, "CtrlT", 0x0014, "CtrlU", 0x0015,
		"CtrlV", 0x0016, "CtrlW", 0x0017, "CtrlX", 0x0018,
		"CtrlY", 0x0019, "CtrlZ", 0x001a,

		"Esc", 0x011b, "AltSpace", 0x0200, CtrlIns, 0x0400,
		"ShiftIns", 0x0500, "CtrlDel", 0x0600, ShiftDel, 0x0700,
		"Back", 0x0e08, "CtrlBack", 0x0e7f, ShiftTab, 0x0f00,
		"Tab", 0x0f09, AltQ, 0x1000, AltW, 0x1100,
		"AltE", 0x1200, AltR, 0x1300, AltT, 0x1400,
		"AltY", 0x1500, AltU, 0x1600, AltI, 0x1700,
		"AltO", 0x1800, AltP, 0x1900, CtrlEnter, 0x1c0a,
		"Enter", 0x1c0d, AltA, 0x1e00, AltS, 0x1f00,
		"AltD", 0x2000, AltF, 0x2100, AltG, 0x2200,
		"AltH", 0x2300, AltJ, 0x2400, AltK, 0x2500,
		"AltL", 0x2600, AltZ, 0x2c00, AltX, 0x2d00,
		"AltC", 0x2e00, AltV, 0x2f00, AltB, 0x3000,
		"AltN", 0x3100, AltM, 0x3200, F1, 0x3b00,
		"F2", 0x3c00, F3, 0x3d00, F4, 0x3e00,
		"F5", 0x3f00, F6, 0x4000, F7, 0x4100,
		"F8", 0x4200, F9, 0x4300, F10, 0x4400,
		"Home", 0x4700, Up, 0x4800, PgUp, 0x4900,
		"GrayMinus", 0x4a2d, Left, 0x4b00, Right, 0x4d00,
		"GrayPlus", 0x4e2b, End, 0x4f00, Down, 0x5000,
		"PgDn", 0x5100, Ins, 0x5200, Del, 0x5300,
		"ShiftF1", 0x5400, ShiftF2, 0x5500, ShiftF3, 0x5600,
		"ShiftF4", 0x5700, ShiftF5, 0x5800, ShiftF6, 0x5900,
		"ShiftF7", 0x5a00, ShiftF8, 0x5b00, ShiftF9, 0x5c00,
		"ShiftF10", 0x5d00, CtrlF1, 0x5e00, CtrlF2, 0x5f00,
		"CtrlF3", 0x6000, CtrlF4, 0x6100, CtrlF5, 0x6200,
		"CtrlF6", 0x6300, CtrlF7, 0x6400, CtrlF8, 0x6500,
		"CtrlF9", 0x6600, CtrlF10, 0x6700, AltF1, 0x6800,
		"AltF2", 0x6900, AltF3, 0x6a00, AltF4, 0x6b00,
		"AltF5", 0x6c00, AltF6, 0x6d00, AltF7, 0x6e00,
		"AltF8", 0x6f00, AltF9, 0x7000, AltF10, 0x7100,
		"CtrlPrtSc", 0x7200, CtrlLeft, 0x7300, CtrlRight, 0x7400,
		"CtrlEnd", 0x7500, CtrlPgDn, 0x7600, CtrlHome, 0x7700,
		"Alt1", 0x7800, Alt2, 0x7900, Alt3, 0x7a00,
		"Alt4", 0x7b00, Alt5, 0x7c00, Alt6, 0x7d00,
		"Alt7", 0x7e00, Alt8, 0x7f00, Alt9, 0x8000,
		"Alt0", 0x8100, AltMinus, 0x8200, AltEqual, 0x8300,
		"CtrlPgUp", 0x8400, NoKey, 0x0000,
	);
}

int main_2(int argc, char **argv)
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
	sol::usertype<TLua> TLua_usertype = lua.new_usertype<TLua>("TVision", sol::meta_function::new_index, &TLua::setter);

	TLua_usertype["kb"] = makeTKeysTable(lua);

	// add a static global of it
	lua["tv"] = TLua{};

	// run script
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
	TLua &tv = lua["tv"];
	if (tv.initStatusLine_lua)
		tv.initStatusLine_lua();
	else
		tv.initStatusLine_native();

	return 0;
}
#endif
