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
#ifndef _CVAR_H_
#define _CVAR_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "math.h"

/* cvar type enum */
enum
{
	CVAR_TYPE_BOOL,
	CVAR_TYPE_INT,
	CVAR_TYPE_UINT,
	CVAR_TYPE_FIXED,
	CVAR_TYPE_FLOAT,
	CVAR_TYPE_STRING
};

/* cvar structure */
typedef struct cvar_t
{
	/* name for searching */
	const char *name;

	/* value type identifier */
	int type;

	/* value union */
	union {
		bool b;
		int i;
		unsigned int u;
		fix32_t x;
		float f;
		const char *s;
	} value;

	/* next in chain */
	struct cvar_t *next;
} cvar_t;

/* cvar creation macros */
#define CVAR_BOOL(n, v) (cvar_t){ .name = n, .type = CVAR_TYPE_BOOL, .value.b = v, .next = NULL }
#define CVAR_INT(n, v) (cvar_t){ .name = n, .type = CVAR_TYPE_INT, .value.i = v, .next = NULL }
#define CVAR_UINT(n, v) (cvar_t){ .name = n, .type = CVAR_TYPE_UINT, .value.u = v, .next = NULL }
#define CVAR_FIXED(n, v) (cvar_t){ .name = n, .type = CVAR_TYPE_FIXED, .value.x = v, .next = NULL }
#define CVAR_FLOAT(n, v) (cvar_t){ .name = n, .type = CVAR_TYPE_FLOAT, .value.f = v, .next = NULL }
#define CVAR_STRING(n, v) (cvar_t){ .name = n, .type = CVAR_TYPE_STRING, .value.s = v, .next = NULL }

extern cvar_t *cvar_list;

/* retrieve cvar from chain */
cvar_t *cvar_retrieve(const char *name);

/* add cvar to chain */
void cvar_register(cvar_t *cvar);

/* retrieve values from cvar */
bool cvar_get_bool(const char *name);
int cvar_get_int(const char *name);
unsigned int cvar_get_uint(const char *name);
fix32_t cvar_get_fixed(const char *name);
float cvar_get_float(const char *name);
const char *cvar_get_string(const char *name);

#ifdef __cplusplus
}
#endif
#endif /* _CVAR_H_ */
