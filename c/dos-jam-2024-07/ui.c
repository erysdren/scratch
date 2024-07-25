
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "ui.h"
#include "util.h"
#include "vid.h"

static size_t num_elements = 0;
static element_t elements[MAX_ELEMENTS];
static element_t *sorted_elements[MAX_ELEMENTS];

/* create new object with specified parent */
object_t *object_new(object_t *parent)
{
	object_t *o = calloc(1, sizeof(object_t));

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
	uint8_t color = vid_cell_color(o->bg, o->fg);
	uint16_t cell = vid_cell(' ', color);

	/* fill color of element */
	vid_cell_fill(o->r.x, o->r.y, o->r.w, o->r.h, cell);

	/* write text */
	if (o->text)
	{
		int x = o->r.x;
		int y = o->r.y;
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
				x = o->r.x;
				continue;
			}
			else if (o->text[i] == '\t')
			{
				x += 4;
				continue;
			}

			/* automatically wrap text */
			if (x >= o->r.x + o->r.w)
			{
				x = o->r.x;
				y += 1;
			}

			/* gone out of range */
			if (y >= o->r.y + o->r.h)
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

void ui_mark(rect_t *r)
{
	for (int i = 0; i < num_elements; i++)
	{
		if (rect_intersects(r, &elements[i].r))
		{
			elements[i].dirty = 1;
		}
	}
}

element_t *ui_push(const char *text, rect_t *r, int z, uint8_t bg, uint8_t fg)
{
	if (num_elements >= MAX_ELEMENTS)
		return NULL;

	elements[num_elements] = (element_t){
		text ? strdup(text) : NULL, *r, z, 0, bg, fg
	};

	return &elements[num_elements++];
}

static int ui_compare(const void *a, const void *b)
{
	return (*(element_t **)a)->z - (*(element_t **)b)->z;
}

void ui_sort(void)
{
	for (int i = 0; i < num_elements; i++)
		sorted_elements[i] = &elements[i];

	qsort(sorted_elements, num_elements, sizeof(element_t *), ui_compare);
}

void ui_reset(void)
{
	for (int i = 0; i < num_elements; i++)
	{
		if (elements[i].text)
			free(elements[i].text);
	}

	num_elements = 0;
	memset(elements, 0, sizeof(elements));
	memset(sorted_elements, 0, sizeof(sorted_elements));
}

element_t *ui_next(void)
{
	static size_t n = 0;

	if (n >= num_elements)
	{
		n = 0;
		return NULL;
	}

	return sorted_elements[n++];
}

element_t *ui_probe(int x, int y)
{
	rect_t probe = {x, y, 1, 1};

	for (int i = num_elements; i >= 0; --i)
	{
		if (rect_intersects(&sorted_elements[i]->r, &probe))
		{
			return sorted_elements[i];
		}
	}

	return NULL;
}

#if 0

/* shrink drawable size to fit text contents */
void ui_drawable_shrinkwrap(ui_drawable_t *d)
{
	rect_t new = {d->r.x, d->r.y, 0, 1};

	for (int i = 0; i < strlen(d->text); i++)
	{
		if (d->text[i] == '\n')
		{
			new.h += 1;
		}
		else if (d->text[i] == '\t')
		{
			new.w += 4;
		}
		else
		{
			new.w += 1;
		}
	}

	d->r = new;
}

/* immediately draw drawable */
void ui_drawable_draw(ui_drawable_t *d)
{
	int x, y;
	uint8_t color = vid_cell_color(d->bg, d->fg);
	uint16_t cell = vid_cell(' ', color);

	/* fill color of element */
	vid_cell_fill(d->r.x, d->r.y, d->r.w, d->r.h, cell);

	/* write text */
	if (d->text)
	{
		x = d->r.x;
		y = d->r.y;
		for (int i = 0; i < strlen(d->text); i++)
		{
			/* handle control characters */
			if (d->text[i] == '\n')
			{
				y += 1;
				continue;
			}
			else if (d->text[i] == '\r')
			{
				x = d->r.x;
				continue;
			}
			else if (d->text[i] == '\t')
			{
				x += 4;
				continue;
			}

			/* automatically wrap text */
			if (x >= d->r.x + d->r.w)
			{
				x = d->r.x;
				y += 1;
			}

			/* gone out of range */
			if (y >= d->r.y + d->r.h)
			{
				break;
			}

			cell = vid_cell(d->text[i], color);
			vid_cell_put(x, y, cell);

			x += 1;
		}
	}
}

#endif
