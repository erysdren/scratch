
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "rect.h"
#include "util.h"

/* returns 1 if r0 fully contains r1 */
int rect_contains(rect_t *r0, rect_t *r1)
{
	return
	r1->x >= r0->x &&
	r1->y >= r0->y &&
	r1->x + r1->w <= r0->x + r0->w &&
	r1->y + r1->h <= r0->y + r0->h;
}

/* returns 1 if r0 and r1 overlap in any way */
int rect_intersects(rect_t *r0, rect_t *r1)
{
	return
	r0->x < r1->x + r1->w &&
	r0->x + r0->w > r1->x &&
	r0->y < r1->y + r1->h &&
	r0->y + r0->h > r1->y;
}

/* merge two rects by their largest extents */
void rect_merge(rect_t *out, rect_t *r0, rect_t *r1)
{
	out->x = imin(r0->x, r1->x);
	out->y = imin(r0->y, r1->y);

	out->w = imax(r0->x + r0->w, r1->x + r1->w) - out->x;
	out->h = imax(r0->y + r0->h, r1->y + r1->h) - out->y;
}

/* convert a rectangle to two points */
void rect_to_points(rect_t *r, point_t *p0, point_t *p1)
{
	*p0 = (point_t){r->x, r->y};
	*p1 = (point_t){r->x + r->w, r->y + r->h};
}

/* convert two points to a rect */
void points_to_rect(rect_t *r, point_t *p0, point_t *p1)
{
	r->x = imin(p0->x, p1->x);
	r->y = imin(p0->y, p1->y);
	r->w = imax(p0->x, p1->x) - r->x;
	r->h = imax(p0->y, p1->y) - r->y;
}
