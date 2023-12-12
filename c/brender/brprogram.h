
#ifndef _BRPROG_H_
#define _BRPROG_H_

/* headers*/
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

enum {
	SC_ESCAPE = 0x01,
	SC_1 = 0x02,
	SC_2 = 0x03,
	SC_3 = 0x04,
	SC_4 = 0x05,
	SC_5 = 0x06,
	SC_6 = 0x07,
	SC_7 = 0x08,
	SC_8 = 0x09,
	SC_9 = 0x0A,
	SC_0 = 0x0B,
	SC_MINUS = 0x0C,
	SC_EQUALS = 0x0D,
	SC_BACKSPACE = 0x0E,
	SC_TAB = 0x0F,
	SC_Q = 0x10,
	SC_W = 0x11,
	SC_E = 0x12,
	SC_R = 0x13,
	SC_T = 0x14,
	SC_Y = 0x15,
	SC_U = 0x16,
	SC_I = 0x17,
	SC_O = 0x18,
	SC_P = 0x19,
	SC_LEFTBRACKET = 0x1A,
	SC_RIGHTBRACKET = 0x1B,
	SC_ENTER = 0x1C,
	SC_CONTROL = 0x1D,
	SC_A = 0x1E,
	SC_S = 0x1F,
	SC_D = 0x20,
	SC_F = 0x21,
	SC_G = 0x22,
	SC_H = 0x23,
	SC_J = 0x24,
	SC_K = 0x25,
	SC_L = 0x26,
	SC_SEMICOLON = 0x27,
	SC_QUOTE = 0x28,
	SC_TILDE = 0x29,
	SC_LSHIFT = 0x2A,
	SC_BACKSLASH = 0x2B,
	SC_Z = 0x2C,
	SC_X = 0x2D,
	SC_C = 0x2E,
	SC_V = 0x2F,
	SC_B = 0x30,
	SC_N = 0x31,
	SC_M = 0x32,
	SC_COMMA = 0x33,
	SC_PERIOD = 0x34,
	SC_SLASH = 0x35,
	SC_RSHIFT = 0x36,
	SC_MULTIPLY = 0x37,
	SC_ALT = 0x38,
	SC_SPACE = 0x39,
	SC_CAPSLOCK = 0x3A,
	SC_F1 = 0x3B,
	SC_F2 = 0x3C,
	SC_F3 = 0x3D,
	SC_F4 = 0x3E,
	SC_F5 = 0x3F,
	SC_F6 = 0x40,
	SC_F7 = 0x41,
	SC_F8 = 0x42,
	SC_F9 = 0x43,
	SC_F10 = 0x44,
	SC_NUMLOCK = 0x45,
	SC_SCROLLLOCK = 0x46,
	SC_HOME = 0x47,
	SC_UP = 0x48,
	SC_PAGEUP = 0x49,
	SC_LEFT = 0x4B,
	SC_RIGHT = 0x4D,
	SC_PLUS = 0x4E,
	SC_END = 0x4F,
	SC_DOWN = 0x50,
	SC_PAGEDOWN = 0x51,
	SC_INSERT = 0x52,
	SC_DELETE = 0x53,
	SC_F11 = 0x57,
	SC_F12 = 0x58
};

/* globals */
extern br_actor *world;
extern br_actor *camera;
extern float frametime;

/* entry point */
int BrProgram(const char *title, int w, int h);

/* utilities */
void BrProgramClearKeyQueue(void);
int BrProgramGetKey(int sc);

/* user must implement these */
br_error BrProgramInit(void);
void BrProgramQuit(void);
br_error BrProgramRender(br_pixelmap *colour, br_pixelmap *depth);
br_error BrProgramEvent(SDL_Event *event);

#endif /* _BRPROG_H_ */
