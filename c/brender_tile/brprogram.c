 
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

#include "brprogram.h"

/* local constants */
static uint8_t primitive_heap[1500 * 1024];
static br_pixelmap *screen = NULL;
static br_pixelmap *colour = NULL;
static br_pixelmap *depth = NULL;
static br_order_table *order_table = NULL;
static br_actor *world = NULL;
static br_actor *camera = NULL;

static br_program_init_cbfn *init_cbfn = NULL;
static br_program_quit_cbfn *quit_cbfn = NULL;
static br_program_render_cbfn *render_cbfn = NULL;
static br_program_event_cbfn *event_cbfn = NULL;

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

/* create scene */
static br_error BrProgramCreateScene(void)
{
    br_error r = BRE_OK;
    br_camera *camdata;

    world = BrActorAllocate(BR_ACTOR_NONE, NULL);
    order_table = BrZsOrderTableAllocate(1024, BR_ORDER_TABLE_LEAVE_BOUNDS | BR_ORDER_TABLE_BUCKET_SORT, BR_SORT_AVERAGE);
    BrZsActorOrderTableSet(world, order_table);

    /* add camera */
    camera = BrActorAdd(world, BrActorAllocate(BR_ACTOR_CAMERA, NULL));
    camdata = camera->type_data;
    camdata->field_of_view = BR_ANGLE_DEG(60);
    camdata->hither_z = BR_SCALAR(0.1);
    camdata->aspect = BR_DIV(BR_SCALAR(screen->width), BR_SCALAR(screen->height));

    order_table->min_z = camdata->hither_z;
    order_table->max_z = camdata->yon_z;

    return r;
}

void BrProgramInitHook(br_program_init_cbfn *hook)
{
    if (hook) init_cbfn = hook;
}

void BrProgramQuitHook(br_program_quit_cbfn *hook)
{
    if (hook) quit_cbfn = hook;
}

void BrProgramRenderHook(br_program_render_cbfn *hook)
{
    if (hook) render_cbfn = hook;
}

void BrProgramEventHook(br_program_event_cbfn *hook)
{
    if (hook) event_cbfn = hook;
}

/* initialize program */
br_error BrProgramInit(const char *title, int w, int h)
{
    br_error r = BRE_OK;

    /* x11 hint */
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    /* begin brender */
    BrBegin();
    BrModelFindHook(BrModelFindFailedLoad);
    BrMapFindHook(BrMapFindFailedLoad);
    BrMaterialFindHook(BrMaterialFindFailedLoad);

    /* begin device */
    r = BrDevBeginVar(&screen, "SDL2",
                      BRT_WIDTH_I32,        w,
                      BRT_HEIGHT_I32,       h,
                      BRT_PIXEL_TYPE_U8,    BR_PMT_RGB_888,
                      BRT_WINDOW_NAME_CSTR, title,
                      BRT_HIDPI_B,          BR_TRUE,
                      BRT_RESIZABLE_B,      BR_TRUE,
                      BRT_OPENGL_B,         BR_TRUE,
                      BR_NULL_TOKEN);

    if (r != BRE_OK) return r;

    /* fix up origin */
    screen->origin_x = (br_int_16)(screen->width / 2);
    screen->origin_y = (br_int_16)(screen->height / 2);

    /* setup and resize buffers */
    r = BrSDLUtilResizeBuffers(screen, &colour, &depth);
    if (r != BRE_OK) return r;

    /* begin renderer */
    BrRendererBegin(colour, NULL, NULL, primitive_heap, sizeof(primitive_heap));

    /* create scene */
    BrProgramCreateScene();

    /* do user hook */
    if (init_cbfn)
        r = init_cbfn(world, camera, screen, colour, depth);

    return r;
}

/* do main loop */
br_error BrProgramLoop(void)
{
    br_error r = BRE_OK;
    br_boolean running = BR_TRUE;
    SDL_Event event;

    /* main loop */
    while (running == BR_TRUE && r == BRE_OK)
    {
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
                            ((br_camera *)camera->type_data)->aspect = BR_DIV(BR_SCALAR(screen->width),
                                                                              BR_SCALAR(screen->height));
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

                /* not handled */
                default:
                {
                    break;
                }
            }

            /* do user hook */
            if (event_cbfn)
                r = event_cbfn(&event);
        }

        /* begin render */
        BrRendererFrameBegin();

        /* do user hook */
        if (render_cbfn)
            r = render_cbfn();

        /* end render */
        BrRendererFrameEnd();

        /* push to screen  */
        BrPixelmapDoubleBuffer(screen, colour);
    }

    return r;
}

/* shutdown program */
void BrProgramQuit(void)
{
    /* do user hook */
    if (quit_cbfn)
        quit_cbfn();

    /* shutdown renderer */
    BrRendererEnd();

    /* free pixelmaps */
    if (depth) BrPixelmapFree(depth);
    if (colour) BrPixelmapFree(colour);
    if (screen) BrPixelmapFree(screen);

    /* end BRender */
    BrEnd();
}

