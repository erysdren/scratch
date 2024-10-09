
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static const uintptr_t resource_magic = 0xBEEFCAFE;

typedef struct resource {
	/* linked list of sibling resources */
	struct resource *next;
	struct resource *prev;
	/* pointer to first in list of child resources */
	struct resource *children;
	/* pointer to parent resource */
	struct resource *parent;
	/* pad struct to 8 pointers wide */
	uintptr_t _pad;
	/* user-requested size */
	uintptr_t size;
	/* user pointer */
	uintptr_t user;
	/* magic identifier */
	uintptr_t magic;
} resource_t;

resource_t *user_to_resource(void *user)
{
	resource_t *res = (uint8_t *)user - sizeof(resource_t);

	if (res->magic != resource_magic)
		return NULL;
	if (res->user != (uintptr_t)user)
		return NULL;

	return res;
}

void *resource_allocate_aligned(void *parent, size_t alignment, size_t size)
{
	resource_t *res = NULL;

	if (size == 0)
		return NULL;

	/* allocate structure and user data */
#if _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
	if (posix_memalign(&res, alignment, sizeof(resource_t) + size) != 0)
		return NULL;
#else

#endif

	/* setup structure */
	res->size = size;
	res->user = (uintptr_t)((uint8_t *)res + sizeof(resource_t));
	res->magic = resource_magic;
	res->next = NULL;
	res->prev = NULL;
	res->children = NULL;

	/* add to parent */
	if (parent)
	{

	}

	return (void *)(res->user);
}

void *resource_allocate(void *parent, size_t size)
{
	/* allocate buffer and leader */
	resource_t *res = SDL_aligned_alloc(16, sizeof(resource_t) + size);
	SDL_assert(res != NULL);

	/* setup fields */
	res->size = size;
	res->user = (uint8_t *)res + sizeof(resource_t);
	res->magic = resource_magic;

	/* create new children list */
	LIST_NEW(&res->children);

	/* add to parent */
	if (parent)
	{
		resource_t *p = user_to_resource(parent);
		LIST_ADD_HEAD(&p->children, res);
	}

	return res->user;
}
