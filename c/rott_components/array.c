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

#include "array.h"

/* get array index from string value */
/* returns -1 on error */
int string_array_get_index_from_value(string_array_t *array, const char *value)
{
	int i;

	/* sanity checks */
	if (array == NULL || value == NULL)
		return -1;

	/* slow linear search */
	for (i = 0; i < array->num_entries; i++)
	{
		if (array->entries[i] != NULL)
		{
			if (strcmp(array->entries[i], value) == 0)
				return i;
		}
	}

	/* fail */
	return -1;
}

/* get string value from array index */
/* returns NULL on error */
const char *string_array_get_value_from_index(string_array_t *array, int index)
{
	/* sanity checks */
	if (array == NULL)
		return NULL;
	if (index < 0 || index >= array->num_entries)
		return NULL;

	/* return value at index */
	return array->entries[index];
}
