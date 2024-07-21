
#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

/* NOTE: all coordinate and size values are in character cells, NOT pixels */
/* NOTE: coordinates grow from the top left of the screen, starting at 0,0 */

#define MAX_ELEMENTS (256)
#define WIDTH (80)
#define HEIGHT (25)

/*
 * utils
 */

__attribute__((const)) int imin(int x, int y);
__attribute__((const)) int imax(int x, int y);
__attribute__((const)) int iclamp(int i, int min, int max);

/*
 * rects
 */

typedef struct point {
	int x, y;
} point_t;

#define print_point(p) printf(#p " x=%04d y=%04d\n", (p)->x, (p)->y)

typedef struct rect {
	int x, y, w, h;
} rect_t;

#define print_rect(r) printf(#r " x=%04d y=%04d w=%04d h=%04d\n", (r)->x, (r)->y, (r)->w, (r)->h)

/* returns 1 if r0 fully contains r1 */
int rect_contains(rect_t *r0, rect_t *r1);

/* returns 1 if r0 and r1 intersect in any way */
int rect_intersects(rect_t *r0, rect_t *r1);

/* merge r0 and r1 into out by their largest extents */
void rect_merge(rect_t *out, rect_t *r0, rect_t *r1);

/* convert a rectangle to two points */
void rect_to_points(rect_t *r, point_t *p0, point_t *p1);

/* convert two points to a rect */
void points_to_rect(rect_t *r, point_t *p0, point_t *p1);

/*
 * ui
 */

typedef struct element {
	char *label;
	rect_t r;
	int z;
	int dirty;
	uint32_t fg;
	uint32_t bg;
} element_t;

/* mark an area of the screen as dirty */
void ui_mark(rect_t *r);

/* push a new element to the stack */
element_t *ui_push(const char *label, rect_t *r, int z, uint32_t bg, uint32_t fg);

/* sort all elements in the stack by their z value */
void ui_sort(void);

/* clear elements structure and free any allocated memory */
void ui_reset(void);

/* get the next ui element in the stack */
element_t *ui_next(void);

#endif /* _UI_H_ */
