
#ifndef _BRPROG_H_
#define _BRPROG_H_

/* headers*/
#include <SDL.h>
#include <brender.h>
#include <brglrend.h>
#include <brsdl2dev.h>

/* init callback fn */
typedef br_error BR_CALLBACK br_program_init_cbfn(br_actor *world, br_actor *camera, br_pixelmap *screen, br_pixelmap *colour, br_pixelmap *depth);
typedef void BR_CALLBACK br_program_quit_cbfn(void);
typedef br_error BR_CALLBACK br_program_render_cbfn(void);
typedef br_error BR_CALLBACK br_program_event_cbfn(SDL_Event *event);

/* set hooks */
void BrProgramInitHook(br_program_init_cbfn *hook);
void BrProgramQuitHook(br_program_quit_cbfn *hook);
void BrProgramRenderHook(br_program_render_cbfn *hook);
void BrProgramEventHook(br_program_event_cbfn *hook);

/* actual functions */
br_error BrProgramInit(const char *title, int w, int h);
br_error BrProgramLoop(void);
void BrProgramQuit(void);

#endif /* _BRPROG_H_ */
