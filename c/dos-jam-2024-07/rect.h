
#ifndef _RECT_H_
#define _RECT_H_

typedef struct point {
	int x, y;
} point_t;

#define print_point(p) printf(#p " x=%04d y=%04d\n", (p)->x, (p)->y)

typedef struct rect {
	int x, y, w, h;
} rect_t;

#define print_rect(r) printf(#r " x=%04d y=%04d w=%04d h=%04d\n", (r)->x, (r)->y, (r)->w, (r)->h)

#define RECT(x, y, w, h) (rect_t){x, y, w, h}

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

#endif /* _RECT_H_ */
