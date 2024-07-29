
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "ui.h"
#include "util.h"
#include "vid.h"
#include "mem.h"

/* create new object with specified parent */
object_t *object_new(object_t *parent)
{
	object_t *o = memalloc(sizeof(object_t));

	/* initialize fields */
	LIST_NEW(&o->children);

	o->parent = parent;

	if (parent)
		LIST_ADDHEAD(&parent->children, o);

	return o;
}

/* free an object and all children */
void object_free(object_t *o)
{
	while (LIST_HEAD(&o->children))
		object_free(LIST_REMOVE(o->children));

	if (o->text)
		free(o->text);

	free(o);
}

/* immediately draw object and all children */
void object_draw(object_t *o)
{
	/* translate origin from parents */
	int bg = o->bg;
	int fg = o->fg;
	rect_t r = o->r;
	object_t *parent = o->parent;
	while (parent != NULL)
	{
		if (bg < 0) bg = parent->bg;
		if (fg < 0) fg = parent->fg;
		if (r.w == 0) r.w = parent->r.w;
		else if (r.w < 0) r.w += parent->r.w;
		if (r.h == 0) r.h = parent->r.h;
		else if (r.h < 0) r.h += parent->r.h;
		r.x += parent->r.x;
		r.y += parent->r.y;
		parent = parent->parent;
	}

	/* no color was specified */
	if (bg < 0 || fg < 0)
		return;
	/* no valid size was defined */
	if (r.w <= 0 || r.h <= 0)
		return;

	uint8_t color = vid_cell_color(bg, fg);
	uint16_t cell = vid_cell(' ', color);

	/* fill color of element */
	vid_cell_fill(r.x, r.y, r.w, r.h, cell);

	/* write text */
	if (o->text)
	{
		int x = r.x;
		int y = r.y;
		for (int i = 0; i < strlen(o->text); i++)
		{
			/* handle control characters */
			if (o->text[i] == '\n')
			{
				y += 1;
				continue;
			}
			else if (o->text[i] == '\r')
			{
				x = r.x;
				continue;
			}
			else if (o->text[i] == '\t')
			{
				x += 4;
				continue;
			}

			/* automatically wrap text */
			if (x >= r.x + r.w)
			{
				x = r.x;
				y += 1;
			}

			/* gone out of range */
			if (y >= r.y + r.h)
			{
				break;
			}

			cell = vid_cell(o->text[i], color);
			vid_cell_put(x, y, cell);

			x += 1;
		}
	}

	/* draw children */
	object_t *child;
	LIST_FOR(&o->children, child)
		object_draw(child);
}
