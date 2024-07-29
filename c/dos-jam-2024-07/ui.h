
#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

#include "rect.h"
#include "list.h"

typedef struct object {
	/* object_t can be used as list_node_t */
	struct object *next;
	struct object **prev;
	/* object_t.children can be used as list_t */
	struct object *children;
	struct object *parent;
	/* text buffer, wrapped and clipped to size. control codes accepted. */
	char *text;
	/* x&y are relative to parent.
	 * if w or h == 0, inherit from parent.
	 * if w or h < 0, subtract from parent size.
	 */
	rect_t r;
	/* valid color range is 0-15, or < 0 to inherit from parent */
	int bg;
	int fg;
} object_t;

/* create new object with specified parent */
object_t *object_new(object_t *parent);

/* free an object and all children */
void object_free(object_t *object);

/* immediately draw object and all children */
void object_draw(object_t *o);

#endif /* _UI_H_ */
