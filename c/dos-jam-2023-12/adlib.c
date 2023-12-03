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

#include "engine.h"
#include "utils.h"
#include "adlib.h"

#define ADLIB_PORT 0x388

static uint8_t adlib_slots[9][2] = {
	{0, 3}, {1, 4}, {2, 5}, {6, 9}, {7, 10}, {8, 11}, {12, 15}, {13, 16}, {14, 17}
};

static uint8_t adlib_offsets[18] = {
	0, 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 16, 17, 18, 19, 20, 21
};

bool adlib_detect(void)
{
	int status1, status2, i;

	adlib_output(4, 0x60);
	adlib_output(4, 0x80);

	status1 = inportb(ADLIB_PORT);

	adlib_output(2, 0xFF);
	adlib_output(4, 0x21);

	for (i = 100; i > 0; i--)
		inportb(ADLIB_PORT);

	status2 = inportb(ADLIB_PORT);

	adlib_output(4, 0x60);
	adlib_output(4, 0x80);

	if (((status1 & 0xe0) == 0x00) && ((status2 & 0xe0) == 0xc0))
	{
		adlib_clear_registers();
		return true;
	}
	else
	{
		return false;
	}
}

void adlib_output(uint8_t reg, uint8_t data)
{
	int i;

	outportb(ADLIB_PORT, reg);

	for (i = 6; i > 0; i--)
		inportb(ADLIB_PORT);

	outportb(ADLIB_PORT + 1, data);

	for (i = 35; i > 0; i--)
		inportb(ADLIB_PORT);
}

void adlib_reset(void)
{
	uint8_t i, slot1, slot2;

	/* set WSE=1 */
	adlib_output(1, 0x20);

	/* set CSM=0 & SEL=0 */
	adlib_output(8, 0);

	/* set AM Depth, VIB depth & Rhythm = 0 */
	adlib_output(0xBD, 0);

	for(i = 0; i < 9; i++)
	{
		slot1 = adlib_offsets[adlib_slots[i][0]];
		slot2 = adlib_offsets[adlib_slots[i][1]];

		/* turn note off */
		adlib_output(0xB0 + i, 0);

		/* clear frequency */
		adlib_output(0xA0 + i, 0);

		adlib_output(0xE0 + slot1, 0);
		adlib_output(0xE0 + slot2, 0);

		adlib_output(0x60 + slot1, 0xff);
		adlib_output(0x60 + slot2, 0xff);
		adlib_output(0x80 + slot1, 0xff);
		adlib_output(0x80 + slot2, 0xff);

		adlib_output(0x40 + slot1, 0xff);
		adlib_output(0x40 + slot2, 0xff);
	}
}

void adlib_clear_registers(void)
{
	uint8_t i;

	/* clear all registers */
	for (i = 1; i <= 0xF5; i++)
		adlib_output(i, 0);

	/* set WSE=1 */
	adlib_output(1, 0x20);
}
