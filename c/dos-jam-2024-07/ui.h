
#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

#include "rect.h"
#include "list.h"

#define MAX_ELEMENTS (2048)
#define MAX_FRAMES (1024)

/*
 * ui
 */

typedef struct element {
	char *text;
	rect_t r;
	int z;
	int dirty;
	uint8_t bg;
	uint8_t fg;
} element_t;

typedef struct drawable {
	char *text;
	rect_t r;
	uint8_t bg;
	uint8_t fg;
} drawable_t;

typedef struct object {
	/* object_t can be used as list_node_t */
	struct object *next;
	struct object **prev;
	/* object_t.children can be used as list_t */
	struct object *children;
	struct object *parent;
	/* text buffer, wrapped to size. control codes accepted. */
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

/* create new object with specified parent and type */
object_t *object_new(object_t *parent);

/* free an object and all children */
void object_free(object_t *object);

/* immediately draw object and all children */
void object_draw(object_t *o);

/* mark an area of the screen as dirty */
void ui_mark(rect_t *r);

/* push a new element to the stack */
element_t *ui_push(const char *text, rect_t *r, int z, uint8_t bg, uint8_t fg);

/* sort all elements in the stack by their z value */
void ui_sort(void);

/* clear elements structure and free any allocated memory */
void ui_reset(void);

/* get the next ui element in the stack */
element_t *ui_next(void);

/* probe at x,y for element */
element_t *ui_probe(int x, int y);

#if 0

/* shrink drawable size to fit text contents */
void ui_drawable_shrinkwrap(ui_drawable_t *e);

/* immediately draw drawable */
void ui_drawable_draw(ui_drawable_t *e);

#endif

#endif /* _UI_H_ */
