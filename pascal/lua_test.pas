program LuaTest;

uses
	Lua;

var
	L : LuaState;

begin
	L := LuaState.create();
	L.destroy();
end.
