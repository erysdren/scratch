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

#pragma once
#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/* init console */
void console_init(void);

/* quit console */
void console_quit(void);

/* push console up with a line of text */
void console_push(char *src);

/* print formatted text to console */
void console_printf(const char *s, ...);

/* render console text to pixelmap */
void console_render(pixelmap_t *dst);

/* process one char of console input */
void console_input(int c);

/* evaluate string of console input */
void console_eval(char *s);

/* clear console non-input lines */
void console_clear(void);

/* clear console input line */
void console_clear_input(void);

/* run console */
int console_run(void);

#ifdef __cplusplus
}
#endif
#endif /* _CONSOLE_H_ */
