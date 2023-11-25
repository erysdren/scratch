
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

#include "brprogram.h"

/* map */
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define CAMERA_START_X 12
#define CAMERA_START_Y 12
static br_uint_8 map[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static struct {
	br_pixelmap *screen;
	br_pixelmap *colour;
	br_pixelmap *depth;
	br_actor *world;
	br_actor *camera;
	br_actor *camera_bbox;
	br_actor *level;
	br_uint_64 ticks_then;
	br_uint_64 ticks_now;
	const Uint8 *keys;
} prog;

br_bounds get_absolute_bounds(br_actor *a)
{
	br_bounds r = a->model->bounds;

	r.min.v[0] += a->t.t.translate.t.v[0];
	r.min.v[1] += a->t.t.translate.t.v[1];
	r.min.v[2] += a->t.t.translate.t.v[2];

	r.max.v[0] += a->t.t.translate.t.v[0];
	r.max.v[1] += a->t.t.translate.t.v[1];
	r.max.v[2] += a->t.t.translate.t.v[2];

	return r;
}

/* swept aabb */
br_scalar aabb_swept(br_actor *a, br_actor *b, br_vector3 *normal)
{
	return BR_SCALAR(0);
}

/* aabb */
br_boolean actor_overlapping(br_actor *a, br_actor *b)
{
	br_bounds a_abs = get_absolute_bounds(a);
	br_bounds b_abs = get_absolute_bounds(b);

	/* return true if colliding */
	return !(a_abs.max.v[0] < b_abs.min.v[0] || a_abs.min.v[0] > b_abs.max.v[0] ||
			a_abs.max.v[1] < b_abs.min.v[1] || a_abs.min.v[1] > b_abs.max.v[1] ||
			a_abs.max.v[2] < b_abs.min.v[2] || a_abs.min.v[2] > b_abs.max.v[2]);
}

br_error prog_init(br_actor *world, br_actor *camera, br_pixelmap *screen, br_pixelmap *colour, br_pixelmap *depth)
{
	memset(&prog, 0, sizeof(prog));

	/* store a copy for ourselves */
	prog.world = world;
	prog.camera = camera;
	prog.screen = screen;
	prog.colour = colour;
	prog.depth = depth;

	/* move camera */
	BrMatrix34Translate(&prog.camera->t.t.mat, BR_SCALAR(CAMERA_START_X), BR_SCALAR(0), BR_SCALAR(CAMERA_START_Y));

	prog.camera_bbox = BrActorAdd(prog.world, BrActorAllocate(BR_ACTOR_MODEL, NULL));
	prog.camera_bbox->model = BrModelFind("cube.dat");
	prog.camera_bbox->material = BrMaterialFind("checkerboard.mat");

	/* start counting time */
	prog.ticks_then = SDL_GetTicks64();

	/* create level scene */
	prog.level = BrActorAdd(prog.world, BrActorAllocate(BR_ACTOR_NONE, NULL));
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] > 0)
			{
				br_actor *cube = BrActorAdd(prog.level, BrActorAllocate(BR_ACTOR_MODEL, NULL));

				cube->model = BrModelFind("cube.dat");
				cube->material = BrMaterialFind("checkerboard.mat");

				BrMatrix34Translate(&cube->t.t.mat, BR_SCALAR(x), BR_SCALAR(0), BR_SCALAR(y));
			}
		}
	}

	return BRE_OK;
}

void prog_quit(void)
{

}

br_error prog_render(void)
{
	/* get deltatime */
	float dt;
	prog.ticks_now = SDL_GetTicks64();
	dt = (float)(prog.ticks_now - prog.ticks_then) / 1000.0f;
	prog.ticks_then = prog.ticks_now;

	/* get key state */
	prog.keys = SDL_GetKeyboardState(NULL);

	/* turning left and right */
	if (prog.keys[SDL_SCANCODE_LEFT])
		BrMatrix34PreRotateY(&prog.camera->t.t.mat, BR_ANGLE_DEG(BR_SCALAR(80) * BR_SCALAR(dt)));
	if (prog.keys[SDL_SCANCODE_RIGHT])
		BrMatrix34PreRotateY(&prog.camera->t.t.mat, BR_ANGLE_DEG(BR_SCALAR(-80) * BR_SCALAR(dt)));

	/* moving forward and back */
	if (prog.keys[SDL_SCANCODE_UP] || prog.keys[SDL_SCANCODE_W])
		BrMatrix34PreTranslate(&prog.camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(0), BR_SCALAR(-8) * BR_SCALAR(dt));
	if (prog.keys[SDL_SCANCODE_DOWN] || prog.keys[SDL_SCANCODE_S])
		BrMatrix34PreTranslate(&prog.camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(0), BR_SCALAR(8) * BR_SCALAR(dt));

	/* moving left and right */
	if (prog.keys[SDL_SCANCODE_A])
		BrMatrix34PreTranslate(&prog.camera->t.t.mat, BR_SCALAR(-8) * BR_SCALAR(dt), BR_SCALAR(0), BR_SCALAR(0));
	if (prog.keys[SDL_SCANCODE_D])
		BrMatrix34PreTranslate(&prog.camera->t.t.mat, BR_SCALAR(8) * BR_SCALAR(dt), BR_SCALAR(0), BR_SCALAR(0));

	/* moving up and down */
	if (prog.keys[SDL_SCANCODE_PAGEUP])
		BrMatrix34PreTranslate(&prog.camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(8) * BR_SCALAR(dt), BR_SCALAR(0));
	if (prog.keys[SDL_SCANCODE_PAGEDOWN])
		BrMatrix34PreTranslate(&prog.camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(-8) * BR_SCALAR(dt), BR_SCALAR(0));

	/* update bbox */
	BrMatrix34Copy(&prog.camera_bbox->t.t.mat, &prog.camera->t.t.mat);

	/* determine collision with any map block */
	br_actor *block;
	BR_FOR_SIMPLELIST(prog.level->children, block)
	{
		if (actor_overlapping(block, prog.camera_bbox))
			printf("camera colliding!\n");
	}

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
