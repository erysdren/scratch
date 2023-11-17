/* This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild */

#ifndef KAITAI_PIC_H
#define KAITAI_PIC_H

#include "kaitaistruct.h"

/* Forward declarations */

/* Main struct */
#ifndef HAVE_DECL_pic
#define HAVE_DECL_pic
typedef struct ksx_pic ksx_pic;
#endif
typedef struct ksx_array_pic ksx_array_pic;
typedef struct ksx_pic_internal ksx_pic_internal;
typedef struct ksx_abgr1555 ksx_abgr1555;
typedef struct ksx_array_abgr1555 ksx_array_abgr1555;
typedef struct ksx_abgr1555_internal ksx_abgr1555_internal;

/* Enums */

/* Main structures */

ksx_pic* ksx_read_pic_from_stream(ks_stream* stream, ks_error* error);

struct ksx_abgr1555
{
    ks_usertype_generic kaitai_base;
    ks_bool a;
    uint64_t b;
    uint64_t g;
    uint64_t r;
};

struct ksx_pic
{
    ks_usertype_generic kaitai_base;
    ksx_array_abgr1555* palette;
    int32_t width;
    int32_t height;
    ks_array_uint8_t* bitmap;
};

/* Array structures */

struct ksx_array_pic
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_pic** data;
};

struct ksx_array_abgr1555
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_abgr1555** data;
};

#endif
