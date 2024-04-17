/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

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

#include <stdio.h>
#include <string.h>

#include "steampath.h"

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define PLATFORM_WINDOWS (1)
#endif

#if PLATFORM_WINDOWS

/* retrieve full path of steam directory */
int steam_get_path(char *out, size_t outsize)
{
	return 0;
}

#else

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/* retrieve full path of steam directory */
int steam_get_path(char *out, size_t outsize)
{
	const char steam_dir[] = ".steam/steam";
	const char *home_dir = NULL;

	/* get home dir */
	home_dir = getenv("XDG_CONFIG_HOME");
	if (home_dir == NULL)
		home_dir = getenv("HOME");
	if (home_dir == NULL)
		homedir = getpwuid(getuid())->pw_dir;
	if (home_dir == NULL)
		return 0;

	/* write path */
	if ((size_t)snprintf(out, outsize, "%s/%s", home_dir, steam_dir) >= outsize)
		return 0;

	return 1;
}

#endif
