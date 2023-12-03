/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

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

#include "dos.h"
#include "engine.h"
#include "timer.h"

static uint64_t last_ticks;

void timerhandler(void)
{
	/* iterate tick counter */
	engine.ticks++;

	/* get frametime in seconds */
	engine.frametime = FIX32_DIV(FIX32(engine.ticks - last_ticks), FIX32(engine.tickrate));

	/* add to time */
	engine.time += engine.frametime;

	/* store last tick */
	last_ticks = engine.ticks;

	outp(0x20, 0x20);
}

void timer_init(int rate)
{
	const int speed = DOS_CLOCK_SPEED / rate;

	_go32_dpmi_get_protected_mode_interrupt_vector(8, &engine.timerhandler_old);
	engine.timerhandler_new.pm_offset = (int)timerhandler;
	engine.timerhandler_new.pm_selector = _go32_my_cs();
	_go32_dpmi_allocate_iret_wrapper(&engine.timerhandler_new);
	_go32_dpmi_set_protected_mode_interrupt_vector(8, &engine.timerhandler_new);

	outp(0x43, 0x34);
	outp(0x40, speed);
	outp(0x40, speed >> 8);

	last_ticks = 0;
	engine.tickrate = rate;
}

void timer_quit(void)
{
	_go32_dpmi_set_protected_mode_interrupt_vector(8, &engine.timerhandler_old);
	_go32_dpmi_free_iret_wrapper(&engine.timerhandler_new);

	outp(0x43, 0x34);
	outp(0x40, 0x00);
	outp(0x40, 0x00);
}
