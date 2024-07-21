program LuaTest;

uses
	Lua;
const
	lua_script = 'print("hello world!\n")';
var
	L : LuaState;
	ret : integer;

begin
	L := LuaState.create();
	L.openLibs();
	ret := L.doString(lua_script);
	writeLn(ret);
	L.destroy();
end.
