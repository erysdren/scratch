
typedef struct list_node {
	struct list_node *next;
	struct list_node *prev;
} list_node_t;

typedef struct list {
	list_node_t *head;
	list_node_t *tail;
} list_t;

#define LIST_TEMPLATE(T) \
	T *next; \
	T *prev; \
	struct { T *head; T *tail; } children; \
	T *parent;

#define LIST_HEAD(l) ((void *)(((list_t *)(l))->head))
#define LIST_TAIL(l) ((void *)(((list_t *)(l))->tail))

#define LIST_NEXT(n) ((void *)(((list_node_t *)(n))->next))
#define LIST_PREV(n) ((void *)(((list_node_t *)(n))->prev))

#define LIST_WALK_FORWARDS(l, p) \
	for ((p) = LIST_HEAD(l); LIST_NEXT(p); (p) = LIST_NEXT(p))

#define LIST_WALK_BACKWARDS(l, p) \
	for ((p) = LIST_TAIL(l); LIST_PREV(p); (p) = LIST_PREV(p))

typedef struct example {
	LIST_TEMPLATE(struct example);
} example_t;

int main(int argc, char **argv)
{
	return 0;
}
