
#ifndef ERYSCLIB_H
#define ERYSCLIB_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#define CPU_UNKNOWN (0)
#define CPU_IA16 (1)
#define CPU_IA32 (2)
#define CPU_IA64 (3)

/*
 * cpu detection stuff
 */

#if defined(__amd64__) || defined(__x86_64__) || defined(_M_X64)
#define CPU CPU_IA64
#define HAS_STOSB (1)
#define HAS_STOSW (1)
#define HAS_STOSD (1)
#define HAS_STOSQ (1)
#elif defined(__i386__) || defined(_M_IX86)
#define CPU CPU_IA32
#define HAS_STOSB (1)
#define HAS_STOSW (1)
#define HAS_STOSD (1)
#define HAS_STOSQ (0)
#elif defined(_M_I86)
#define CPU CPU_IA16
#define HAS_STOSB (1)
#define HAS_STOSW (1)
#define HAS_STOSD (0)
#define HAS_STOSQ (0)
#else
#define CPU CPU_UNKNOWN
#define HAS_STOSB (0)
#define HAS_STOSW (0)
#define HAS_STOSD (0)
#define HAS_STOSQ (0)
#endif

/* we have assert() at home */
#define ASSERT(e) \
	do { \
		if (!(e)) die("assertion (" #e ") failed at " __FILE__ "#%d", __LINE__); \
	} while (0)

/* true and false */
#define TRUE (1 == 1)
#define FALSE (1 == 0)

/* static array size */
#define ASIZE(a) (sizeof(a) / sizeof(a[0]))

/* stop everything and die immediately */
void die(const char *fmt, ...);

/* memory */
void *mem_alloc(size_t size);
void mem_free(void *ptr);

/* file handling */
FILE *file_open(const char *filename, const char *mode);
int file_close(FILE *stream);
size_t file_write(void *ptr, size_t size, size_t n, FILE *stream);

/* strings */
int string_endswith(char *str, char *ext);
char *string_duplicate(const char *s, ...);

#ifdef __cplusplus
}
#endif
#endif /* ERYSCLIB_H */
