
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <stdint.h>

/* mouse button masks */
#define MOUSE_LMB (0x1)
#define MOUSE_RMB (0x2)

/* enable mouse input */
void mouse_enable(void);

/* show mouse cursor */
void mouse_show(void);

/* hide mouse cursor */
void mouse_hide(void);

/* read mouse position and returns button mask */
int16_t mouse_read(int16_t *x, int16_t *y);

#endif /* _MOUSE_H_ */
