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

#pragma once
#ifndef _RLEW_H_
#define _RLEW_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* uncompress data from SRC and read into DEST */
/* returns the number of bytes written to DEST */
size_t carmack_uncompress(uint8_t *src, size_t src_len, uint16_t *dest, size_t dest_len);

#ifdef __cplusplus
}
#endif
#endif /* _RLEW_H_ */
