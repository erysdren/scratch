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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include "engine.h"
#include "dos.h"
#include "utils.h"
#include "console.h"

char **tokenize(char *s, int *num_args)
{
	static char *argv[32];
	int argc = 0;
	char *ptr, *end;

	ptr = s;
	for(;;)
	{
		while(*ptr && isspace(*ptr))
			ptr++;

		if(!*ptr)
			break;

		end = ptr + 1;

		while(*end && !isspace(*end))
			end++;

		if (argc < 32 - 1)
			argv[argc++] = ptr;

		if (!*end)
			break;

		*end = 0;
		ptr = end + 1;
	}

	argv[argc] = 0;
	*num_args = argc;
	return argv;
}

void error(const char *s, ...)
{
	static char errbuf[256];
	va_list args;

	engine_quit();

	va_start(args, s);
	vsnprintf(errbuf, 256, s, args);
	va_end(args);

	printf("Error: %s\n", errbuf);

	exit(0);
}

void warning(const char *s, ...)
{
	static char errbuf[256];
	va_list args;

	engine_quit();

	va_start(args, s);
	vsnprintf(errbuf, 256, s, args);
	va_end(args);

	console_printf("Warning: %s", errbuf);

	exit(0);
}
