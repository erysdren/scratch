
#ifndef _UTIL_H_
#define _UTIL_H_

__attribute__((pure)) int imin(int x, int y);
__attribute__((pure)) int imax(int x, int y);
__attribute__((pure)) int iclamp(int i, int min, int max);
void die(const char *fmt, ...);

#endif /* _UTIL_H_ */
