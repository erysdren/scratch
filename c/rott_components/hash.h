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
#ifndef _HASH_H_
#define _HASH_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/* hash type */
typedef uint32_t hash_t;

/* hashtable entry */
typedef struct hashtable_entry_t {
	char *key;
	void *value;
} hashtable_entry_t;

/* hashtable */
typedef struct hashtable_t {
	hashtable_entry_t *entries;
	size_t num_entries;
	size_t capacity;
} hashtable_t;

/* add value by key to hash table */
void hashtable_add(hashtable_t *table, char *key, void *value);

/* retrieve entry from hash table */
void *hashtable_retrieve(hashtable_t *table, char *key);

/* allocate hash table */
hashtable_t *hashtable_allocate(size_t max);

/* free hash table */
void hashtable_free(hashtable_t *table);

/* generate hash from key string */
hash_t hash_from_key(char *key);

#ifdef __cplusplus
}
#endif
#endif /* _HASH_H_ */
