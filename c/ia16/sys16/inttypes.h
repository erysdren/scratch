
#ifndef _INTTYPES_H_
#define _INTTYPES_H_

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int int16_t;
typedef unsigned short int uint16_t;

typedef signed long int int32_t;
typedef unsigned long int uint32_t;

#define INT8_MIN (0x80)
#define INT8_MAX (0x7F)

#define UINT8_MIN (0x00)
#define UINT8_MAX (0xFF)

#define INT16_MIN (0x8000)
#define INT16_MAX (0x7FFF)

#define UINT16_MIN (0x0000)
#define UINT16_MAX (0xFFFF)

#define INT32_MIN (0x80000000)
#define INT32_MAX (0x7FFFFFFF)

#define UINT32_MIN (0x00000000)
#define UINT32_MAX (0xFFFFFFFF)

#endif /* _INTTYPES_H_ */
