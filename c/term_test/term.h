
#ifndef _TERM_H_
#define _TERM_H_

#include <stdint.h>
#include <stddef.h>

#define WITH ";"
#define PLAIN "0"
#define NO "2"
#define BRIGHT "1"
#define DIM "2"
#define ITALIC "3"
#define UNDERLINE "4"
#define REVERSE "7"

#define FG "3"
#define BG "4"
#define BRIGHTFG "9"
#define BRIGHTBG "10"
#define BLACK "0"
#define RED "1"
#define GREEN "2"
#define YELLOW "3"
#define BLUE "4"
#define MAGENTA "5"
#define CYAN "6"
#define WHITE "7"

#define ALTBUF "?1049"
#define CURSOR "?25"
#define CLEARTERM "2J"
#define CLEARLINE "2K"
#define HIGH "h"
#define LOW "l"
#define JUMP "H"

#define ESC "\x1b["
#define COLOR "m"

#define PAL(i) "8;5;" #i
#define RGB(r, g, b) "8;2;" #r ";" #g ";" #b

/* init/shutdown */
void term_init(void);
void term_quit(void);

/* push to term */
void term_write(const char *s);
void term_printf(const char *fmt, ...);
void term_printf_xy(uint16_t x, uint16_t y, const char *fmt, ...);
void term_setxy(uint16_t x, uint16_t y);
void term_setformat(const char *fmt);
void term_clear(void);
void term_clear_line(void);

/* get */
uint16_t term_getwidth(void);
uint16_t term_getheight(void);

/* flush to screen */
void term_flush(void);

/* utils */
size_t term_textsize(const char *str);

/* widgets */
void term_filledbox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *fill);
void term_messagebox(const char *message);

/* user must implement this! */
void term_repaint(void);

#endif /* _TERM_H_ */
