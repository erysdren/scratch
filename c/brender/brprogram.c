 
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

#include "brprogram.h"

/* local constants */
static uint8_t primitive_heap[1500 * 1024];
static br_order_table *order_table = NULL;
static br_pixelmap *screen = NULL;
static br_pixelmap *colour = NULL;
static br_pixelmap *depth = NULL;
static br_uint_64 then = 0;
static br_uint_64 now = 0;
const Uint8 *keys;

/* keyboard buffer */
#define KB_BUFSZ 64
#define KB_ADVANCE(x) ((x) = ((x) + 1) & (KB_BUFSZ - 1))
static int kb_buffer[KB_BUFSZ];
static int kb_buffer_ridx, kb_buffer_widx;

/* constants */
br_actor *world = NULL;
br_actor *camera = NULL;
float frametime = 0;

/* begin hook */
void _BrBeginHook(void)
{
	BrDevAddStatic(NULL, BrDrv1SDL2Begin, NULL);
	BrDevAddStatic(NULL, BrDrv1GLBegin, NULL);
}

/* end hook */
void _BrEndHook(void)
{

}

/* initialize program */
int BrProgram(const char *title, int w, int h)
{
	br_error r = BRE_OK;
	br_boolean running = BR_TRUE;
	SDL_Event event;

	/* x11 hint */
	SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

	/* begin brender */
	BrBegin();
	BrModelFindHook(BrModelFindFailedLoad);
	BrMapFindHook(BrMapFindFailedLoad);
	BrMaterialFindHook(BrMaterialFindFailedLoad);

	/* begin device */
	r = BrDevBeginVar(&screen, "SDL2",
					BRT_WIDTH_I32, w,
					BRT_HEIGHT_I32, h,
					BRT_PIXEL_TYPE_U8, BR_PMT_RGB_888,
					BRT_WINDOW_NAME_CSTR, title,
					BRT_HIDPI_B, BR_TRUE,
					BRT_RESIZABLE_B, BR_TRUE,
					BRT_OPENGL_B, BR_TRUE,
					BR_NULL_TOKEN);

	if (r != BRE_OK)
		return 1;

	/* fix up origin */
	screen->origin_x = (br_int_16)(screen->width / 2);
	screen->origin_y = (br_int_16)(screen->height / 2);

	/* setup and resize buffers */
	r = BrSDLUtilResizeBuffers(screen, &colour, &depth);
	if (r != BRE_OK)
		return 1;

	/* begin renderer */
	BrRendererBegin(colour, NULL, NULL, primitive_heap, sizeof(primitive_heap));

	/* setup world */
	world = BrActorAllocate(BR_ACTOR_NONE, NULL);
	order_table = BrZsOrderTableAllocate(1024, BR_ORDER_TABLE_LEAVE_BOUNDS | BR_ORDER_TABLE_BUCKET_SORT, BR_SORT_AVERAGE);
	BrZsActorOrderTableSet(world, order_table);

	/* add camera */
	camera = BrActorAdd(world, BrActorAllocate(BR_ACTOR_CAMERA, NULL));
	((br_camera *)camera->type_data)->field_of_view = BR_ANGLE_DEG(60);
	((br_camera *)camera->type_data)->hither_z = BR_SCALAR(0.1);
	((br_camera *)camera->type_data)->yon_z = BR_SCALAR(2048);
	((br_camera *)camera->type_data)->aspect = BR_DIV(BR_SCALAR(screen->width), BR_SCALAR(screen->height));

	/* setup order table */
	order_table->min_z = ((br_camera *)camera->type_data)->hither_z;
	order_table->max_z = ((br_camera *)camera->type_data)->yon_z;

	/* do user hook */
	r = BrProgramInit();
	if (r != BRE_OK)
		return 1;

	/* start counting time */
	then = SDL_GetTicks64();

	/* main loop */
	while (running == BR_TRUE && r == BRE_OK)
	{
		/* get key state */
		keys = SDL_GetKeyboardState(NULL);

		/* event poll loop */
		while (SDL_PollEvent(&event) > 0)
		{
			/* handle events */
			switch (event.type)
			{
				/* quit */
				case SDL_QUIT:
				{
					running = BR_FALSE;
					break;
				}

				/* window */
				case SDL_WINDOWEVENT:
				{
					r = BrPixelmapHandleWindowEvent(screen, &event.window);

					/* handle window events */
					switch (event.window.event)
					{
						/* window resize */
						case SDL_WINDOWEVENT_SIZE_CHANGED:
						{
							/* update origin */
							screen->origin_x = (br_int_16)(screen->width / 2);
							screen->origin_y = (br_int_16)(screen->height / 2);

							/* resize buffers */
							r = BrSDLUtilResizeBuffers(screen, &colour, &depth);

							/* update camera aspect ratio */
							((br_camera *)camera->type_data)->aspect = BR_DIV(BR_SCALAR(screen->width), BR_SCALAR(screen->height));

							break;
						}

						/* not handled */
						default:
						{
							break;
						}
					}

					break;
				}

				/* add to keyboard buffer */
				case SDL_KEYDOWN:
				{
					kb_buffer[kb_buffer_widx] = event.key.keysym.scancode;
					KB_ADVANCE(kb_buffer_widx);
					if (kb_buffer_widx == kb_buffer_ridx)
						KB_ADVANCE(kb_buffer_ridx);
					break;
				}

				/* not handled */
				default:
				{
					break;
				}
			}

			/* do user hook */
			r = BrProgramEvent(&event);
		}

		now = SDL_GetTicks64();
		frametime = (float)(now - then) / 1000.0f;
		then = now;

		/* do user hook */
		r = BrProgramRender(colour, depth);

		/* push to screen */
		BrPixelmapDoubleBuffer(screen, colour);
	}

	/* do user hook */
	BrProgramQuit();

	/* shutdown renderer */
	BrRendererEnd();

	/* free pixelmaps */
	if (depth) BrPixelmapFree(depth);
	if (colour) BrPixelmapFree(colour);
	if (screen) BrPixelmapFree(screen);
	if (world) BrActorFree(world);

	/* end BRender */
	BrEnd();

	return 0;
}

int BrProgramGetKey(int sc)
{
	int res;

	if (sc)
		return keys[sc] ? 1 : 0;

	if (kb_buffer_ridx == kb_buffer_widx)
		return -1;

	res = kb_buffer[kb_buffer_ridx];
	KB_ADVANCE(kb_buffer_ridx);

	return res;
}

void BrProgramClearKeyQueue(void)
{
	kb_buffer_ridx = kb_buffer_widx = 0;
}
