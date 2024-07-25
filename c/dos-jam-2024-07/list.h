
#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_node {
	struct list_node *next;
	struct list_node **prev;
} list_node_t;

typedef struct list {
	list_node_t *head;
} list_t;

#define LIST_HEAD(l) ((void *)(((list_t *)(l))->head))
#define LIST_NEXT(n) ((void *)(((list_node_t *)(n))->next))

#define LIST_INSERTED(n) ((void *)(((list_node_t *)(n))->prev))

#define LIST_CHECK(l) LIST_HEAD(l)

#define LIST_FOR(l, p) for((p) = LIST_HEAD(l); (p); (p) = LIST_NEXT(p))

#define LIST_NEW(l) list_new((list_t *)(l))
#define LIST_ADDHEAD(l, n) list_add_head((list_t *)(l), (list_node_t *)(n))
#define LIST_REMHEAD(l) ((void *)list_rem_head((list_t *)(l)))
#define LIST_INSERT(l, n1, n2) list_insert((list_t *)(l), (list_node_t *)(n1), (list_node_t *)(n2))
#define LIST_REMOVE(n) ((void *)list_remove((list_node_t *)(n)))

void list_new(list_t *list);
void list_add_head(list_t *list, list_node_t *node);
list_node_t *list_rem_head(list_t *list);
void list_insert(list_t *list, list_node_t *here, list_node_t *node);
list_node_t *list_remove(list_node_t *node);

#endif /* _LIST_H_ */
