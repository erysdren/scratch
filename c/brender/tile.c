
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

#include "brprogram.h"

typedef struct br_tile {
	br_uint_16 x;
	br_uint_16 y;
	br_uint_16 z;
} br_tile;

/* map */
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
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

br_actor *level;
const Uint8 *keys;

br_error BrProgramInit(void)
{
	/* move camera */
	BrMatrix34Translate(&camera->t.t.mat, BR_SCALAR(12), BR_SCALAR(0), BR_SCALAR(12));

	/* create level scene */
	level = BrActorAdd(world, BrActorAllocate(BR_ACTOR_NONE, NULL));
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] > 0)
			{
				/* create actor */
				br_actor *cube = BrActorAdd(level, BrActorAllocate(BR_ACTOR_MODEL, NULL));

				/* create tile info */
				br_tile *tile = BrResAllocate(cube, sizeof(br_tile), BR_MEMORY_APPLICATION);
				tile->x = x;
				tile->y = y;

				/* add model and material */
				cube->model = BrModelFind("cube.dat");
				cube->material = BrMaterialFind("checkerboard.mat");

				/* add tile info */
				cube->user = (void *)tile;

				/* move to position */
				BrMatrix34Translate(&cube->t.t.mat, BR_SCALAR(x), BR_SCALAR(0), BR_SCALAR(y));
			}
		}
	}

	return BRE_OK;
}

void BrProgramQuit(void)
{

}

br_error BrProgramRender(br_pixelmap *colour, br_pixelmap *depth)
{
	/* get key state */
	keys = SDL_GetKeyboardState(NULL);

	/* turning left and right */
	if (keys[SDL_SCANCODE_LEFT])
		BrMatrix34PreRotateY(&camera->t.t.mat, BR_ANGLE_DEG(BR_SCALAR(80) * BR_SCALAR(frametime)));
	if (keys[SDL_SCANCODE_RIGHT])
		BrMatrix34PreRotateY(&camera->t.t.mat, BR_ANGLE_DEG(BR_SCALAR(-80) * BR_SCALAR(frametime)));

	/* moving forward and back */
	if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(0), BR_SCALAR(-8) * BR_SCALAR(frametime));
	if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(0), BR_SCALAR(8) * BR_SCALAR(frametime));

	/* moving left and right */
	if (keys[SDL_SCANCODE_A])
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(-8) * BR_SCALAR(frametime), BR_SCALAR(0), BR_SCALAR(0));
	if (keys[SDL_SCANCODE_D])
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(8) * BR_SCALAR(frametime), BR_SCALAR(0), BR_SCALAR(0));

	/* moving up and down */
	if (keys[SDL_SCANCODE_PAGEUP])
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(8) * BR_SCALAR(frametime), BR_SCALAR(0));
	if (keys[SDL_SCANCODE_PAGEDOWN])
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(-8) * BR_SCALAR(frametime), BR_SCALAR(0));

	/* exit on escape */
	if (keys[SDL_SCANCODE_ESCAPE])
		return BRE_FAIL;

	/* update block positions */
	br_actor *block;
	BR_FOR_SIMPLELIST(level->children, block)
	{
		br_tile *tile = (br_tile *)block->user;
		BrMatrix34Translate(&block->t.t.mat, BR_SCALAR(tile->x), BR_SCALAR(0), BR_SCALAR(tile->y));
	}

	/* do render */
    BrRendererFrameBegin();
	BrPixelmapFill(colour, BR_COLOUR_RGB(66, 66, 66));
	BrPixelmapFill(depth, 0xFFFFFFFF);
	BrZbSceneRender(world, camera, colour, depth);
    BrRendererFrameEnd();

	return BRE_OK;
}

br_error BrProgramEvent(SDL_Event *event)
{
	return BRE_OK;
}

/* main */
int main(int argc, char **argv)
{
	return BrProgram("tile", 1280, 720);
}
