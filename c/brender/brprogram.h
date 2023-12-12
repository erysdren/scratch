
#ifndef _BRPROG_H_
#define _BRPROG_H_

/* headers*/
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

/* globals */
extern br_actor *world;
extern br_actor *camera;
extern float frametime;

/* entry point */
int BrProgram(const char *title, int w, int h);

/* user must implement these */
br_error BrProgramInit(void);
void BrProgramQuit(void);
br_error BrProgramRender(br_pixelmap *colour, br_pixelmap *depth);
br_error BrProgramEvent(SDL_Event *event);

#endif /* _BRPROG_H_ */
