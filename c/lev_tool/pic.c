/* This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild */

#define KS_DEPEND_ON_INTERNALS
#include "pic.h"

static void ksx_fill_pic_instances(ksx_pic* data);
static void ksx_read_pic_instances(ksx_pic* data);
static ksx_pic* ksx_read_pic(ks_stream* root_stream, ksx_pic* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_abgr1555_instances(ksx_abgr1555* data);
static void ksx_read_abgr1555_instances(ksx_abgr1555* data);
static ksx_abgr1555* ksx_read_abgr1555(ks_stream* root_stream, ksx_pic* root_data, void* parent_data, ks_stream* stream);
struct ksx_abgr1555_internal
{
    ks_bool (*_get_a)(ksx_abgr1555* data);
    uint64_t (*_get_b)(ksx_abgr1555* data);
    uint64_t (*_get_g)(ksx_abgr1555* data);
    uint64_t (*_get_r)(ksx_abgr1555* data);
};

struct ksx_pic_internal
{
    ksx_array_abgr1555* (*_get_palette)(ksx_pic* data);
    int32_t (*_get_width)(ksx_pic* data);
    int32_t (*_get_height)(ksx_pic* data);
    ks_array_uint8_t* (*_get_bitmap)(ksx_pic* data);
};


ksx_pic* ksx_read_pic_from_stream(ks_stream* stream, ks_error* error)
{
    ksx_pic* data;
    data = ksx_read_pic(stream, 0, 0, stream);
    if (error) *error = stream->config->error;
    KS_CHECK_DATA();
    ksx_read_pic_instances(data);
    if (error) *error = stream->config->error;
    KS_CHECK_DATA();
    return data;
}

static ksx_pic* ksx_read_pic(ks_stream* root_stream, ksx_pic* root_data, void* parent_data, ks_stream* stream)
{
    ksx_pic* data = ks_alloc(root_stream->config, sizeof(ksx_pic));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_pic), sizeof(ksx_pic_internal), (ks_usertype_generic*)parent_data));
    root_data = root_data != 0 ? root_data : data;
    ksx_fill_pic_instances(data);
    /* Array (repeat-expr) */
    data->palette = ks_alloc(root_stream->config, sizeof(ksx_array_abgr1555));
    data->palette->size = 256;
    data->palette->data = ks_alloc(root_stream->config, sizeof(ksx_abgr1555*) * data->palette->size);
    KS_CHECK_DATA(HANDLE(data->palette) = ks_handle_create(stream, data->palette, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_abgr1555*), 0, 0));
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_DATA(data->palette->data[i] = ksx_read_abgr1555(root_stream, root_data, data, stream));
    }
    KS_CHECK_DATA(data->width = ks_stream_read_s4be(stream));
    KS_CHECK_DATA(data->height = ks_stream_read_s4be(stream));
    /* Array (repeat-expr) */
    data->bitmap = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->bitmap->size = (FIELD(data, ksx_pic, width) * FIELD(data, ksx_pic, height));
    data->bitmap->data = ks_alloc(root_stream->config, sizeof(uint8_t) * data->bitmap->size);
    KS_CHECK_DATA(HANDLE(data->bitmap) = ks_handle_create(stream, data->bitmap, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    for (i = 0; i < data->bitmap->size; i++)
    {
        KS_CHECK_DATA(data->bitmap->data[i] = ks_stream_read_u1(stream));
    }
    return data;
}

static ksx_abgr1555* ksx_read_abgr1555(ks_stream* root_stream, ksx_pic* root_data, void* parent_data, ks_stream* stream)
{
    ksx_abgr1555* data = ks_alloc(root_stream->config, sizeof(ksx_abgr1555));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_abgr1555), sizeof(ksx_abgr1555_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_abgr1555_instances(data);
    KS_CHECK_DATA(data->a = ks_stream_read_bits_be(stream, 1));
    KS_CHECK_DATA(data->b = ks_stream_read_bits_be(stream, 5));
    KS_CHECK_DATA(data->g = ks_stream_read_bits_be(stream, 5));
    KS_CHECK_DATA(data->r = ks_stream_read_bits_be(stream, 5));
    return data;
}

static ks_bool ksx_get_abgr1555_a(ksx_abgr1555* data)
{
    return data->a;
}

static uint64_t ksx_get_abgr1555_b(ksx_abgr1555* data)
{
    return data->b;
}

static uint64_t ksx_get_abgr1555_g(ksx_abgr1555* data)
{
    return data->g;
}

static uint64_t ksx_get_abgr1555_r(ksx_abgr1555* data)
{
    return data->r;
}

static ksx_array_abgr1555* ksx_get_pic_palette(ksx_pic* data)
{
    return data->palette;
}

static int32_t ksx_get_pic_width(ksx_pic* data)
{
    return data->width;
}

static int32_t ksx_get_pic_height(ksx_pic* data)
{
    return data->height;
}

static ks_array_uint8_t* ksx_get_pic_bitmap(ksx_pic* data)
{
    return data->bitmap;
}

static void ksx_fill_abgr1555_instances(ksx_abgr1555* data)
{
    ksx_abgr1555_internal* internal = (ksx_abgr1555_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_a = ksx_get_abgr1555_a;
    internal->_get_b = ksx_get_abgr1555_b;
    internal->_get_g = ksx_get_abgr1555_g;
    internal->_get_r = ksx_get_abgr1555_r;
}

static void ksx_read_abgr1555_instances(ksx_abgr1555* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_abgr1555_internal* internal = (ksx_abgr1555_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_pic_instances(ksx_pic* data)
{
    ksx_pic_internal* internal = (ksx_pic_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_palette = ksx_get_pic_palette;
    internal->_get_width = ksx_get_pic_width;
    internal->_get_height = ksx_get_pic_height;
    internal->_get_bitmap = ksx_get_pic_bitmap;
}

static void ksx_read_pic_instances(ksx_pic* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_pic_internal* internal = (ksx_pic_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_VOID(ksx_read_abgr1555_instances(data->palette->data[i]));
    }
}

