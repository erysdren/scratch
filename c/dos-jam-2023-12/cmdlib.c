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

#include "main.h"
#include "utils.h"
#include "cvar.h"
#include "cmd.h"
#include "cmdlib.h"
#include "console.h"

int _cmd_restart(int argc, char **argv)
{
	engine_quit();
	engine_init();
	return 0;
}

int _cmd_quit(int argc, char **argv)
{
	engine_quit();
	exit(0);
	return 0;
}

int _cmd_typeof(int argc, char **argv)
{
	cvar_t *cvar;
	cmd_t *cmd;

	if (argc < 2)
	{
		console_printf("must specify cvar or command");
		return 1;
	}

	if ((cmd = cmd_retrieve(argv[1])) != NULL)
	{
		console_printf("command, int");
		return 0;
	}

	if ((cvar = cvar_retrieve(argv[1])) != NULL)
	{
		switch (cvar->type)
		{
			case CVAR_TYPE_BOOL:
				console_printf("cvar, bool");
				break;

			case CVAR_TYPE_INT:
				console_printf("cvar, int");
				break;

			case CVAR_TYPE_UINT:
				console_printf("cvar, uint");
				break;

			case CVAR_TYPE_FIXED:
				console_printf("cvar, fixed");
				break;

			case CVAR_TYPE_FLOAT:
				console_printf("cvar, float");
				break;

			case CVAR_TYPE_STRING:
				console_printf("cvar, string");
				break;

			default:
				console_printf("cvar, unknown");
				break;
		}

		return 0;
	}

	console_printf("couldn't find cvar or command specified");
	return 1;
}

cmd_t _cmdlib[] = {
	CMD("restart", _cmd_restart),
	CMD("quit", _cmd_quit),
	CMD("exit", _cmd_quit),
	CMD("typeof", _cmd_typeof)
};

void cmdlib_init(void)
{
	for (int i = 0; i < ASIZE(_cmdlib); i++)
	{
		cmd_register(&_cmdlib[i]);
	}
}

void cmdlib_quit(void)
{

}
