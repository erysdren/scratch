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
#include "cvar.h"
#include "cmd.h"
#include "cmdlib.h"
#include "console.h"
#include "level.h"
#include "ray.h"

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

int _cmd_clear(int argc, char **argv)
{
	console_clear();
	return 0;
}

int _cmd_find(int argc, char **argv)
{
	int i;
	cmd_t *cmd;
	cvar_t *cvar;
	char *ptr;

	if (argc < 2)
	{
		console_printf("must specify search string");
		return 1;
	}

	/* iterate over cmds */
	cmd = cmd_list;
	while (cmd)
	{
		/* do text search */
		if ((ptr = strstr(cmd->name, argv[1])) != NULL)
			console_printf("cmd: %s", cmd->name);

		/* next */
		cmd = cmd->next;
	}

	/* iterate over cvars */
	cvar = cvar_list;
	while (cvar)
	{
		/* do text search */
		if ((ptr = strstr(cvar->name, argv[1])) != NULL)
			console_printf("cvar: %s", cvar->name);

		/* next */
		cvar = cvar->next;
	}

	return 0;
}

int _cmd_help(int argc, char **argv)
{
	cmd_t *cmd;

	/* iterate over cmds */
	cmd = cmd_list;
	while (cmd)
	{
		/* print name */
		console_printf("%s: %s", cmd->name, cmd->help);

		/* next */
		cmd = cmd->next;
	}
}

int _cmd_map(int argc, char **argv)
{
	if (argc < 2)
	{
		console_printf("must specify map filename");
		return 1;
	}

	/* free old level */
	level_free(engine.level);

	/* load new level */
	if ((engine.level = level_load(argv[1])) == NULL)
	{
		console_printf("map %s not found", argv[1]);
		return 1;
	}

	console_printf("successfully loaded %s", argv[1]);

	/* restart raycaster */
	ray_quit();
	ray_init(engine.level);

	return 0;
}

cmd_t _cmdlib[] = {
	CMD("restart", "restart engine", _cmd_restart),
	CMD("quit", "return to dos", _cmd_quit),
	CMD("exit", "return to dos", _cmd_quit),
	CMD("typeof", "print type of cvar", _cmd_typeof),
	CMD("clear", "clear console screen", _cmd_clear),
	CMD("cls", "clear console screen", _cmd_clear),
	CMD("find", "find cvar or cmd by name", _cmd_find),
	CMD("help", "print help text", _cmd_help),
	CMD("map", "load map from file", _cmd_map)
};

void cmdlib_init(void)
{
	int i;
	for (i = 0; i < ASIZE(_cmdlib); i++)
		cmd_register(&_cmdlib[i]);
}

void cmdlib_quit(void)
{
	cmd_list = NULL;
}
