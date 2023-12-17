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
 * Name: RLEW Format Module
 *
 * Description: Support functions for reading and writing RLEW encoded data.
 *
 * Dependencies:
 * - libc
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* compress data from SRC and write into DEST */
/* returns the number of bytes written to DEST */
size_t rlew_compress(uint16_t *src, size_t src_len, uint16_t tag, uint16_t *dest, size_t dest_len)
{
	size_t read, written;
	uint16_t count, value, i;

	/* compress and write source data */
	read = 0;
	written = 0;
	while (read < src_len && written < dest_len)
	{
		count = 1;

		/* read 16-bit word from source */
		value = *src++;
		read += sizeof(uint16_t);

		/* count repetitions */
		while (*src == value && read < src_len)
		{
			count++; /* repetitions */
			src++; /* source data */
			read += sizeof(uint16_t); /* total number of bytes read from src */
		}

		/* if more than 3 repetitions, or the value is the same as the tag */
		if (count > 3 || value == tag)
		{
			*dest++ = tag; /* tag */
			*dest++ = count; /* repetitions */
			*dest++ = value; /* value */
		}
		else
		{
			/* otherwise write out the read values */
			for (i = 0; i < count; i++)
			{
				*dest++ = value;
			}
		}

		/* total number of bytes written to dest */
		written += count * sizeof(uint16_t);
	}

	return written;
}

/* uncompress data from SRC and read into DEST */
/* returns the number of bytes written to DEST */
size_t rlew_uncompress(uint16_t *src, size_t src_len, uint16_t tag, uint16_t *dest, size_t dest_len)
{
	size_t read, written;
	uint16_t test, rle_len, rle_value, i;

	/* read plane data */
	read = 0;
	written = 0;
	while (read < src_len && written < dest_len)
	{
		/* read test value */
		test = *src++;
		read += sizeof(uint16_t);

		if (test == tag)
		{
			/* read compressed data from src */
			rle_len = *src++;
			rle_value = *src++;
			read += 2 * sizeof(uint16_t);

			/* write compressed data to dest */
			for (i = 0; i < rle_len; i++)
			{
				*dest++ = rle_value;
			}

			written += rle_len * sizeof(uint16_t);
		}
		else
		{
			/* write uncompressed data to dest */
			*dest++ = test;

			written += sizeof(uint16_t);
		}

		read = src - start;
	}

	return written;
}
