
#ifndef _STREAM_H_
#define _STREAM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/* opaque stream type */
typedef struct stream stream_t;

#define STREAM_R_TEXT "rt"
#define STREAM_R_BIN "rb"

#define STREAM_W_TEXT "wt"
#define STREAM_W_BIN "wb"

#define STREAM_RW_TEXT "r+t"
#define STREAM_RW_BIN "r+b"

/*
 * creation and destruction
 */

/* create stream from file - mode follows cstdlib */
stream_t *stream_from_file(const char *filename, const char *mode);

/* create stream from memory buffer */
stream_t *stream_from_buffer(void *buffer, size_t len, const char *mode);

/* destroy stream and free all associated memory */
void stream_delete(stream_t *s);

/*
 * reading
 */

/* read signed integers */
int stream_read_schar(stream_t *s, signed char *v);
int stream_read_sshort(stream_t *s, signed short *v);
int stream_read_sint(stream_t *s, signed int *v);
int stream_read_slong(stream_t *s, signed long *v);
int stream_read_sllong(stream_t *s, signed long long *v);

/* read unsigned integers */
int stream_read_uchar(stream_t *s, unsigned char *v);
int stream_read_ushort(stream_t *s, unsigned short *v);
int stream_read_uint(stream_t *s, unsigned int *v);
int stream_read_ulong(stream_t *s, unsigned long *v);
int stream_read_ullong(stream_t *s, unsigned long long *v);

/* read floating point numbers */
int stream_read_float(stream_t *s, float *v);
int stream_read_double(stream_t *s, double *v);
int stream_read_ldouble(stream_t *s, long double *v);

/* read strings */
int stream_read_char(stream_t *s, char *v);
int stream_read_string(stream_t *s, char *v, size_t max);

/*
 * writing
 */

/* write signed integers */
int stream_write_schar(stream_t *s, signed char v);
int stream_write_sshort(stream_t *s, signed short v);
int stream_write_sint(stream_t *s, signed int v);
int stream_write_slong(stream_t *s, signed long v);
int stream_write_sllong(stream_t *s, signed long long v);

/* write unsigned integers */
int stream_write_uchar(stream_t *s, unsigned char v);
int stream_write_ushort(stream_t *s, unsigned short v);
int stream_write_uint(stream_t *s, unsigned int v);
int stream_write_ulong(stream_t *s, unsigned long v);
int stream_write_ullong(stream_t *s, unsigned long long v);

/* write floating point numbers */
int stream_write_float(stream_t *s, float v);
int stream_write_double(stream_t *s, double v);
int stream_write_ldouble(stream_t *s, long double v);

/* write strings */
int stream_write_char(stream_t *s, char v);
int stream_write_string(stream_t *s, const char *v);

/*
 * printing
 */

int stream_printf(stream_t *s, const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif /* _STREAM_H_ */
