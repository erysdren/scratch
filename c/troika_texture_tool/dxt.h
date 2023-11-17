/*
DXT1/DXT3/DXT5 texture decompression

The original code is from Benjamin Dobell, see below for details. Compared to
the original the code is now valid C89, has support for 64-bit architectures
and has been refactored. It also has support for additional formats and uses
a different PackRGBA order.

---

Copyright (c) 2012 - 2022, Matthäus G. "Anteru" Chajdas (https://anteru.net)

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

---

Copyright (C) 2009 Benjamin Dobell, Glass Echidna

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

---
*/

#ifndef _DXT_H_
#define _DXT_H_
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

void DecompressBlockBC1(uint32_t x, uint32_t y, uint32_t stride, const uint8_t *blockStorage, unsigned char *image);
void DecompressBlockBC2(uint32_t x, uint32_t y, uint32_t stride, const uint8_t *blockStorage, unsigned char *image);
void DecompressBlockBC3(uint32_t x, uint32_t y, uint32_t stride, const uint8_t *blockStorage, unsigned char *image);
void DecompressBlockBC4(uint32_t x, uint32_t y, uint32_t stride, enum BC4Mode mode, const uint8_t *blockStorage,
                        unsigned char *image);
void DecompressBlockBC5(uint32_t x, uint32_t y, uint32_t stride, enum BC5Mode mode, const uint8_t *blockStorage,
                        unsigned char *image);

#ifdef __cplusplus
}
#endif
#endif /* _DXT_H_ */
