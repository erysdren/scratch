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

#include "tileset.h"

/* get tileset index from tile name */
/* returns -1 on error */
int tileset_get_index_from_name(tileset_t *tileset, const char *name)
{
	int i;

	/* sanity checks */
	if (tileset == NULL || name == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < tileset->num_entries; i++)
	{
		if (tileset->entries[i].name != NULL)
		{
			if (strcmp(tileset->entries[i].name, name) == 0)
				return tileset->entries[i].index;
		}
	}

	/* fail */
	return -1;
}

/* get tile name from tileset index */
/* returns NULL on error */
const char *tileset_get_name_from_index(tileset_t *tileset, int index)
{
	int i;

	/* sanity checks */
	if (tileset == NULL || index < 0)
		return NULL;

	/* slow linear search */
	for (i = 0; i < tileset->num_entries; i++)
	{
		if (index == tileset->entries[i].index)
			return tileset->entries[i].name;
	}

	/* fail */
	return NULL;
}
