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

#include "vte.h"

/* https://github.com/BlazingRenderer/BRender/blob/master/core/fw/resource.c */

static const uintptr_t resource_magic = 0xBEEFCAFE;

typedef struct resource {
	list_node_t node;
	list_t children;
	size_t size;
	void *user;
	uintptr_t magic;
} __attribute__((packed, aligned(16))) resource_t;

static resource_t *_user_to_resource(void *user)
{
	resource_t *res = (resource_t *)((Uint8 *)user - sizeof(resource_t));

	SDL_assert(res->magic == resource_magic);
	SDL_assert(res->user == user);

	return res;
}

void *Res_Alloc(void *parent, size_t size)
{
	/* allocate buffer and leader */
	resource_t *res = SDL_aligned_alloc(16, sizeof(resource_t) + size);
	SDL_assert(res != NULL);

	/* setup fields */
	res->size = size;
	res->user = (Uint8 *)res + sizeof(resource_t);
	res->magic = resource_magic;

	/* create new children list */
	LIST_NEW(&res->children);

	/* add to parent */
	if (parent)
	{
		resource_t *p = _user_to_resource(parent);
		LIST_ADD_HEAD(&p->children, res);
	}

	return res->user;
}

static void _res_free(resource_t *res)
{
	/* free any children */
	while (LIST_HEAD(&res->children))
		_res_free((resource_t *)LIST_REMOVE(LIST_HEAD(&res->children)));

	/* remove from any parent list */
	if (LIST_INSERTED(res))
		LIST_REMOVE(res);

	/* untag memory */
	res->magic = 0;
	res->user = NULL;

	/* finally free memory */
	SDL_aligned_free(res);
}

void Res_Free(void *user)
{
	resource_t *res = user_to_resource(user);

	_res_free(res);
}
