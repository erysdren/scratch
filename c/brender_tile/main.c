
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

#include "brprogram.h"

static struct {
    br_pixelmap *screen;
    br_pixelmap *colour;
    br_pixelmap *depth;
    br_actor *world;
    br_actor *camera;
    br_actor *cube;
    br_uint_64 ticks_then;
    br_uint_64 ticks_now;
} prog;

br_error prog_init(br_actor *world, br_actor *camera, br_pixelmap *screen, br_pixelmap *colour, br_pixelmap *depth)
{
    memset(&prog, 0, sizeof(prog));

    /* store a copy for ourselves */
    prog.world = world;
    prog.camera = camera;
    prog.screen = screen;
    prog.colour = colour;
    prog.depth = depth;

    BrMatrix34Translate(&prog.camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(0), BR_SCALAR(2));

    prog.cube = BrActorAdd(prog.world, BrActorAllocate(BR_ACTOR_MODEL, NULL));
    prog.cube->model = BrModelFind("cube.dat");
    prog.cube->material = BrMaterialFind("checkerboard.mat");

    prog.ticks_then = SDL_GetTicks64();

    return BRE_OK;
}

void prog_quit(void)
{

}

br_error prog_render(void)
{
    /* rotate cube */
    float dt;
    prog.ticks_now = SDL_GetTicks64();
    dt = (float)(prog.ticks_now - prog.ticks_then) / 1000.0f;
    prog.ticks_then = prog.ticks_now;
    BrMatrix34PostRotateY(&prog.cube->t.t.mat, BR_ANGLE_DEG(BR_SCALAR(50) * BR_SCALAR(dt)));

    /* do render */
    BrPixelmapFill(prog.colour, BR_COLOUR_RGB(66, 66, 66));
    BrPixelmapFill(prog.depth, 0xFFFFFFFF);
    BrZbSceneRender(prog.world, prog.camera, prog.colour, prog.depth);

    return BRE_OK;
}

br_error prog_event(SDL_Event *event)
{
    return BRE_OK;
}

int main(int argc, char **argv)
{
    /* set hooks */
    BrProgramInitHook(prog_init);
    BrProgramQuitHook(prog_quit);
    BrProgramRenderHook(prog_render);
    BrProgramEventHook(prog_event);

    /* initialize program */
    BrProgramInit("tile", 1280, 720);

    /* do main loop */
    BrProgramLoop();

    /* quit program */
    BrProgramQuit();

    return 0;
}
