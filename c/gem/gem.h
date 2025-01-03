/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _GEM_H_
#define _GEM_H_

#include <stdint.h>

/* software interrupt to communicate with gem */
#define GEM_INTERRUPT 0xEF

/* gem block */
enum {
	GEM_BLOCK_CONTROL,
	GEM_BLOCK_GLOBAL,
	GEM_BLOCK_INT_IN,
	GEM_BLOCK_INT_OUT,
	GEM_BLOCK_ADDR_IN,
	GEM_BLOCK_ADDR_OUT,
	GEM_BLOCK_SIZE
};

/* gem control array */
enum {
	GEM_CONTROL_OPCODE,
	GEM_CONTROL_INT_IN,
	GEM_CONTROL_INT_OUT,
	GEM_CONTROL_ADDR_IN,
	GEM_CONTROL_ADDR_OUT,
	GEM_CONTROL_SIZE
};

/* gem global array */
enum {
	GEM_GLOBAL_VERSION,
	GEM_GLOBAL_COUNT,
	GEM_GLOBAL_ID,
	GEM_GLOBAL_LOPRIVATE,
	GEM_GLOBAL_HIPRIVATE,
	GEM_GLOBAL_LOPNAME,
	GEM_GLOBAL_HIPNAME,
	GEM_GLOBAL_LO1RESV,
	GEM_GLOBAL_HI1RESV,
	GEM_GLOBAL_LO2RESV,
	GEM_GLOBAL_HI2RESV,
	GEM_GLOBAL_LO3RESV,
	GEM_GLOBAL_HI3RESV,
	GEM_GLOBAL_LO4RESV,
	GEM_GLOBAL_HI4RESV,
	GEM_GLOBAL_SIZE
};

/* gem i/o arrays */
#define GEM_INT_IN_SIZE 16
#define GEM_INT_OUT_SIZE 7
#define GEM_ADDR_IN_SIZE 2
#define GEM_ADDR_OUT_SIZE 5

