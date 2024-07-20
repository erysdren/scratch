unit Lua;

{$mode objfpc}
{$M+}
{$linklib lua}

interface

uses
	ctypes;
type
	LuaState = class
	private
		L : pointer;
	public
		constructor create();
		destructor destroy();
	end;

{ c lua functions }
function luaL_newstate() : pointer; cdecl; external 'lua';
procedure lua_close(L : pointer); cdecl; external 'lua';

{ LuaState class implementation }
implementation

constructor LuaState.create();
begin
	writeLn('hello world!');
	L := luaL_newstate();
end;

destructor LuaState.destroy();
begin
	lua_close(L);
	writeLn('goodbye world!');
end;

end.
