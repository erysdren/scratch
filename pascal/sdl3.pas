unit SDL3;

{$linklib SDL3}

interface

uses
	ctypes;
const
	SDL_INIT_TIMER = $00000001;
	SDL_INIT_AUDIO = $00000010;
	SDL_INIT_VIDEO = $00000020;
	SDL_INIT_JOYSTICK = $00000200;
	SDL_INIT_HAPTIC = $00001000;
	SDL_INIT_GAMEPAD = $00002000;
	SDL_INIT_EVENTS = $00004000;
	SDL_INIT_SENSOR = $00008000;
	SDL_INIT_CAMERA = $00010000;

{ SDL_error.h }
function SDL_GetError() : pchar; cdecl; external 'SDL3';

{ SDL_init.h }
function SDL_Init(flags : integer) : integer; cdecl; external 'SDL3';
procedure SDL_Quit(); cdecl; external 'SDL3';

implementation

end.