enum {
	/* Application Manager */
	GEM_OPCODE_APPL_INIT = 10,
	GEM_OPCODE_APPL_READ = 11,
	GEM_OPCODE_APPL_WRITE = 12,
	GEM_OPCODE_APPL_FIND = 13,
	GEM_OPCODE_APPL_TPLAY = 14,
	GEM_OPCODE_APPL_TRECORD = 15,
	GEM_OPCODE_APPL_BVSET = 16,
	GEM_OPCODE_APPL_YIELD = 17,
	GEM_OPCODE_APPL_EXIT = 19,
	/* Event Manager */
	GEM_OPCODE_EVNT_KEYBD = 20,
	GEM_OPCODE_EVNT_BUTTON = 21,
	GEM_OPCODE_EVNT_MOUSE = 22,
	GEM_OPCODE_EVNT_MESAG = 23,
	GEM_OPCODE_EVNT_TIMER = 24,
	GEM_OPCODE_EVNT_MULTI = 25,
	GEM_OPCODE_EVNT_DCLICK = 26,
	/* Menu Manager */
	GEM_OPCODE_MENU_BAR = 30,
	GEM_OPCODE_MENU_ICHECK = 31,
	GEM_OPCODE_MENU_IENABLE = 32,
	GEM_OPCODE_MENU_TNORMAL = 33,
	GEM_OPCODE_MENU_TEXT = 34,
	GEM_OPCODE_MENU_REGISTER = 35,
	GEM_OPCODE_MENU_UNREGISTER = 36,
	GEM_OPCODE_MENU_CLICK = 37,
	/* Object Manager */
	GEM_OPCODE_OBJC_ADD = 40,
	GEM_OPCODE_OBJC_DELETE = 41,
	GEM_OPCODE_OBJC_DRAW = 42,
	GEM_OPCODE_OBJC_FIND = 43,
	GEM_OPCODE_OBJC_OFFSET = 44,
	GEM_OPCODE_OBJC_ORDER = 45,
	GEM_OPCODE_OBJC_EDIT = 46,
	GEM_OPCODE_OBJC_CHANGE = 47,
	/* Form Manager */
	GEM_OPCODE_FORM_DO = 50,
	GEM_OPCODE_FORM_DIAL = 51,
	GEM_OPCODE_FORM_ALERT = 52,
	GEM_OPCODE_FORM_ERROR = 53,
	GEM_OPCODE_FORM_CENTER = 54,
	GEM_OPCODE_FORM_KEYBD = 55,
	GEM_OPCODE_FORM_BUTTON = 56,
	/* Graphics Manager */
	GEM_OPCODE_GRAF_RUBBOX = 70,
	GEM_OPCODE_GRAF_DRAGBOX = 71,
	GEM_OPCODE_GRAF_MBOX = 72,
	GEM_OPCODE_GRAF_GROWBOX = 73,
	GEM_OPCODE_GRAF_SHRINKBOX = 74,
	GEM_OPCODE_GRAF_WATCHBOX = 75,
	GEM_OPCODE_GRAF_SLIDEBOX = 76,
	GEM_OPCODE_GRAF_HANDLE = 77,
	GEM_OPCODE_GRAF_MOUSE = 78,
	GEM_OPCODE_GRAF_MKSTATE = 79,
	/* Scrap Manager */
	GEM_OPCODE_SCRP_READ = 80,
	GEM_OPCODE_SCRP_WRITE = 81,
	GEM_OPCODE_SCRP_CLEAR = 82,
	/* File Selector Manager */
	GEM_OPCODE_FSEL_INPUT = 90,
	/* Window Manager */
	GEM_OPCODE_WIND_CREATE = 100,
	GEM_OPCODE_WIND_OPEN = 101,
	GEM_OPCODE_WIND_CLOSE = 102,
	GEM_OPCODE_WIND_DELETE = 103,
	GEM_OPCODE_WIND_GET = 104,
	GEM_OPCODE_WIND_SET = 105,
	GEM_OPCODE_WIND_FIND = 106,
	GEM_OPCODE_WIND_UPDATE = 107,
	GEM_OPCODE_WIND_CALC = 108,
	/* Resource Manager */
	GEM_OPCODE_RSRC_LOAD = 110,
	GEM_OPCODE_RSRC_FREE = 111,
	GEM_OPCODE_RSRC_GADDR = 112,
	GEM_OPCODE_RSRC_SADDR = 113,
	GEM_OPCODE_RSRC_OBFIX = 114,
	/* Shell Manager */
	GEM_OPCODE_SHEL_READ = 120,
	GEM_OPCODE_SHEL_WRITE = 121,
	GEM_OPCODE_SHEL_GET = 122,
	GEM_OPCODE_SHEL_PUT = 123,
	GEM_OPCODE_SHEL_FIND = 124,
	GEM_OPCODE_SHEL_ENVRN = 125,
	GEM_OPCODE_SHEL_RDEF = 126,
	GEM_OPCODE_SHEL_WDEF = 127,
	/* Extended Graphics Manager */
	GEM_OPCODE_XGRF_STEPCALC = 130,
	GEM_OPCODE_XGRF_2BOX = 131
};

/*
 *
 * gem types
 *
 */

typedef struct gemblk {
	void __far *control;
	void __far *global;
	void __far *int_in;
	void __far *int_out;
	void __far *addr_in;
	void __far *addr_out;
} gemblk_t;

typedef struct gem {
	unsigned short control[GEM_CONTROL_SIZE];
	unsigned short global[GEM_GLOBAL_SIZE];
	unsigned short int_in[GEM_INT_IN_SIZE];
	unsigned short int_out[GEM_INT_OUT_SIZE];
	void __far *addr_in[GEM_ADDR_IN_SIZE];
	void __far *addr_out[GEM_ADDR_OUT_SIZE];
} gem_t;

/*
 *
 * gem functions
 *
 */

/* returns 0 if gem is available, or -1 on error */
int gem_available(void);

/* run gem command */
unsigned short gem(unsigned short opcode, gem_t *gem);

#endif /* _GEM_H_ */
