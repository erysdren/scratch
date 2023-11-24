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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash.h"

#define FNV_OFFSET 2166136261UL
#define FNV_PRIME 16777619UL

void hashtable_add(hashtable_t *table, char *key, void *value)
{
	hash_t hash;
	size_t index;

	/* get hash and index */
	hash = hash_from_key(key);
	index = (hash & (hash_t)(table->capacity - 1));

	/* check if it exists */
	if (table->entries[index].key == NULL)
	{
		/* it doesn't exist, so add it */
		table->entries[index].key = strdup(key);
		table->entries[index].value = value;
		table->num_entries++;
	}
	else if (strcmp(key, table->entries[index].key) == 0)
	{
		/* it's already in the table */
		fprintf(stderr, "\"%s\" was already in this table!\n", key);
	}
	else
	{
		/* other error */
		fprintf(stderr, "failed to add \"%s\" to this table!\n", key);
	}
}

void *hashtable_retrieve(hashtable_t *table, char *key)
{
	hash_t hash;
	size_t index;

	/* get hash and index */
	hash = hash_from_key(key);
	index = (hash & (hash_t)(table->capacity - 1));

	/* loop until we find it */
	while (table->entries[index].key != NULL)
	{
		/* found key, return the value */
		if (strcmp(key, table->entries[index].key) == 0)
			return table->entries[index].value;

		/* not found, do some linear probing */
		/* and wrap around at the end of the array */
		index++;
		if (index >= table->capacity)
			index = 0;
	}

	return NULL;
}

hashtable_t *hashtable_allocate(size_t max)
{
	hashtable_t *table;

	table = calloc(1, sizeof(hashtable_t));
	table->entries = calloc(max, sizeof(hashtable_entry_t));
	table->num_entries = 0;
	table->capacity = max;

	return table;
}

void hashtable_free(hashtable_t *table)
{
	int i;

	if (table)
	{
		for (i = 0; i < table->capacity; i++)
		{
			if (table->entries[i].key != NULL)
				free(table->entries[i].key);
		}
	}
}

hash_t hash_from_key(char *key)
{
	hash_t hash = FNV_OFFSET;

	for (char *p = key; *p; p++)
	{
		hash ^= (hash_t)(uint8_t)(*p);
		hash *= FNV_PRIME;
	}

	return hash;
}
