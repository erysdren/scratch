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

#include "cvar.h"

/* global cvar chain */
cvar_t *cvar_list = NULL;

/* retrieve cvar from chain */
cvar_t *cvar_retrieve(const char *name)
{
	cvar_t *cvar = cvar_list;

	while (cvar != NULL)
	{
		if (strcasecmp(name, cvar->name) == 0)
			return cvar;

		/* move down chain */
		cvar = cvar->next;
	}

	return NULL;
}

/* add cvar to chain */
void cvar_register(cvar_t *cvar)
{
	/* don't add it if there's already one in the chain with the same name */
	if (cvar_retrieve(cvar->name) != NULL)
		return;

	if (cvar_list == NULL)
	{
		/* start chain */
		cvar_list = cvar;
	}
	else
	{
		/* add to chain */
		cvar->next = cvar_list;
		cvar_list = cvar;
	}
}

bool cvar_get_bool(const char *name)
{
	cvar_t *cvar;

	if ((cvar = cvar_retrieve(name)) == NULL)
		return false;
	if (cvar->type != CVAR_TYPE_BOOL)
		return false;

	return cvar->value.b;
}

int cvar_get_int(const char *name)
{
	cvar_t *cvar;

	if ((cvar = cvar_retrieve(name)) == NULL)
		return 0;
	if (cvar->type != CVAR_TYPE_INT)
		return 0;

	return cvar->value.i;
}

unsigned int cvar_get_uint(const char *name)
{
	cvar_t *cvar;

	if ((cvar = cvar_retrieve(name)) == NULL)
		return 0;
	if (cvar->type != CVAR_TYPE_UINT)
		return 0;

	return cvar->value.u;
}

fix32_t cvar_get_fixed(const char *name)
{
	cvar_t *cvar;

	if ((cvar = cvar_retrieve(name)) == NULL)
		return 0;
	if (cvar->type != CVAR_TYPE_FIXED)
		return 0;

	return cvar->value.x;
}

float cvar_get_float(const char *name)
{
	cvar_t *cvar;

	if ((cvar = cvar_retrieve(name)) == NULL)
		return 0;
	if (cvar->type != CVAR_TYPE_FLOAT)
		return 0;

	return cvar->value.f;
}

const char *cvar_get_string(const char *name)
{
	cvar_t *cvar;

	if ((cvar = cvar_retrieve(name)) == NULL)
		return NULL;
	if (cvar->type != CVAR_TYPE_STRING)
		return NULL;

	return cvar->value.s;
}
