/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _LUNA_H_
#define _LUNA_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <unistd.h>

#include <dos.h>
#include <io.h>
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/*
 *
 * types
 *
 */

typedef struct point {
	lua_Integer x, y;
} point_t;

typedef struct rect {
	lua_Integer x, y, w, h;
} rect_t;

typedef struct appl {
	char *name;
	rect_t frame;
	int reg;
	int z;
} appl_t;

/*
 *
 * luna.c
 *
 */

/* register new appl and get handle (or -1 for error) */
int appl_register(lua_State *L, const char *name);

/* unregister appl by handle */
void appl_unregister(lua_State *L, int reg);

/* create new appl and get structure (or NULL for error) */
appl_t *appl_new(lua_State *L, const char *name);

/* delete appl and free memory */
void appl_delete(lua_State *L, appl_t **appl);

/* call function on appl */
int appl_call(lua_State *L, appl_t *appl, const char *func);

/* call draw function on appl */
int appl_draw(lua_State *L, appl_t *appl);

/* open appl lib */
#define LUA_APPLLIBNAME "appl"
int luaopen_appl(lua_State *L);

/* open luna lib */
#define LUA_LUNALIBNAME "luna"
int luaopen_luna(lua_State *L);

/* open all luna libs */
void luna_openlibs(lua_State *L);

/*
 *
 * mouse.c
 *
 */

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

/*
 *
 * rect.c
 *
 */

/* returns 1 if r0 fully contains r1 */
int rect_contains(rect_t *r0, rect_t *r1);

/* returns 1 if r0 and r1 intersect in any way */
int rect_intersects(rect_t *r0, rect_t *r1);

/* merge r0 and r1 into out by their largest extents */
void rect_merge(rect_t *out, rect_t *r0, rect_t *r1);

/* convert a rectangle to two points */
void rect_to_points(rect_t *r, point_t *p0, point_t *p1);

/* convert two points to a rect */
void points_to_rect(rect_t *r, point_t *p0, point_t *p1);

/*
 *
 * util.c
 *
 */

__attribute__((pure)) int imin(int x, int y);
__attribute__((pure)) int imax(int x, int y);
__attribute__((pure)) int iclamp(int i, int min, int max);

int file_exists(const char *filename);

void die(const char *fmt, ...);

void *memset8(void *dest, uint8_t val, size_t n);
void *memset16(void *dest, uint16_t val, size_t n);
void *memset32(void *dest, uint32_t val, size_t n);

/*
 *
 * vid.c
 *
 */


#define VID_WIDTH (80)
#define VID_HEIGHT (50)
#define VID_BITS_PER_PIXEL (16)
#define VID_BYTES_PER_PIXEL (VID_BITS_PER_PIXEL / 8)
#define VID_PITCH (VID_WIDTH * VID_BYTES_PER_PIXEL)
#define VID_BUFFER_SIZE (VID_PITCH * VID_HEIGHT)

#define VID_FONT_WIDTH (8)
#define VID_FONT_HEIGHT (8)

/* start video system */
void vid_init(void);

/* shutdown video system */
void vid_quit(void);

/* get pointer to writeable video framebuffer */
uint8_t *vid_framebuffer_get(void);

/* set video mode */
void vid_mode_set(uint8_t mode);

/* get current video mode */
uint8_t vid_mode_get(void);

/* wait for vertical retrace */
void vid_vsync_wait(void);

/* set palette color at index */
void vid_palette_set_color(int i, uint8_t red, uint8_t grn, uint8_t blu);

/* set palette of N colors */
void vid_palette_set(int num_colors, uint8_t *colors);

/* put background color at x/y */
void vid_put_bg(int x, int y, uint8_t c);

/* put foreground color at x/y */
void vid_put_fg(int x, int y, uint8_t c);

/* put foreground character at x/y */
void vid_put_code(int x, int y, unsigned char c);

/* fill background color rect at x/y */
void vid_fill_bg(int x, int y, int w, int h, uint8_t c);

/* fill foreground color rect at x/y */
void vid_fill_fg(int x, int y, int w, int h, uint8_t c);

/* fill foreground character rect at x/y */
void vid_fill_code(int x, int y, int w, int h, unsigned char c);

/* draw string at x/y */
void vid_put_string(int x, int y, uint8_t c, const char *s);

/* set cursor position */
void vid_cursor_set_position(uint8_t x, uint8_t y);

/* set stencil dimensions */
void vid_stencil_set(int x, int y, int w, int h);

/* set coordinate offset */
void vid_offset_set(int x, int y);

/* clear zbuffer */
void vid_zbuffer_clear(uint8_t v);

/* fill zbuffer area */
void vid_zbuffer_fill(int x, int y, int w, int h, uint8_t v);

/* set current zbuffer value for all draw operations */
void vid_zbuffer_set(uint8_t v);

#endif /* _LUNA_H_ */
