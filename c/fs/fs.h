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

#ifndef _FS_H_
#define _FS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* private file struct */
typedef struct fs_file fs_file_t;

/** initialize filesystem
 *
 * determine working directory and
 *
 * @return true for success, false otherwise
 */
bool fs_init(void);

/** shutdown filesystem
 *
 * close all open file handles and free all used memory.
 */
void fs_quit(void);

bool fs_mount(const char *dir);

/** flush filesystem
 *
 * close all open file handles and reset all mountpoints. this is essentially a
 * 100% reset of the filesystem manager.
 *
 * @return true for success, false otherwise
 */
bool fs_flush(void);

#ifdef __cplusplus
}
#endif
#endif /* _FS_H_ */
