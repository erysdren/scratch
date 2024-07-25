
#include <stddef.h>
#include "list.h"

void list_new(list_t *list)
{
	list->head = NULL;
}

void list_add_head(list_t *list, list_node_t *node)
{
	node->next = list->head;
	node->prev = &list->head;

	if (node->next)
		node->next->prev = &node->next;

	list->head = node;
}

list_node_t *list_rem_head(list_t *list)
{
	list_node_t *node = list->head;

	if (node)
		list_remove(node);

	return node;
}

void list_insert(list_t *list, list_node_t *here, list_node_t *node)
{
	node->next = here->next;
	node->prev = &here->next;

	if (node->next)
		node->next->prev = &node->next;

	here->next = node;
}

list_node_t *list_remove(list_node_t *node)
{
	*(node->prev) = node->next;

	if (node->next)
		node->next->prev = node->prev;

	node->prev = NULL;
	node->next = NULL;

	return node;
}
