
#ifndef _RAY_H_
#define _RAY_H_

/* raycaster screen buffer */
extern uint16_t __far *ray_screen_buffer;

/* initialize raycaster */
int ray_init(void);

/* quit raycaster */
void ray_quit(void);

/* run one frame of raycaster */
void ray_frame(void);

#endif /* _RAY_H_ */
