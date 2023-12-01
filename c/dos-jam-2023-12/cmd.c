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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include "cmd.h"

/* global cmd chain */
static cmd_t *cmd_list = NULL;

/* retrieve cmd from chain */
cmd_t *cmd_retrieve(const char *name)
{
	cmd_t *cmd = cmd_list;

	while (cmd != NULL)
	{
		if (strcasecmp(name, cmd->name) == 0)
			return cmd;

		/* move down chain */
		cmd = cmd->next;
	}

	return NULL;
}

/* add cmd to chain */
void cmd_register(cmd_t *cmd)
{
	/* don't add it if there's already one in the chain with the same name */
	if (cmd_retrieve(cmd->name) != NULL)
		return;

	if (cmd_list == NULL)
	{
		/* start chain */
		cmd_list = cmd;
	}
	else
	{
		/* add to chain */
		cmd->next = cmd_list;
		cmd_list = cmd;
	}
}
