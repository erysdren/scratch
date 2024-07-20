program SDL3Test;

uses
	SDL3;

var
	ret : integer;

begin
	{ initialize SDL3 }
	ret := SDL_Init(SDL_INIT_VIDEO and SDL_INIT_AUDIO);

	{ check for error }
	if (ret < 0) then begin
		writeLn('SDL3 Error: ' + SDL_GetError());
	end else begin
		writeLn('SDL3 initialized successfully');
	end;

	{ shutdown }
	SDL_Quit();
end.
