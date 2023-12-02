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
#ifndef _CMD_H_
#define _CMD_H_
#ifdef __cplusplus
extern "C" {
#endif

/* console command structure */
typedef struct cmd_t
{
	/* name for searching */
	const char *name;

	/* help text */
	const char *help;

	/* function to call */
	int (*func)(int, char**);

	/* next in chain */
	struct cmd_t *next;

} cmd_t;

/* cmd creation macro */
#define CMD(n, h, f) (cmd_t){ .name = n, .help = h, .func = f, .next = NULL }

extern cmd_t *cmd_list;

/* retrieve cmd from chain */
cmd_t *cmd_retrieve(const char *name);

/* add cmd to chain */
void cmd_register(cmd_t *cmd);

#ifdef __cplusplus
}
#endif
#endif /* _CMD_H_ */
