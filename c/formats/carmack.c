/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

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

/*
 * Name: Carmack Format Module
 *
 * Description: Support functions for decompressing Carmack compressed data.
 *
 * Dependencies:
 * - libc
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* uncompress data from SRC and read into DEST */
/* returns the number of bytes written to DEST */
size_t carmack_uncompress(uint8_t *src, size_t src_len, uint16_t *dest, size_t dest_len)
{
	const uint8_t tag_near = 0xA7;
	const uint8_t tag_far = 0xA8;
	size_t read, written, offset;
	uint8_t low, high, *in;
	uint16_t *out, *copy;

	/* read data */
	read = 0;
	written = 0;
	in = src;
	out = dest;
	while (read <= src_len && written <= dest_len)
	{
		low = *in++;
		high = *in++;

		if (high == tag_near)
		{
			if (!low)
			{
				*out++ = (high << 8) | *in++;
			}
			else
			{
				offset = *in;
				in++;

				copy = out - offset;

				while (low--)
					*out++ = *copy++;
			}
		}
		else if (high == tag_far)
		{
			if (!low)
			{
				*out++ = (high << 8) | *in++;
			}
			else
			{
				offset = (*(in + 1) << 8) | *in;
				in += 2;

				copy = dest + offset;

				while (low--)
					*out++ = *copy++;
			}
		}
		else
		{
			*out++ = (high << 8) | low;
		}

		written = out - dest;
		read = in - src;
	}

	return written;
}
