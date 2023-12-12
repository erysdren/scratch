
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

#include "brprogram.h"

/* tile structure */
typedef struct br_tile {
	br_uint_16 x;
	br_uint_16 y;
	br_uint_16 z;
} br_tile;

br_actor *tilemap;

br_actor *GetTile(br_uint_16 x, br_uint_16 y)
{
	br_actor *cube;

	if (!tilemap || !tilemap->children)
		return NULL;

	BR_FOR_SIMPLELIST(tilemap->children, cube)
	{
		br_tile *tile = (br_tile *)cube->user;

		if (tile->x == x && tile->y == y)
			return cube;
	}

	return NULL;
}

br_actor *AddTile(br_uint_16 x, br_uint_16 y, br_uint_16 z)
{
	br_actor *cube;
	br_tile *tile;

	/* can't stack tiles */
	if (GetTile(x, y))
		return NULL;

	/* create cube actor */
	cube = BrActorAdd(tilemap, BrActorAllocate(BR_ACTOR_MODEL, NULL));
	cube->model = BrModelFind("cube.dat");
	cube->material = BrMaterialFind("checkerboard.mat");

	/* create tile info */
	tile = BrResAllocate(cube, sizeof(br_tile), BR_MEMORY_APPLICATION);
	tile->x = x;
	tile->y = y;
	tile->z = z;

	cube->user = (void *)tile;

	/* move to position */
	BrMatrix34Translate(&cube->t.t.mat, BR_SCALAR(x), BR_SCALAR(0), BR_SCALAR(y));

	return cube;
}

br_error BrProgramInit(void)
{
	tilemap = BrActorAdd(world, BrActorAllocate(BR_ACTOR_NONE, NULL));

	return BRE_OK;
}

void BrProgramQuit(void)
{

}

br_error BrProgramRender(br_pixelmap *colour, br_pixelmap *depth)
{
	/* turning left and right */
	if (BrProgramGetKey(SDL_SCANCODE_LEFT))
		BrMatrix34PreRotateY(&camera->t.t.mat, BR_ANGLE_DEG(BR_SCALAR(80 * frametime)));
	if (BrProgramGetKey(SDL_SCANCODE_RIGHT))
		BrMatrix34PreRotateY(&camera->t.t.mat, BR_ANGLE_DEG(BR_SCALAR(-80 * frametime)));

	/* moving forward and back */
	if (BrProgramGetKey(SDL_SCANCODE_UP) || BrProgramGetKey(SDL_SCANCODE_W))
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(0), BR_SCALAR(-8 * frametime));
	if (BrProgramGetKey(SDL_SCANCODE_DOWN) || BrProgramGetKey(SDL_SCANCODE_S))
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(0), BR_SCALAR(8 * frametime));

	/* moving left and right */
	if (BrProgramGetKey(SDL_SCANCODE_A))
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(-8 * frametime), BR_SCALAR(0), BR_SCALAR(0));
	if (BrProgramGetKey(SDL_SCANCODE_D))
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(8 * frametime), BR_SCALAR(0), BR_SCALAR(0));

	/* moving up and down */
	if (BrProgramGetKey(SDL_SCANCODE_PAGEUP))
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(8 * frametime), BR_SCALAR(0));
	if (BrProgramGetKey(SDL_SCANCODE_PAGEDOWN))
		BrMatrix34PreTranslate(&camera->t.t.mat, BR_SCALAR(0), BR_SCALAR(-8 * frametime), BR_SCALAR(0));

	/* create block on space */
	if (BrProgramGetKey(SDL_SCANCODE_SPACE))
		AddTile(camera->t.t.translate.t.v[0], camera->t.t.translate.t.v[2], 1);

	/* exit on escape */
	if (BrProgramGetKey(SDL_SCANCODE_ESCAPE))
		return BRE_FAIL;

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
