
#ifndef _FILE_H_
#define _FILE_H_

#include "inttypes.h"

/* file handle type */
typedef uint16_t file_t;

/* enum for read/write/etc */
enum {
	MODE_READ = 0,
	MODE_WRITE = 1,
	MODE_READWRITE = 2
};

/* enum for file attributes */
enum {
	ATTR_NORMAL = 0,
	ATTR_READONLY = 1,
	ATTR_HIDDEN = 2,
	ATTR_SYSTEM = 3
};

/* create file and return handle */
file_t file_create(const char __far *filename, uint16_t attribute);

/* open file and return handle */
file_t file_open(const char __far *filename, uint8_t mode);

/* close file handle */
void file_close(file_t file);

/* write bytes to file */
uint16_t file_write(file_t file, void __far *data, uint16_t size);

/* write string to file */
uint16_t file_print(file_t file, string s);

#endif /* _FILE_H_ */
