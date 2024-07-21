unit Lua;

{$mode objfpc}
{$M+}
{$linklib lua}

interface

uses
	ctypes;
type
	lua_State = pointer;
	LuaState = class
	private
		L: lua_State;
	public
		function doString(s: AnsiString): integer;
		procedure openLibs();
		constructor create();
		destructor destroy();
	end;

{ lua.h }
procedure lua_close(L: lua_State); cdecl; external 'lua';
function lua_pcallk(L: lua_State; nargs: integer; nresults: integer; errfunc: integer; ctx: pointer; k: pointer): integer; cdecl; external 'lua';

{ lualib.h }
function luaopen_base(L: lua_State): integer; cdecl; external 'lua';
function luaopen_coroutine(L: lua_State): integer; cdecl; external 'lua';
function luaopen_table(L: lua_State): integer; cdecl; external 'lua';
function luaopen_io(L: lua_State): integer; cdecl; external 'lua';
function luaopen_os(L: lua_State): integer; cdecl; external 'lua';
function luaopen_string(L: lua_State): integer; cdecl; external 'lua';
function luaopen_utf8(L: lua_State): integer; cdecl; external 'lua';
function luaopen_math(L: lua_State): integer; cdecl; external 'lua';
function luaopen_debug(L: lua_State): integer; cdecl; external 'lua';
function luaopen_package(L: lua_State): integer; cdecl; external 'lua';
procedure luaL_openlibs(L: lua_State); cdecl; external 'lua';

{ lauxlib.h }
function luaL_newstate(): lua_State; cdecl; external 'lua';
function luaL_loadstring(L: lua_State; s: pchar): integer; cdecl; external 'lua';

{ LuaState class implementation }
implementation

constructor LuaState.create();
begin
	L := luaL_newstate();
end;

destructor LuaState.destroy();
begin
	lua_close(L);
end;

function LuaState.doString(s: AnsiString): integer;
var
	ret : integer;
begin
	ret := luaL_loadstring(L, pansichar(s));
	if (ret = 0) then
		ret := lua_pcallk(L, 0, -1, 0, nil, nil);
	doString := ret;
end;

procedure LuaState.openLibs();
begin
	luaL_openlibs(L);
end;

end.
