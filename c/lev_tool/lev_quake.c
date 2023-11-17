/* This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild */

#define KS_DEPEND_ON_INTERNALS
#include "lev_quake.h"

static void ksx_fill_lev_quake_instances(ksx_lev_quake* data);
static void ksx_read_lev_quake_instances(ksx_lev_quake* data);
static ksx_lev_quake* ksx_read_lev_quake(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_tile_texture_data_t_instances(ksx_tile_texture_data_t* data);
static void ksx_read_tile_texture_data_t_instances(ksx_tile_texture_data_t* data);
static ksx_tile_texture_data_t* ksx_read_tile_texture_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_entity_data_t_instances(ksx_entity_data_t* data);
static void ksx_read_entity_data_t_instances(ksx_entity_data_t* data);
static ksx_entity_data_t* ksx_read_entity_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_resource_0x6c_t_instances(ksx_resource_0x6c_t* data);
static void ksx_read_resource_0x6c_t_instances(ksx_resource_0x6c_t* data);
static ksx_resource_0x6c_t* ksx_read_resource_0x6c_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_sector_t_instances(ksx_sector_t* data);
static void ksx_read_sector_t_instances(ksx_sector_t* data);
static ksx_sector_t* ksx_read_sector_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_resources_prefix_t_instances(ksx_resources_prefix_t* data);
static void ksx_read_resources_prefix_t_instances(ksx_resources_prefix_t* data);
static ksx_resources_prefix_t* ksx_read_resources_prefix_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_sound_t_instances(ksx_sound_t* data);
static void ksx_read_sound_t_instances(ksx_sound_t* data);
static ksx_sound_t* ksx_read_sound_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_entity_t_instances(ksx_entity_t* data);
static void ksx_read_entity_t_instances(ksx_entity_t* data);
static ksx_entity_t* ksx_read_entity_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream, int32_t p_index);
static void ksx_fill_resources_t_instances(ksx_resources_t* data);
static void ksx_read_resources_t_instances(ksx_resources_t* data);
static ksx_resources_t* ksx_read_resources_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_vertex_t_instances(ksx_vertex_t* data);
static void ksx_read_vertex_t_instances(ksx_vertex_t* data);
static ksx_vertex_t* ksx_read_vertex_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_header_t_instances(ksx_header_t* data);
static void ksx_read_header_t_instances(ksx_header_t* data);
static ksx_header_t* ksx_read_header_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_resource_0x34_t_instances(ksx_resource_0x34_t* data);
static void ksx_read_resource_0x34_t_instances(ksx_resource_0x34_t* data);
static ksx_resource_0x34_t* ksx_read_resource_0x34_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_entity_polymover_t_instances(ksx_entity_polymover_t* data);
static void ksx_read_entity_polymover_t_instances(ksx_entity_polymover_t* data);
static ksx_entity_polymover_t* ksx_read_entity_polymover_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_len_and_unknown_t_instances(ksx_len_and_unknown_t* data);
static void ksx_read_len_and_unknown_t_instances(ksx_len_and_unknown_t* data);
static ksx_len_and_unknown_t* ksx_read_len_and_unknown_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_quad_t_instances(ksx_quad_t* data);
static void ksx_read_quad_t_instances(ksx_quad_t* data);
static ksx_quad_t* ksx_read_quad_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_texture_t_instances(ksx_texture_t* data);
static void ksx_read_texture_t_instances(ksx_texture_t* data);
static ksx_texture_t* ksx_read_texture_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_palette_entry_t_instances(ksx_palette_entry_t* data);
static void ksx_read_palette_entry_t_instances(ksx_palette_entry_t* data);
static ksx_palette_entry_t* ksx_read_palette_entry_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_entity_polylink_data1_t_instances(ksx_entity_polylink_data1_t* data);
static void ksx_read_entity_polylink_data1_t_instances(ksx_entity_polylink_data1_t* data);
static ksx_entity_polylink_data1_t* ksx_read_entity_polylink_data1_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_entity_polylink_data2_t_instances(ksx_entity_polylink_data2_t* data);
static void ksx_read_entity_polylink_data2_t_instances(ksx_entity_polylink_data2_t* data);
static ksx_entity_polylink_data2_t* ksx_read_entity_polylink_data2_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_resource_t_instances(ksx_resource_t* data);
static void ksx_read_resource_t_instances(ksx_resource_t* data);
static ksx_resource_t* ksx_read_resource_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_tile_t_instances(ksx_tile_t* data);
static void ksx_read_tile_t_instances(ksx_tile_t* data);
static ksx_tile_t* ksx_read_tile_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_entity_polylink_t_instances(ksx_entity_polylink_t* data);
static void ksx_read_entity_polylink_t_instances(ksx_entity_polylink_t* data);
static ksx_entity_polylink_t* ksx_read_entity_polylink_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_plane_t_instances(ksx_plane_t* data);
static void ksx_read_plane_t_instances(ksx_plane_t* data);
static ksx_plane_t* ksx_read_plane_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_sky_bitmap_t_instances(ksx_sky_bitmap_t* data);
static void ksx_read_sky_bitmap_t_instances(ksx_sky_bitmap_t* data);
static ksx_sky_bitmap_t* ksx_read_sky_bitmap_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_entity_generic_t_instances(ksx_entity_generic_t* data);
static void ksx_read_entity_generic_t_instances(ksx_entity_generic_t* data);
static ksx_entity_generic_t* ksx_read_entity_generic_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_resource_0x6a_t_instances(ksx_resource_0x6a_t* data);
static void ksx_read_resource_0x6a_t_instances(ksx_resource_0x6a_t* data);
static ksx_resource_0x6a_t* ksx_read_resource_0x6a_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_sky_data_t_instances(ksx_sky_data_t* data);
static void ksx_read_sky_data_t_instances(ksx_sky_data_t* data);
static ksx_sky_data_t* ksx_read_sky_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
static void ksx_fill_tile_color_data_t_instances(ksx_tile_color_data_t* data);
static void ksx_read_tile_color_data_t_instances(ksx_tile_color_data_t* data);
static ksx_tile_color_data_t* ksx_read_tile_color_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream);
struct ksx_tile_texture_data_t_internal
{
    ks_bytes* (*_get_data)(ksx_tile_texture_data_t* data);
};

struct ksx_entity_data_t_internal
{
    ks_bytes* (*_get_data)(ksx_entity_data_t* data);
};

struct ksx_resource_0x6c_t_internal
{
    uint16_t (*_get_unknown0)(ksx_resource_0x6c_t* data);
    uint16_t (*_get_len_data)(ksx_resource_0x6c_t* data);
    ks_bytes* (*_get_data)(ksx_resource_0x6c_t* data);
};

struct ksx_sector_t_internal
{
    ks_array_uint16_t* (*_get_reserved)(ksx_sector_t* data);
    ks_array_uint16_t* (*_get_position)(ksx_sector_t* data);
    uint16_t (*_get_distance)(ksx_sector_t* data);
    uint16_t (*_get_plane_start_index)(ksx_sector_t* data);
    uint16_t (*_get_plane_end_index)(ksx_sector_t* data);
    ks_array_uint16_t* (*_get_unknown)(ksx_sector_t* data);
};

struct ksx_resources_prefix_t_internal
{
    uint32_t (*_get_num_values)(ksx_resources_prefix_t* data);
    ks_array_int16_t* (*_get_values)(ksx_resources_prefix_t* data);
};

struct ksx_sound_t_internal
{
    int32_t (*_get_len_samples)(ksx_sound_t* data);
    int32_t (*_get_maybe_pitch_adjust)(ksx_sound_t* data);
    int32_t (*_get_bits)(ksx_sound_t* data);
    int32_t (*_get_loop_point)(ksx_sound_t* data);
    ks_bytes* (*_get_samples)(ksx_sound_t* data);
};

struct ksx_entity_t_internal
{
    ks_bool _flag_get_entity_data;
    ks_usertype_generic* (*_get_get_entity_data)(ksx_entity_t* data);
    ks_callback _read_instances_get_entity_data;
    uint16_t (*_get_ent_type)(ksx_entity_t* data);
    uint16_t (*_get_ofs_entity_data)(ksx_entity_t* data);
    int32_t (*_get_index)(ksx_entity_t* data);
};

struct ksx_resources_t_internal
{
    ksx_resources_prefix_t* (*_get_prefix)(ksx_resources_t* data);
    uint32_t (*_get_num_sounds)(ksx_resources_t* data);
    ksx_array_sound_t* (*_get_sounds)(ksx_resources_t* data);
    uint32_t (*_get_len_palette)(ksx_resources_t* data);
    ksx_array_palette_entry_t* (*_get_palette)(ksx_resources_t* data);
    uint32_t (*_get_num_resources)(ksx_resources_t* data);
    ksx_array_resource_t* (*_get_resources)(ksx_resources_t* data);
};

struct ksx_vertex_t_internal
{
    ks_array_int16_t* (*_get_coords)(ksx_vertex_t* data);
    uint8_t (*_get_color_lookup)(ksx_vertex_t* data);
    uint8_t (*_get_reserved)(ksx_vertex_t* data);
};

struct ksx_header_t_internal
{
    uint32_t (*_get_unknown_01)(ksx_header_t* data);
    uint32_t (*_get_unknown_02)(ksx_header_t* data);
    uint32_t (*_get_num_sectors)(ksx_header_t* data);
    uint32_t (*_get_num_planes)(ksx_header_t* data);
    uint32_t (*_get_num_vertices)(ksx_header_t* data);
    uint32_t (*_get_num_quads)(ksx_header_t* data);
    uint32_t (*_get_len_tile_texture_data)(ksx_header_t* data);
    uint32_t (*_get_num_tiles)(ksx_header_t* data);
    uint32_t (*_get_len_tile_color_data)(ksx_header_t* data);
    uint32_t (*_get_num_entities)(ksx_header_t* data);
    uint32_t (*_get_len_entity_data)(ksx_header_t* data);
    uint32_t (*_get_num_entity_polylinks)(ksx_header_t* data);
    uint32_t (*_get_num_entity_polylink_data1_segments)(ksx_header_t* data);
    uint32_t (*_get_num_entity_polylink_data2_segments)(ksx_header_t* data);
    uint32_t (*_get_num_unknown)(ksx_header_t* data);
};

struct ksx_resource_0x34_t_internal
{
    uint16_t (*_get_unknown0)(ksx_resource_0x34_t* data);
    ks_array_uint64_t* (*_get_bitmap)(ksx_resource_0x34_t* data);
};

struct ksx_entity_polymover_t_internal
{
    int16_t (*_get_polylink_id)(ksx_entity_polymover_t* data);
    ks_array_int16_t* (*_get_data)(ksx_entity_polymover_t* data);
};

struct ksx_len_and_unknown_t_internal
{
    uint32_t (*_get_len_data)(ksx_len_and_unknown_t* data);
    ks_bytes* (*_get_data)(ksx_len_and_unknown_t* data);
};

struct ksx_quad_t_internal
{
    ks_array_uint8_t* (*_get_vertex_indices)(ksx_quad_t* data);
    uint8_t (*_get_texture_index)(ksx_quad_t* data);
};

struct ksx_texture_t_internal
{
    ksx_array_palette_entry_t* (*_get_palette)(ksx_texture_t* data);
    ks_array_uint64_t* (*_get_bitmap)(ksx_texture_t* data);
};

struct ksx_palette_entry_t_internal
{
    ks_bool (*_get_a)(ksx_palette_entry_t* data);
    uint64_t (*_get_b)(ksx_palette_entry_t* data);
    uint64_t (*_get_g)(ksx_palette_entry_t* data);
    uint64_t (*_get_r)(ksx_palette_entry_t* data);
};

struct ksx_entity_polylink_data1_t_internal
{
    ks_array_uint8_t* (*_get_data)(ksx_entity_polylink_data1_t* data);
};

struct ksx_entity_polylink_data2_t_internal
{
    ks_array_uint8_t* (*_get_data)(ksx_entity_polylink_data2_t* data);
};

struct ksx_resource_t_internal
{
    uint8_t (*_get_flags)(ksx_resource_t* data);
    uint8_t (*_get_resource_type)(ksx_resource_t* data);
    ks_usertype_generic* (*_get_data)(ksx_resource_t* data);
    ks_callback _read_instances_data;
};

struct ksx_tile_t_internal
{
    ks_bool _flag_get_color_data;
    ks_array_uint8_t* (*_get_get_color_data)(ksx_tile_t* data);
    ks_bool _flag_get_tile_texture_data;
    ks_array_uint8_t* (*_get_get_tile_texture_data)(ksx_tile_t* data);
    uint16_t (*_get_ofs_texture_data)(ksx_tile_t* data);
    uint8_t (*_get_width)(ksx_tile_t* data);
    uint8_t (*_get_height)(ksx_tile_t* data);
    uint16_t (*_get_ofs_color_data)(ksx_tile_t* data);
    uint16_t (*_get_unknown)(ksx_tile_t* data);
    ks_array_int32_t* (*_get_horizontal_vector)(ksx_tile_t* data);
    ks_array_int32_t* (*_get_vertical_vector)(ksx_tile_t* data);
    ks_array_int32_t* (*_get_base_vector)(ksx_tile_t* data);
};

struct ksx_entity_polylink_t_internal
{
    ks_bool _flag_getdata1;
    ks_array_uint8_t* (*_get_getdata1)(ksx_entity_polylink_t* data);
    ks_bool _flag_getdata2;
    ks_array_uint8_t* (*_get_getdata2)(ksx_entity_polylink_t* data);
    uint16_t (*_get_lead)(ksx_entity_polylink_t* data);
    ks_array_uint16_t* (*_get_ofs_entity_polylink_data1)(ksx_entity_polylink_t* data);
    ks_array_uint16_t* (*_get_ofs_entity_polylink_data2)(ksx_entity_polylink_t* data);
    uint16_t (*_get_unknown)(ksx_entity_polylink_t* data);
    ks_array_uint16_t* (*_get_reserved)(ksx_entity_polylink_t* data);
};

struct ksx_plane_t_internal
{
    ks_array_uint16_t* (*_get_vertex_indices)(ksx_plane_t* data);
    uint16_t (*_get_sector_index)(ksx_plane_t* data);
    uint16_t (*_get_flags)(ksx_plane_t* data);
    uint16_t (*_get_collision_flags)(ksx_plane_t* data);
    uint16_t (*_get_tile_index)(ksx_plane_t* data);
    uint16_t (*_get_unknown_index)(ksx_plane_t* data);
    uint16_t (*_get_quad_start_index)(ksx_plane_t* data);
    uint16_t (*_get_quad_end_index)(ksx_plane_t* data);
    uint16_t (*_get_vertex_start_index)(ksx_plane_t* data);
    uint16_t (*_get_vertex_end_index)(ksx_plane_t* data);
    ks_array_int16_t* (*_get_normal)(ksx_plane_t* data);
    int16_t (*_get_distance)(ksx_plane_t* data);
    int16_t (*_get_angle)(ksx_plane_t* data);
    ks_array_uint16_t* (*_get_reserved)(ksx_plane_t* data);
};

struct ksx_sky_bitmap_t_internal
{
    ks_bytes* (*_get_image)(ksx_sky_bitmap_t* data);
};

struct ksx_entity_generic_t_internal
{
    int16_t (*_get_start)(ksx_entity_generic_t* data);
    ks_array_int16_t* (*_get_coords)(ksx_entity_generic_t* data);
};

struct ksx_resource_0x6a_t_internal
{
    uint16_t (*_get_unknown0)(ksx_resource_0x6a_t* data);
    uint16_t (*_get_len_data)(ksx_resource_0x6a_t* data);
    ks_bytes* (*_get_data)(ksx_resource_0x6a_t* data);
};

struct ksx_sky_data_t_internal
{
    ksx_array_palette_entry_t* (*_get_palette)(ksx_sky_data_t* data);
    ksx_array_sky_bitmap_t* (*_get_bitmaps)(ksx_sky_data_t* data);
};

struct ksx_tile_color_data_t_internal
{
    ks_bytes* (*_get_data)(ksx_tile_color_data_t* data);
};

struct ksx_lev_quake_internal
{
    ksx_sky_data_t* (*_get_sky_data)(ksx_lev_quake* data);
    ksx_header_t* (*_get_header)(ksx_lev_quake* data);
    ksx_array_sector_t* (*_get_sectors)(ksx_lev_quake* data);
    ksx_array_plane_t* (*_get_planes)(ksx_lev_quake* data);
    ksx_array_tile_t* (*_get_tiles)(ksx_lev_quake* data);
    ksx_array_vertex_t* (*_get_vertices)(ksx_lev_quake* data);
    ksx_array_quad_t* (*_get_quads)(ksx_lev_quake* data);
    ksx_array_entity_t* (*_get_entities)(ksx_lev_quake* data);
    ksx_array_entity_polylink_t* (*_get_entity_polylinks)(ksx_lev_quake* data);
    ksx_entity_polylink_data1_t* (*_get_entity_polylink_data1)(ksx_lev_quake* data);
    ksx_entity_polylink_data2_t* (*_get_entity_polylink_data2)(ksx_lev_quake* data);
    ksx_entity_data_t* (*_get_entity_data)(ksx_lev_quake* data);
    ksx_tile_texture_data_t* (*_get_tile_texture_data)(ksx_lev_quake* data);
    ksx_tile_color_data_t* (*_get_tile_color_data)(ksx_lev_quake* data);
    ks_array_bytes* (*_get_unknown)(ksx_lev_quake* data);
    ksx_resources_t* (*_get_resources)(ksx_lev_quake* data);
    ksx_len_and_unknown_t* (*_get_unknown0)(ksx_lev_quake* data);
    ks_string* (*_get_level_name)(ksx_lev_quake* data);
    ks_array_uint32_t* (*_get_unknown1)(ksx_lev_quake* data);
    ksx_len_and_unknown_t* (*_get_unknown2)(ksx_lev_quake* data);
    ksx_len_and_unknown_t* (*_get_unknown3)(ksx_lev_quake* data);
};


ksx_lev_quake* ksx_read_lev_quake_from_stream(ks_stream* stream, ks_error* error)
{
    ksx_lev_quake* data;
    data = ksx_read_lev_quake(stream, 0, 0, stream);
    if (error) *error = stream->config->error;
    KS_CHECK_DATA();
    ksx_read_lev_quake_instances(data);
    if (error) *error = stream->config->error;
    KS_CHECK_DATA();
    return data;
}

static ksx_lev_quake* ksx_read_lev_quake(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_lev_quake* data = ks_alloc(root_stream->config, sizeof(ksx_lev_quake));
    ks_bytes* _raw_sky_data;
    ks_stream* _io_sky_data;
    ks_bytes* _raw_entity_polylink_data1;
    ks_stream* _io_entity_polylink_data1;
    ks_bytes* _raw_entity_polylink_data2;
    ks_stream* _io_entity_polylink_data2;
    ks_bytes* _raw_entity_data;
    ks_stream* _io_entity_data;
    ks_bytes* _raw_tile_texture_data;
    ks_stream* _io_tile_texture_data;
    ks_bytes* _raw_tile_color_data;
    ks_stream* _io_tile_color_data;
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_lev_quake), sizeof(ksx_lev_quake_internal), (ks_usertype_generic*)parent_data));
    root_data = root_data != 0 ? root_data : data;
    ksx_fill_lev_quake_instances(data);
    KS_CHECK_DATA(_raw_sky_data = ks_stream_read_bytes(stream, 131104));
    /* Subtype with substream */
    _io_sky_data = ks_stream_create_from_bytes(_raw_sky_data);
    KS_CHECK_DATA(data->sky_data = ksx_read_sky_data_t(root_stream, root_data, data, _io_sky_data));
    KS_CHECK_DATA(data->header = ksx_read_header_t(root_stream, root_data, data, stream));
    /* Array (repeat-expr) */
    data->sectors = ks_alloc(root_stream->config, sizeof(ksx_array_sector_t));
    data->sectors->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_sectors);
    data->sectors->data = ks_alloc(root_stream->config, sizeof(ksx_sector_t*) * data->sectors->size);
    KS_CHECK_DATA(HANDLE(data->sectors) = ks_handle_create(stream, data->sectors, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_sector_t*), 0, 0));
    for (i = 0; i < data->sectors->size; i++)
    {
        KS_CHECK_DATA(data->sectors->data[i] = ksx_read_sector_t(root_stream, root_data, data, stream));
    }
    /* Array (repeat-expr) */
    data->planes = ks_alloc(root_stream->config, sizeof(ksx_array_plane_t));
    data->planes->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_planes);
    data->planes->data = ks_alloc(root_stream->config, sizeof(ksx_plane_t*) * data->planes->size);
    KS_CHECK_DATA(HANDLE(data->planes) = ks_handle_create(stream, data->planes, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_plane_t*), 0, 0));
    for (i = 0; i < data->planes->size; i++)
    {
        KS_CHECK_DATA(data->planes->data[i] = ksx_read_plane_t(root_stream, root_data, data, stream));
    }
    /* Array (repeat-expr) */
    data->tiles = ks_alloc(root_stream->config, sizeof(ksx_array_tile_t));
    data->tiles->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_tiles);
    data->tiles->data = ks_alloc(root_stream->config, sizeof(ksx_tile_t*) * data->tiles->size);
    KS_CHECK_DATA(HANDLE(data->tiles) = ks_handle_create(stream, data->tiles, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_tile_t*), 0, 0));
    for (i = 0; i < data->tiles->size; i++)
    {
        KS_CHECK_DATA(data->tiles->data[i] = ksx_read_tile_t(root_stream, root_data, data, stream));
    }
    /* Array (repeat-expr) */
    data->vertices = ks_alloc(root_stream->config, sizeof(ksx_array_vertex_t));
    data->vertices->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_vertices);
    data->vertices->data = ks_alloc(root_stream->config, sizeof(ksx_vertex_t*) * data->vertices->size);
    KS_CHECK_DATA(HANDLE(data->vertices) = ks_handle_create(stream, data->vertices, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_vertex_t*), 0, 0));
    for (i = 0; i < data->vertices->size; i++)
    {
        KS_CHECK_DATA(data->vertices->data[i] = ksx_read_vertex_t(root_stream, root_data, data, stream));
    }
    /* Array (repeat-expr) */
    data->quads = ks_alloc(root_stream->config, sizeof(ksx_array_quad_t));
    data->quads->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_quads);
    data->quads->data = ks_alloc(root_stream->config, sizeof(ksx_quad_t*) * data->quads->size);
    KS_CHECK_DATA(HANDLE(data->quads) = ks_handle_create(stream, data->quads, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_quad_t*), 0, 0));
    for (i = 0; i < data->quads->size; i++)
    {
        KS_CHECK_DATA(data->quads->data[i] = ksx_read_quad_t(root_stream, root_data, data, stream));
    }
    /* Array (repeat-expr) */
    data->entities = ks_alloc(root_stream->config, sizeof(ksx_array_entity_t));
    data->entities->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_entities);
    data->entities->data = ks_alloc(root_stream->config, sizeof(ksx_entity_t*) * data->entities->size);
    KS_CHECK_DATA(HANDLE(data->entities) = ks_handle_create(stream, data->entities, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_entity_t*), 0, 0));
    for (i = 0; i < data->entities->size; i++)
    {
        KS_CHECK_DATA(data->entities->data[i] = ksx_read_entity_t(root_stream, root_data, data, stream, i));
    }
    /* Array (repeat-expr) */
    data->entity_polylinks = ks_alloc(root_stream->config, sizeof(ksx_array_entity_polylink_t));
    data->entity_polylinks->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_entity_polylinks);
    data->entity_polylinks->data = ks_alloc(root_stream->config, sizeof(ksx_entity_polylink_t*) * data->entity_polylinks->size);
    KS_CHECK_DATA(HANDLE(data->entity_polylinks) = ks_handle_create(stream, data->entity_polylinks, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_entity_polylink_t*), 0, 0));
    for (i = 0; i < data->entity_polylinks->size; i++)
    {
        KS_CHECK_DATA(data->entity_polylinks->data[i] = ksx_read_entity_polylink_t(root_stream, root_data, data, stream));
    }
    KS_CHECK_DATA(_raw_entity_polylink_data1 = ks_stream_read_bytes(stream, (FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_entity_polylink_data1_segments) * 2)));
    /* Subtype with substream */
    _io_entity_polylink_data1 = ks_stream_create_from_bytes(_raw_entity_polylink_data1);
    KS_CHECK_DATA(data->entity_polylink_data1 = ksx_read_entity_polylink_data1_t(root_stream, root_data, data, _io_entity_polylink_data1));
    KS_CHECK_DATA(_raw_entity_polylink_data2 = ks_stream_read_bytes(stream, (FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_entity_polylink_data2_segments) * 4)));
    /* Subtype with substream */
    _io_entity_polylink_data2 = ks_stream_create_from_bytes(_raw_entity_polylink_data2);
    KS_CHECK_DATA(data->entity_polylink_data2 = ksx_read_entity_polylink_data2_t(root_stream, root_data, data, _io_entity_polylink_data2));
    KS_CHECK_DATA(_raw_entity_data = ks_stream_read_bytes(stream, FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, len_entity_data)));
    /* Subtype with substream */
    _io_entity_data = ks_stream_create_from_bytes(_raw_entity_data);
    KS_CHECK_DATA(data->entity_data = ksx_read_entity_data_t(root_stream, root_data, data, _io_entity_data));
    KS_CHECK_DATA(_raw_tile_texture_data = ks_stream_read_bytes(stream, FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, len_tile_texture_data)));
    /* Subtype with substream */
    _io_tile_texture_data = ks_stream_create_from_bytes(_raw_tile_texture_data);
    KS_CHECK_DATA(data->tile_texture_data = ksx_read_tile_texture_data_t(root_stream, root_data, data, _io_tile_texture_data));
    KS_CHECK_DATA(_raw_tile_color_data = ks_stream_read_bytes(stream, FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, len_tile_color_data)));
    /* Subtype with substream */
    _io_tile_color_data = ks_stream_create_from_bytes(_raw_tile_color_data);
    KS_CHECK_DATA(data->tile_color_data = ksx_read_tile_color_data_t(root_stream, root_data, data, _io_tile_color_data));
    /* Array (repeat-expr) */
    data->unknown = ks_alloc(root_stream->config, sizeof(ks_array_bytes));
    data->unknown->size = FIELD(FIELD(data, ksx_lev_quake, header), ksx_header_t, num_unknown);
    data->unknown->data = ks_alloc(root_stream->config, sizeof(ks_bytes*) * data->unknown->size);
    KS_CHECK_DATA(HANDLE(data->unknown) = ks_handle_create(stream, data->unknown, KS_TYPE_ARRAY_BYTES, sizeof(ks_bytes*), 0, 0));
    for (i = 0; i < data->unknown->size; i++)
    {
        KS_CHECK_DATA(data->unknown->data[i] = ks_stream_read_bytes(stream, 128));
    }
    KS_CHECK_DATA(data->resources = ksx_read_resources_t(root_stream, root_data, data, stream));
    KS_CHECK_DATA(data->unknown0 = ksx_read_len_and_unknown_t(root_stream, root_data, data, stream));
    KS_CHECK_DATA(data->level_name = ks_string_from_bytes(ks_stream_read_bytes(stream, 32), ks_string_from_cstr(stream->config, "ASCII")));
    /* Array (repeat-expr) */
    data->unknown1 = ks_alloc(root_stream->config, sizeof(ks_array_uint32_t));
    data->unknown1->size = 9;
    data->unknown1->data = ks_alloc(root_stream->config, sizeof(uint32_t) * data->unknown1->size);
    KS_CHECK_DATA(HANDLE(data->unknown1) = ks_handle_create(stream, data->unknown1, KS_TYPE_ARRAY_UINT, 4, 0, 0));
    for (i = 0; i < data->unknown1->size; i++)
    {
        KS_CHECK_DATA(data->unknown1->data[i] = ks_stream_read_u4be(stream));
    }
    KS_CHECK_DATA(data->unknown2 = ksx_read_len_and_unknown_t(root_stream, root_data, data, stream));
    KS_CHECK_DATA(data->unknown3 = ksx_read_len_and_unknown_t(root_stream, root_data, data, stream));
    return data;
}

static ksx_tile_texture_data_t* ksx_read_tile_texture_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_tile_texture_data_t* data = ks_alloc(root_stream->config, sizeof(ksx_tile_texture_data_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_tile_texture_data_t), sizeof(ksx_tile_texture_data_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_tile_texture_data_t_instances(data);
    KS_CHECK_DATA(data->data = ks_stream_read_bytes(stream, FIELD(FIELD(HANDLE(data)->parent, ksx_lev_quake, header), ksx_header_t, len_tile_texture_data)));
    return data;
}

static ksx_entity_data_t* ksx_read_entity_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_entity_data_t* data = ks_alloc(root_stream->config, sizeof(ksx_entity_data_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_entity_data_t), sizeof(ksx_entity_data_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_entity_data_t_instances(data);
    KS_CHECK_DATA(data->data = ks_stream_read_bytes(stream, FIELD(FIELD(HANDLE(data)->parent, ksx_lev_quake, header), ksx_header_t, len_entity_data)));
    return data;
}

static ksx_resource_0x6c_t* ksx_read_resource_0x6c_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_resource_0x6c_t* data = ks_alloc(root_stream->config, sizeof(ksx_resource_0x6c_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_resource_0x6c_t), sizeof(ksx_resource_0x6c_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_resource_0x6c_t_instances(data);
    KS_CHECK_DATA(data->unknown0 = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->len_data = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->data = ks_stream_read_bytes(stream, FIELD(data, ksx_resource_0x6c_t, len_data)));
    return data;
}

static ksx_sector_t* ksx_read_sector_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_sector_t* data = ks_alloc(root_stream->config, sizeof(ksx_sector_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_sector_t), sizeof(ksx_sector_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_sector_t_instances(data);
    /* Array (repeat-expr) */
    data->reserved = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->reserved->size = 2;
    data->reserved->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->reserved->size);
    KS_CHECK_DATA(HANDLE(data->reserved) = ks_handle_create(stream, data->reserved, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->reserved->size; i++)
    {
        KS_CHECK_DATA(data->reserved->data[i] = ks_stream_read_u2be(stream));
    }
    /* Array (repeat-expr) */
    data->position = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->position->size = 3;
    data->position->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->position->size);
    KS_CHECK_DATA(HANDLE(data->position) = ks_handle_create(stream, data->position, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->position->size; i++)
    {
        KS_CHECK_DATA(data->position->data[i] = ks_stream_read_u2be(stream));
    }
    KS_CHECK_DATA(data->distance = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->plane_start_index = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->plane_end_index = ks_stream_read_u2be(stream));
    /* Array (repeat-expr) */
    data->unknown = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->unknown->size = 6;
    data->unknown->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->unknown->size);
    KS_CHECK_DATA(HANDLE(data->unknown) = ks_handle_create(stream, data->unknown, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->unknown->size; i++)
    {
        KS_CHECK_DATA(data->unknown->data[i] = ks_stream_read_u2be(stream));
    }
    return data;
}

static ksx_resources_prefix_t* ksx_read_resources_prefix_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_resources_prefix_t* data = ks_alloc(root_stream->config, sizeof(ksx_resources_prefix_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_resources_prefix_t), sizeof(ksx_resources_prefix_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_resources_prefix_t_instances(data);
    KS_CHECK_DATA(data->num_values = ks_stream_read_u4be(stream));
    /* Array (repeat-expr) */
    data->values = ks_alloc(root_stream->config, sizeof(ks_array_int16_t));
    data->values->size = FIELD(data, ksx_resources_prefix_t, num_values);
    data->values->data = ks_alloc(root_stream->config, sizeof(int16_t) * data->values->size);
    KS_CHECK_DATA(HANDLE(data->values) = ks_handle_create(stream, data->values, KS_TYPE_ARRAY_INT, 2, 0, 0));
    for (i = 0; i < data->values->size; i++)
    {
        KS_CHECK_DATA(data->values->data[i] = ks_stream_read_s2be(stream));
    }
    return data;
}

static ksx_sound_t* ksx_read_sound_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_sound_t* data = ks_alloc(root_stream->config, sizeof(ksx_sound_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_sound_t), sizeof(ksx_sound_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_sound_t_instances(data);
    KS_CHECK_DATA(data->len_samples = ks_stream_read_s4be(stream));
    KS_CHECK_DATA(data->maybe_pitch_adjust = ks_stream_read_s4be(stream));
    KS_CHECK_DATA(data->bits = ks_stream_read_s4be(stream));
    KS_CHECK_DATA(data->loop_point = ks_stream_read_s4be(stream));
    KS_CHECK_DATA(data->samples = ks_stream_read_bytes(stream, FIELD(data, ksx_sound_t, len_samples)));
    return data;
}

static ksx_entity_t* ksx_read_entity_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream, int32_t p_index)
{
    ksx_entity_t* data = ks_alloc(root_stream->config, sizeof(ksx_entity_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_entity_t), sizeof(ksx_entity_t_internal), (ks_usertype_generic*)parent_data));
    data->index = p_index;
    ksx_fill_entity_t_instances(data);
    KS_CHECK_DATA(data->ent_type = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->ofs_entity_data = ks_stream_read_u2be(stream));
    return data;
}

static ksx_resources_t* ksx_read_resources_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_resources_t* data = ks_alloc(root_stream->config, sizeof(ksx_resources_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_resources_t), sizeof(ksx_resources_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_resources_t_instances(data);
    KS_CHECK_DATA(data->prefix = ksx_read_resources_prefix_t(root_stream, root_data, data, stream));
    KS_CHECK_DATA(data->num_sounds = ks_stream_read_u4be(stream));
    /* Array (repeat-expr) */
    data->sounds = ks_alloc(root_stream->config, sizeof(ksx_array_sound_t));
    data->sounds->size = FIELD(data, ksx_resources_t, num_sounds);
    data->sounds->data = ks_alloc(root_stream->config, sizeof(ksx_sound_t*) * data->sounds->size);
    KS_CHECK_DATA(HANDLE(data->sounds) = ks_handle_create(stream, data->sounds, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_sound_t*), 0, 0));
    for (i = 0; i < data->sounds->size; i++)
    {
        KS_CHECK_DATA(data->sounds->data[i] = ksx_read_sound_t(root_stream, root_data, data, stream));
    }
    KS_CHECK_DATA(data->len_palette = ks_stream_read_u4be(stream));
    /* Array (repeat-expr) */
    data->palette = ks_alloc(root_stream->config, sizeof(ksx_array_palette_entry_t));
    data->palette->size = ks_div(FIELD(data, ksx_resources_t, len_palette), 2);
    data->palette->data = ks_alloc(root_stream->config, sizeof(ksx_palette_entry_t*) * data->palette->size);
    KS_CHECK_DATA(HANDLE(data->palette) = ks_handle_create(stream, data->palette, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_palette_entry_t*), 0, 0));
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_DATA(data->palette->data[i] = ksx_read_palette_entry_t(root_stream, root_data, data, stream));
    }
    KS_CHECK_DATA(data->num_resources = ks_stream_read_u4be(stream));
    /* Array (repeat-expr) */
    data->resources = ks_alloc(root_stream->config, sizeof(ksx_array_resource_t));
    data->resources->size = FIELD(data, ksx_resources_t, num_resources);
    data->resources->data = ks_alloc(root_stream->config, sizeof(ksx_resource_t*) * data->resources->size);
    KS_CHECK_DATA(HANDLE(data->resources) = ks_handle_create(stream, data->resources, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_resource_t*), 0, 0));
    for (i = 0; i < data->resources->size; i++)
    {
        KS_CHECK_DATA(data->resources->data[i] = ksx_read_resource_t(root_stream, root_data, data, stream));
    }
    return data;
}

static ksx_vertex_t* ksx_read_vertex_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_vertex_t* data = ks_alloc(root_stream->config, sizeof(ksx_vertex_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_vertex_t), sizeof(ksx_vertex_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_vertex_t_instances(data);
    /* Array (repeat-expr) */
    data->coords = ks_alloc(root_stream->config, sizeof(ks_array_int16_t));
    data->coords->size = 3;
    data->coords->data = ks_alloc(root_stream->config, sizeof(int16_t) * data->coords->size);
    KS_CHECK_DATA(HANDLE(data->coords) = ks_handle_create(stream, data->coords, KS_TYPE_ARRAY_INT, 2, 0, 0));
    for (i = 0; i < data->coords->size; i++)
    {
        KS_CHECK_DATA(data->coords->data[i] = ks_stream_read_s2be(stream));
    }
    KS_CHECK_DATA(data->color_lookup = ks_stream_read_u1(stream));
    KS_CHECK_DATA(data->reserved = ks_stream_read_u1(stream));
    return data;
}

static ksx_header_t* ksx_read_header_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_header_t* data = ks_alloc(root_stream->config, sizeof(ksx_header_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_header_t), sizeof(ksx_header_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_header_t_instances(data);
    KS_CHECK_DATA(data->unknown_01 = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->unknown_02 = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_sectors = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_planes = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_vertices = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_quads = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->len_tile_texture_data = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_tiles = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->len_tile_color_data = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_entities = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->len_entity_data = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_entity_polylinks = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_entity_polylink_data1_segments = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_entity_polylink_data2_segments = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->num_unknown = ks_stream_read_u4be(stream));
    return data;
}

static ksx_resource_0x34_t* ksx_read_resource_0x34_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_resource_0x34_t* data = ks_alloc(root_stream->config, sizeof(ksx_resource_0x34_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_resource_0x34_t), sizeof(ksx_resource_0x34_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_resource_0x34_t_instances(data);
    KS_CHECK_DATA(data->unknown0 = ks_stream_read_u2be(stream));
    /* Array (repeat-expr) */
    data->bitmap = ks_alloc(root_stream->config, sizeof(ks_array_uint64_t));
    data->bitmap->size = 1024;
    data->bitmap->data = ks_alloc(root_stream->config, sizeof(uint64_t) * data->bitmap->size);
    KS_CHECK_DATA(HANDLE(data->bitmap) = ks_handle_create(stream, data->bitmap, KS_TYPE_ARRAY_UINT, 8, 0, 0));
    for (i = 0; i < data->bitmap->size; i++)
    {
        KS_CHECK_DATA(data->bitmap->data[i] = ks_stream_read_bits_be(stream, 8));
    }
    return data;
}

static ksx_entity_polymover_t* ksx_read_entity_polymover_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_entity_polymover_t* data = ks_alloc(root_stream->config, sizeof(ksx_entity_polymover_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_entity_polymover_t), sizeof(ksx_entity_polymover_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_entity_polymover_t_instances(data);
    KS_CHECK_DATA(data->polylink_id = ks_stream_read_s2be(stream));
    /* Array (repeat-expr) */
    data->data = ks_alloc(root_stream->config, sizeof(ks_array_int16_t));
    data->data->size = 20;
    data->data->data = ks_alloc(root_stream->config, sizeof(int16_t) * data->data->size);
    KS_CHECK_DATA(HANDLE(data->data) = ks_handle_create(stream, data->data, KS_TYPE_ARRAY_INT, 2, 0, 0));
    for (i = 0; i < data->data->size; i++)
    {
        KS_CHECK_DATA(data->data->data[i] = ks_stream_read_s2be(stream));
    }
    return data;
}

static ksx_len_and_unknown_t* ksx_read_len_and_unknown_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_len_and_unknown_t* data = ks_alloc(root_stream->config, sizeof(ksx_len_and_unknown_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_len_and_unknown_t), sizeof(ksx_len_and_unknown_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_len_and_unknown_t_instances(data);
    KS_CHECK_DATA(data->len_data = ks_stream_read_u4be(stream));
    KS_CHECK_DATA(data->data = ks_stream_read_bytes(stream, FIELD(data, ksx_len_and_unknown_t, len_data)));
    return data;
}

static ksx_quad_t* ksx_read_quad_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_quad_t* data = ks_alloc(root_stream->config, sizeof(ksx_quad_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_quad_t), sizeof(ksx_quad_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_quad_t_instances(data);
    /* Array (repeat-expr) */
    data->vertex_indices = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->vertex_indices->size = 4;
    data->vertex_indices->data = ks_alloc(root_stream->config, sizeof(uint8_t) * data->vertex_indices->size);
    KS_CHECK_DATA(HANDLE(data->vertex_indices) = ks_handle_create(stream, data->vertex_indices, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    for (i = 0; i < data->vertex_indices->size; i++)
    {
        KS_CHECK_DATA(data->vertex_indices->data[i] = ks_stream_read_u1(stream));
    }
    KS_CHECK_DATA(data->texture_index = ks_stream_read_u1(stream));
    return data;
}

static ksx_texture_t* ksx_read_texture_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_texture_t* data = ks_alloc(root_stream->config, sizeof(ksx_texture_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_texture_t), sizeof(ksx_texture_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_texture_t_instances(data);
    /* Array (repeat-expr) */
    data->palette = ks_alloc(root_stream->config, sizeof(ksx_array_palette_entry_t));
    data->palette->size = 16;
    data->palette->data = ks_alloc(root_stream->config, sizeof(ksx_palette_entry_t*) * data->palette->size);
    KS_CHECK_DATA(HANDLE(data->palette) = ks_handle_create(stream, data->palette, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_palette_entry_t*), 0, 0));
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_DATA(data->palette->data[i] = ksx_read_palette_entry_t(root_stream, root_data, data, stream));
    }
    /* Array (repeat-expr) */
    data->bitmap = ks_alloc(root_stream->config, sizeof(ks_array_uint64_t));
    data->bitmap->size = (64 * 64);
    data->bitmap->data = ks_alloc(root_stream->config, sizeof(uint64_t) * data->bitmap->size);
    KS_CHECK_DATA(HANDLE(data->bitmap) = ks_handle_create(stream, data->bitmap, KS_TYPE_ARRAY_UINT, 8, 0, 0));
    for (i = 0; i < data->bitmap->size; i++)
    {
        KS_CHECK_DATA(data->bitmap->data[i] = ks_stream_read_bits_be(stream, 4));
    }
    return data;
}

static ksx_palette_entry_t* ksx_read_palette_entry_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_palette_entry_t* data = ks_alloc(root_stream->config, sizeof(ksx_palette_entry_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_palette_entry_t), sizeof(ksx_palette_entry_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_palette_entry_t_instances(data);
    KS_CHECK_DATA(data->a = ks_stream_read_bits_be(stream, 1));
    KS_CHECK_DATA(data->b = ks_stream_read_bits_be(stream, 5));
    KS_CHECK_DATA(data->g = ks_stream_read_bits_be(stream, 5));
    KS_CHECK_DATA(data->r = ks_stream_read_bits_be(stream, 5));
    return data;
}

static ksx_entity_polylink_data1_t* ksx_read_entity_polylink_data1_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_entity_polylink_data1_t* data = ks_alloc(root_stream->config, sizeof(ksx_entity_polylink_data1_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_entity_polylink_data1_t), sizeof(ksx_entity_polylink_data1_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_entity_polylink_data1_t_instances(data);
    /* Array (repeat-eos) */
    data->data = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->data->size = 0;
    data->data->data = 0;
    KS_CHECK_DATA(HANDLE(data->data) = ks_handle_create(stream, data->data, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    {
        while (!ks_stream_is_eof(stream)) {
        i = data->data->size;
            data->data->size++;
            data->data->data = ks_realloc(root_stream->config, data->data->data, sizeof(uint8_t) * data->data->size);
            memset(data->data->data + data->data->size - 1, 0, sizeof(uint8_t));
            KS_CHECK_DATA(data->data->data[i] = ks_stream_read_u1(stream));
        }
    }
    return data;
}

static ksx_entity_polylink_data2_t* ksx_read_entity_polylink_data2_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_entity_polylink_data2_t* data = ks_alloc(root_stream->config, sizeof(ksx_entity_polylink_data2_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_entity_polylink_data2_t), sizeof(ksx_entity_polylink_data2_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_entity_polylink_data2_t_instances(data);
    /* Array (repeat-eos) */
    data->data = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->data->size = 0;
    data->data->data = 0;
    KS_CHECK_DATA(HANDLE(data->data) = ks_handle_create(stream, data->data, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    {
        while (!ks_stream_is_eof(stream)) {
        i = data->data->size;
            data->data->size++;
            data->data->data = ks_realloc(root_stream->config, data->data->data, sizeof(uint8_t) * data->data->size);
            memset(data->data->data + data->data->size - 1, 0, sizeof(uint8_t));
            KS_CHECK_DATA(data->data->data[i] = ks_stream_read_u1(stream));
        }
    }
    return data;
}

static ksx_resource_t* ksx_read_resource_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_resource_t* data = ks_alloc(root_stream->config, sizeof(ksx_resource_t));
    ksx_resource_t_internal* internal;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_resource_t), sizeof(ksx_resource_t_internal), (ks_usertype_generic*)parent_data));
    internal = (ksx_resource_t_internal*)HANDLE(data)->internal_read;
    ksx_fill_resource_t_instances(data);
    KS_CHECK_DATA(data->flags = ks_stream_read_u1(stream));
    KS_CHECK_DATA(data->resource_type = ks_stream_read_u1(stream));
    data->_is_valid_data = 0;
    switch (FIELD(data, ksx_resource_t, resource_type)) {
    case 130: {
        data->_is_valid_data = 1;
        KS_CHECK_DATA(data->data = (ks_usertype_generic*)ksx_read_texture_t(root_stream, root_data, data, stream));
        internal->_read_instances_data = (void*)ksx_read_texture_t_instances;
        break;
    }
    case 52: {
        data->_is_valid_data = 1;
        KS_CHECK_DATA(data->data = (ks_usertype_generic*)ksx_read_resource_0x34_t(root_stream, root_data, data, stream));
        internal->_read_instances_data = (void*)ksx_read_resource_0x34_t_instances;
        break;
    }
    case 106: {
        data->_is_valid_data = 1;
        KS_CHECK_DATA(data->data = (ks_usertype_generic*)ksx_read_resource_0x6a_t(root_stream, root_data, data, stream));
        internal->_read_instances_data = (void*)ksx_read_resource_0x6a_t_instances;
        break;
    }
    case 108: {
        data->_is_valid_data = 1;
        KS_CHECK_DATA(data->data = (ks_usertype_generic*)ksx_read_resource_0x6c_t(root_stream, root_data, data, stream));
        internal->_read_instances_data = (void*)ksx_read_resource_0x6c_t_instances;
        break;
    }
    }
    return data;
}

static ksx_tile_t* ksx_read_tile_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_tile_t* data = ks_alloc(root_stream->config, sizeof(ksx_tile_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_tile_t), sizeof(ksx_tile_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_tile_t_instances(data);
    KS_CHECK_DATA(data->ofs_texture_data = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->width = ks_stream_read_u1(stream));
    KS_CHECK_DATA(data->height = ks_stream_read_u1(stream));
    KS_CHECK_DATA(data->ofs_color_data = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->unknown = ks_stream_read_u2be(stream));
    /* Array (repeat-expr) */
    data->horizontal_vector = ks_alloc(root_stream->config, sizeof(ks_array_int32_t));
    data->horizontal_vector->size = 3;
    data->horizontal_vector->data = ks_alloc(root_stream->config, sizeof(int32_t) * data->horizontal_vector->size);
    KS_CHECK_DATA(HANDLE(data->horizontal_vector) = ks_handle_create(stream, data->horizontal_vector, KS_TYPE_ARRAY_INT, 4, 0, 0));
    for (i = 0; i < data->horizontal_vector->size; i++)
    {
        KS_CHECK_DATA(data->horizontal_vector->data[i] = ks_stream_read_s4be(stream));
    }
    /* Array (repeat-expr) */
    data->vertical_vector = ks_alloc(root_stream->config, sizeof(ks_array_int32_t));
    data->vertical_vector->size = 3;
    data->vertical_vector->data = ks_alloc(root_stream->config, sizeof(int32_t) * data->vertical_vector->size);
    KS_CHECK_DATA(HANDLE(data->vertical_vector) = ks_handle_create(stream, data->vertical_vector, KS_TYPE_ARRAY_INT, 4, 0, 0));
    for (i = 0; i < data->vertical_vector->size; i++)
    {
        KS_CHECK_DATA(data->vertical_vector->data[i] = ks_stream_read_s4be(stream));
    }
    /* Array (repeat-expr) */
    data->base_vector = ks_alloc(root_stream->config, sizeof(ks_array_int32_t));
    data->base_vector->size = 3;
    data->base_vector->data = ks_alloc(root_stream->config, sizeof(int32_t) * data->base_vector->size);
    KS_CHECK_DATA(HANDLE(data->base_vector) = ks_handle_create(stream, data->base_vector, KS_TYPE_ARRAY_INT, 4, 0, 0));
    for (i = 0; i < data->base_vector->size; i++)
    {
        KS_CHECK_DATA(data->base_vector->data[i] = ks_stream_read_s4be(stream));
    }
    return data;
}

static ksx_entity_polylink_t* ksx_read_entity_polylink_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_entity_polylink_t* data = ks_alloc(root_stream->config, sizeof(ksx_entity_polylink_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_entity_polylink_t), sizeof(ksx_entity_polylink_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_entity_polylink_t_instances(data);
    KS_CHECK_DATA(data->lead = ks_stream_read_u2be(stream));
    /* Array (repeat-expr) */
    data->ofs_entity_polylink_data1 = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->ofs_entity_polylink_data1->size = 2;
    data->ofs_entity_polylink_data1->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->ofs_entity_polylink_data1->size);
    KS_CHECK_DATA(HANDLE(data->ofs_entity_polylink_data1) = ks_handle_create(stream, data->ofs_entity_polylink_data1, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->ofs_entity_polylink_data1->size; i++)
    {
        KS_CHECK_DATA(data->ofs_entity_polylink_data1->data[i] = ks_stream_read_u2be(stream));
    }
    /* Array (repeat-expr) */
    data->ofs_entity_polylink_data2 = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->ofs_entity_polylink_data2->size = 2;
    data->ofs_entity_polylink_data2->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->ofs_entity_polylink_data2->size);
    KS_CHECK_DATA(HANDLE(data->ofs_entity_polylink_data2) = ks_handle_create(stream, data->ofs_entity_polylink_data2, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->ofs_entity_polylink_data2->size; i++)
    {
        KS_CHECK_DATA(data->ofs_entity_polylink_data2->data[i] = ks_stream_read_u2be(stream));
    }
    KS_CHECK_DATA(data->unknown = ks_stream_read_u2be(stream));
    /* Array (repeat-expr) */
    data->reserved = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->reserved->size = 3;
    data->reserved->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->reserved->size);
    KS_CHECK_DATA(HANDLE(data->reserved) = ks_handle_create(stream, data->reserved, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->reserved->size; i++)
    {
        KS_CHECK_DATA(data->reserved->data[i] = ks_stream_read_u2be(stream));
    }
    return data;
}

static ksx_plane_t* ksx_read_plane_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_plane_t* data = ks_alloc(root_stream->config, sizeof(ksx_plane_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_plane_t), sizeof(ksx_plane_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_plane_t_instances(data);
    /* Array (repeat-expr) */
    data->vertex_indices = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->vertex_indices->size = 4;
    data->vertex_indices->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->vertex_indices->size);
    KS_CHECK_DATA(HANDLE(data->vertex_indices) = ks_handle_create(stream, data->vertex_indices, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->vertex_indices->size; i++)
    {
        KS_CHECK_DATA(data->vertex_indices->data[i] = ks_stream_read_u2be(stream));
    }
    KS_CHECK_DATA(data->sector_index = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->flags = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->collision_flags = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->tile_index = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->unknown_index = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->quad_start_index = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->quad_end_index = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->vertex_start_index = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->vertex_end_index = ks_stream_read_u2be(stream));
    /* Array (repeat-expr) */
    data->normal = ks_alloc(root_stream->config, sizeof(ks_array_int16_t));
    data->normal->size = 3;
    data->normal->data = ks_alloc(root_stream->config, sizeof(int16_t) * data->normal->size);
    KS_CHECK_DATA(HANDLE(data->normal) = ks_handle_create(stream, data->normal, KS_TYPE_ARRAY_INT, 2, 0, 0));
    for (i = 0; i < data->normal->size; i++)
    {
        KS_CHECK_DATA(data->normal->data[i] = ks_stream_read_s2be(stream));
    }
    KS_CHECK_DATA(data->distance = ks_stream_read_s2be(stream));
    KS_CHECK_DATA(data->angle = ks_stream_read_s2be(stream));
    /* Array (repeat-expr) */
    data->reserved = ks_alloc(root_stream->config, sizeof(ks_array_uint16_t));
    data->reserved->size = 2;
    data->reserved->data = ks_alloc(root_stream->config, sizeof(uint16_t) * data->reserved->size);
    KS_CHECK_DATA(HANDLE(data->reserved) = ks_handle_create(stream, data->reserved, KS_TYPE_ARRAY_UINT, 2, 0, 0));
    for (i = 0; i < data->reserved->size; i++)
    {
        KS_CHECK_DATA(data->reserved->data[i] = ks_stream_read_u2be(stream));
    }
    return data;
}

static ksx_sky_bitmap_t* ksx_read_sky_bitmap_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_sky_bitmap_t* data = ks_alloc(root_stream->config, sizeof(ksx_sky_bitmap_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_sky_bitmap_t), sizeof(ksx_sky_bitmap_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_sky_bitmap_t_instances(data);
    KS_CHECK_DATA(data->image = ks_stream_read_bytes(stream, 2048));
    return data;
}

static ksx_entity_generic_t* ksx_read_entity_generic_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_entity_generic_t* data = ks_alloc(root_stream->config, sizeof(ksx_entity_generic_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_entity_generic_t), sizeof(ksx_entity_generic_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_entity_generic_t_instances(data);
    KS_CHECK_DATA(data->start = ks_stream_read_s2be(stream));
    /* Array (repeat-expr) */
    data->coords = ks_alloc(root_stream->config, sizeof(ks_array_int16_t));
    data->coords->size = 3;
    data->coords->data = ks_alloc(root_stream->config, sizeof(int16_t) * data->coords->size);
    KS_CHECK_DATA(HANDLE(data->coords) = ks_handle_create(stream, data->coords, KS_TYPE_ARRAY_INT, 2, 0, 0));
    for (i = 0; i < data->coords->size; i++)
    {
        KS_CHECK_DATA(data->coords->data[i] = ks_stream_read_s2be(stream));
    }
    return data;
}

static ksx_resource_0x6a_t* ksx_read_resource_0x6a_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_resource_0x6a_t* data = ks_alloc(root_stream->config, sizeof(ksx_resource_0x6a_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_resource_0x6a_t), sizeof(ksx_resource_0x6a_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_resource_0x6a_t_instances(data);
    KS_CHECK_DATA(data->unknown0 = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->len_data = ks_stream_read_u2be(stream));
    KS_CHECK_DATA(data->data = ks_stream_read_bytes(stream, FIELD(data, ksx_resource_0x6a_t, len_data)));
    return data;
}

static ksx_sky_data_t* ksx_read_sky_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_sky_data_t* data = ks_alloc(root_stream->config, sizeof(ksx_sky_data_t));
    int64_t i;

    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_sky_data_t), sizeof(ksx_sky_data_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_sky_data_t_instances(data);
    /* Array (repeat-expr) */
    data->palette = ks_alloc(root_stream->config, sizeof(ksx_array_palette_entry_t));
    data->palette->size = 16;
    data->palette->data = ks_alloc(root_stream->config, sizeof(ksx_palette_entry_t*) * data->palette->size);
    KS_CHECK_DATA(HANDLE(data->palette) = ks_handle_create(stream, data->palette, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_palette_entry_t*), 0, 0));
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_DATA(data->palette->data[i] = ksx_read_palette_entry_t(root_stream, root_data, data, stream));
    }
    /* Array (repeat-expr) */
    data->bitmaps = ks_alloc(root_stream->config, sizeof(ksx_array_sky_bitmap_t));
    data->bitmaps->size = 64;
    data->bitmaps->data = ks_alloc(root_stream->config, sizeof(ksx_sky_bitmap_t*) * data->bitmaps->size);
    KS_CHECK_DATA(HANDLE(data->bitmaps) = ks_handle_create(stream, data->bitmaps, KS_TYPE_ARRAY_USERTYPE, sizeof(ksx_sky_bitmap_t*), 0, 0));
    for (i = 0; i < data->bitmaps->size; i++)
    {
        KS_CHECK_DATA(data->bitmaps->data[i] = ksx_read_sky_bitmap_t(root_stream, root_data, data, stream));
    }
    return data;
}

static ksx_tile_color_data_t* ksx_read_tile_color_data_t(ks_stream* root_stream, ksx_lev_quake* root_data, void* parent_data, ks_stream* stream)
{
    ksx_tile_color_data_t* data = ks_alloc(root_stream->config, sizeof(ksx_tile_color_data_t));
    KS_CHECK_DATA(HANDLE(data) = ks_handle_create(stream, data, KS_TYPE_USERTYPE, sizeof(ksx_tile_color_data_t), sizeof(ksx_tile_color_data_t_internal), (ks_usertype_generic*)parent_data));
    ksx_fill_tile_color_data_t_instances(data);
    KS_CHECK_DATA(data->data = ks_stream_read_bytes(stream, FIELD(FIELD(HANDLE(data)->parent, ksx_lev_quake, header), ksx_header_t, len_tile_color_data)));
    return data;
}


static void ksx_read_entity_t_instance_get_entity_data(ks_stream* root_stream, ksx_lev_quake* root_data, ks_stream* stream, ksx_entity_t* data)
{
    int64_t _old_pos = ks_stream_get_pos(stream);
    ks_stream* io;
    ksx_entity_t_internal* internal;

    internal = (ksx_entity_t_internal*)HANDLE(data)->internal_read;
    if (internal->_flag_get_entity_data)
        return;
    data->_is_valid_get_entity_data = 0;
    if (FIELD(data, ksx_entity_t, ofs_entity_data) < FIELD(FIELD(root_data, ksx_lev_quake, header), ksx_header_t, len_entity_data)) {
        data->_is_valid_get_entity_data = 1;
        io = HANDLE(FIELD(root_data, ksx_lev_quake, entity_data))->stream;
        KS_CHECK_VOID(ks_stream_seek(io, FIELD(data, ksx_entity_t, ofs_entity_data)));
        switch (FIELD(data, ksx_entity_t, ent_type)) {
        case 146: {
            KS_CHECK_VOID(data->get_entity_data = (ks_usertype_generic*)ksx_read_entity_polymover_t(root_stream, root_data, data, io));
            internal->_read_instances_get_entity_data = (void*)ksx_read_entity_polymover_t_instances;
            break;
        }
        default: {
            KS_CHECK_VOID(data->get_entity_data = (ks_usertype_generic*)ksx_read_entity_generic_t(root_stream, root_data, data, io));
            internal->_read_instances_get_entity_data = (void*)ksx_read_entity_generic_t_instances;
            break;
        }
        }
        internal->_flag_get_entity_data = 1;
    }
    ks_stream_seek(stream, _old_pos);
}

static void ksx_read_tile_t_instance_get_color_data(ks_stream* root_stream, ksx_lev_quake* root_data, ks_stream* stream, ksx_tile_t* data)
{
    int64_t _old_pos = ks_stream_get_pos(stream);
    ks_stream* io;
    int64_t i;
    ksx_tile_t_internal* internal;

    internal = (ksx_tile_t_internal*)HANDLE(data)->internal_read;
    if (internal->_flag_get_color_data)
        return;
    io = HANDLE(FIELD(root_data, ksx_lev_quake, tile_color_data))->stream;
    KS_CHECK_VOID(ks_stream_seek(io, FIELD(data, ksx_tile_t, ofs_color_data)));
    /* Array (repeat-expr) */
    data->get_color_data = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->get_color_data->size = ((FIELD(data, ksx_tile_t, width) + 1) * (FIELD(data, ksx_tile_t, height) + 1));
    data->get_color_data->data = ks_alloc(root_stream->config, sizeof(uint8_t) * data->get_color_data->size);
    KS_CHECK_VOID(HANDLE(data->get_color_data) = ks_handle_create(stream, data->get_color_data, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    for (i = 0; i < data->get_color_data->size; i++)
    {
        KS_CHECK_VOID(data->get_color_data->data[i] = ks_stream_read_u1(io));
    }
    internal->_flag_get_color_data = 1;
    ks_stream_seek(stream, _old_pos);
}

static void ksx_read_tile_t_instance_get_tile_texture_data(ks_stream* root_stream, ksx_lev_quake* root_data, ks_stream* stream, ksx_tile_t* data)
{
    int64_t _old_pos = ks_stream_get_pos(stream);
    ks_stream* io;
    int64_t i;
    ksx_tile_t_internal* internal;

    internal = (ksx_tile_t_internal*)HANDLE(data)->internal_read;
    if (internal->_flag_get_tile_texture_data)
        return;
    io = HANDLE(FIELD(root_data, ksx_lev_quake, tile_texture_data))->stream;
    KS_CHECK_VOID(ks_stream_seek(io, FIELD(data, ksx_tile_t, ofs_texture_data)));
    /* Array (repeat-expr) */
    data->get_tile_texture_data = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->get_tile_texture_data->size = ((FIELD(data, ksx_tile_t, height) * FIELD(data, ksx_tile_t, width)) * 2);
    data->get_tile_texture_data->data = ks_alloc(root_stream->config, sizeof(uint8_t) * data->get_tile_texture_data->size);
    KS_CHECK_VOID(HANDLE(data->get_tile_texture_data) = ks_handle_create(stream, data->get_tile_texture_data, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    for (i = 0; i < data->get_tile_texture_data->size; i++)
    {
        KS_CHECK_VOID(data->get_tile_texture_data->data[i] = ks_stream_read_u1(io));
    }
    internal->_flag_get_tile_texture_data = 1;
    ks_stream_seek(stream, _old_pos);
}

static void ksx_read_entity_polylink_t_instance_getdata1(ks_stream* root_stream, ksx_lev_quake* root_data, ks_stream* stream, ksx_entity_polylink_t* data)
{
    int64_t _old_pos = ks_stream_get_pos(stream);
    ks_stream* io;
    int64_t i;
    ksx_entity_polylink_t_internal* internal;

    internal = (ksx_entity_polylink_t_internal*)HANDLE(data)->internal_read;
    if (internal->_flag_getdata1)
        return;
    io = HANDLE(FIELD(root_data, ksx_lev_quake, entity_polylink_data1))->stream;
    KS_CHECK_VOID(ks_stream_seek(io, (FIELD(data, ksx_entity_polylink_t, ofs_entity_polylink_data1)->data[0] * 2)));
    /* Array (repeat-expr) */
    data->getdata1 = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->getdata1->size = (((FIELD(data, ksx_entity_polylink_t, ofs_entity_polylink_data1)->data[1] - FIELD(data, ksx_entity_polylink_t, ofs_entity_polylink_data1)->data[0]) + 1) * 2);
    data->getdata1->data = ks_alloc(root_stream->config, sizeof(uint8_t) * data->getdata1->size);
    KS_CHECK_VOID(HANDLE(data->getdata1) = ks_handle_create(stream, data->getdata1, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    for (i = 0; i < data->getdata1->size; i++)
    {
        KS_CHECK_VOID(data->getdata1->data[i] = ks_stream_read_u1(io));
    }
    internal->_flag_getdata1 = 1;
    ks_stream_seek(stream, _old_pos);
}

static void ksx_read_entity_polylink_t_instance_getdata2(ks_stream* root_stream, ksx_lev_quake* root_data, ks_stream* stream, ksx_entity_polylink_t* data)
{
    int64_t _old_pos = ks_stream_get_pos(stream);
    ks_stream* io;
    int64_t i;
    ksx_entity_polylink_t_internal* internal;

    internal = (ksx_entity_polylink_t_internal*)HANDLE(data)->internal_read;
    if (internal->_flag_getdata2)
        return;
    io = HANDLE(FIELD(root_data, ksx_lev_quake, entity_polylink_data2))->stream;
    KS_CHECK_VOID(ks_stream_seek(io, (FIELD(data, ksx_entity_polylink_t, ofs_entity_polylink_data2)->data[0] * 4)));
    /* Array (repeat-expr) */
    data->getdata2 = ks_alloc(root_stream->config, sizeof(ks_array_uint8_t));
    data->getdata2->size = (((FIELD(data, ksx_entity_polylink_t, ofs_entity_polylink_data2)->data[1] - FIELD(data, ksx_entity_polylink_t, ofs_entity_polylink_data2)->data[0]) + 1) * 4);
    data->getdata2->data = ks_alloc(root_stream->config, sizeof(uint8_t) * data->getdata2->size);
    KS_CHECK_VOID(HANDLE(data->getdata2) = ks_handle_create(stream, data->getdata2, KS_TYPE_ARRAY_UINT, 1, 0, 0));
    for (i = 0; i < data->getdata2->size; i++)
    {
        KS_CHECK_VOID(data->getdata2->data[i] = ks_stream_read_u1(io));
    }
    internal->_flag_getdata2 = 1;
    ks_stream_seek(stream, _old_pos);
}
static ks_bytes* ksx_get_tile_texture_data_t_data(ksx_tile_texture_data_t* data)
{
    return data->data;
}

static ks_bytes* ksx_get_entity_data_t_data(ksx_entity_data_t* data)
{
    return data->data;
}

static uint16_t ksx_get_resource_0x6c_t_unknown0(ksx_resource_0x6c_t* data)
{
    return data->unknown0;
}

static uint16_t ksx_get_resource_0x6c_t_len_data(ksx_resource_0x6c_t* data)
{
    return data->len_data;
}

static ks_bytes* ksx_get_resource_0x6c_t_data(ksx_resource_0x6c_t* data)
{
    return data->data;
}

static ks_array_uint16_t* ksx_get_sector_t_reserved(ksx_sector_t* data)
{
    return data->reserved;
}

static ks_array_uint16_t* ksx_get_sector_t_position(ksx_sector_t* data)
{
    return data->position;
}

static uint16_t ksx_get_sector_t_distance(ksx_sector_t* data)
{
    return data->distance;
}

static uint16_t ksx_get_sector_t_plane_start_index(ksx_sector_t* data)
{
    return data->plane_start_index;
}

static uint16_t ksx_get_sector_t_plane_end_index(ksx_sector_t* data)
{
    return data->plane_end_index;
}

static ks_array_uint16_t* ksx_get_sector_t_unknown(ksx_sector_t* data)
{
    return data->unknown;
}

static uint32_t ksx_get_resources_prefix_t_num_values(ksx_resources_prefix_t* data)
{
    return data->num_values;
}

static ks_array_int16_t* ksx_get_resources_prefix_t_values(ksx_resources_prefix_t* data)
{
    return data->values;
}

static int32_t ksx_get_sound_t_len_samples(ksx_sound_t* data)
{
    return data->len_samples;
}

static int32_t ksx_get_sound_t_maybe_pitch_adjust(ksx_sound_t* data)
{
    return data->maybe_pitch_adjust;
}

static int32_t ksx_get_sound_t_bits(ksx_sound_t* data)
{
    return data->bits;
}

static int32_t ksx_get_sound_t_loop_point(ksx_sound_t* data)
{
    return data->loop_point;
}

static ks_bytes* ksx_get_sound_t_samples(ksx_sound_t* data)
{
    return data->samples;
}

static ks_usertype_generic* ksx_get_entity_t_get_entity_data(ksx_entity_t* data)
{
    ks_stream* stream = HANDLE(data)->stream;
    KS_CHECK(ksx_read_entity_t_instance_get_entity_data(ks_stream_get_root(stream), (void*)ks_usertype_get_root((void*)data), stream, data), data->get_entity_data);
    return data->get_entity_data;
}

static uint16_t ksx_get_entity_t_ent_type(ksx_entity_t* data)
{
    return data->ent_type;
}

static uint16_t ksx_get_entity_t_ofs_entity_data(ksx_entity_t* data)
{
    return data->ofs_entity_data;
}

static int32_t ksx_get_entity_t_index(ksx_entity_t* data)
{
    return data->index;
}

static ksx_resources_prefix_t* ksx_get_resources_t_prefix(ksx_resources_t* data)
{
    return (ksx_resources_prefix_t*)data->prefix;
}

static uint32_t ksx_get_resources_t_num_sounds(ksx_resources_t* data)
{
    return data->num_sounds;
}

static ksx_array_sound_t* ksx_get_resources_t_sounds(ksx_resources_t* data)
{
    return data->sounds;
}

static uint32_t ksx_get_resources_t_len_palette(ksx_resources_t* data)
{
    return data->len_palette;
}

static ksx_array_palette_entry_t* ksx_get_resources_t_palette(ksx_resources_t* data)
{
    return data->palette;
}

static uint32_t ksx_get_resources_t_num_resources(ksx_resources_t* data)
{
    return data->num_resources;
}

static ksx_array_resource_t* ksx_get_resources_t_resources(ksx_resources_t* data)
{
    return data->resources;
}

static ks_array_int16_t* ksx_get_vertex_t_coords(ksx_vertex_t* data)
{
    return data->coords;
}

static uint8_t ksx_get_vertex_t_color_lookup(ksx_vertex_t* data)
{
    return data->color_lookup;
}

static uint8_t ksx_get_vertex_t_reserved(ksx_vertex_t* data)
{
    return data->reserved;
}

static uint32_t ksx_get_header_t_unknown_01(ksx_header_t* data)
{
    return data->unknown_01;
}

static uint32_t ksx_get_header_t_unknown_02(ksx_header_t* data)
{
    return data->unknown_02;
}

static uint32_t ksx_get_header_t_num_sectors(ksx_header_t* data)
{
    return data->num_sectors;
}

static uint32_t ksx_get_header_t_num_planes(ksx_header_t* data)
{
    return data->num_planes;
}

static uint32_t ksx_get_header_t_num_vertices(ksx_header_t* data)
{
    return data->num_vertices;
}

static uint32_t ksx_get_header_t_num_quads(ksx_header_t* data)
{
    return data->num_quads;
}

static uint32_t ksx_get_header_t_len_tile_texture_data(ksx_header_t* data)
{
    return data->len_tile_texture_data;
}

static uint32_t ksx_get_header_t_num_tiles(ksx_header_t* data)
{
    return data->num_tiles;
}

static uint32_t ksx_get_header_t_len_tile_color_data(ksx_header_t* data)
{
    return data->len_tile_color_data;
}

static uint32_t ksx_get_header_t_num_entities(ksx_header_t* data)
{
    return data->num_entities;
}

static uint32_t ksx_get_header_t_len_entity_data(ksx_header_t* data)
{
    return data->len_entity_data;
}

static uint32_t ksx_get_header_t_num_entity_polylinks(ksx_header_t* data)
{
    return data->num_entity_polylinks;
}

static uint32_t ksx_get_header_t_num_entity_polylink_data1_segments(ksx_header_t* data)
{
    return data->num_entity_polylink_data1_segments;
}

static uint32_t ksx_get_header_t_num_entity_polylink_data2_segments(ksx_header_t* data)
{
    return data->num_entity_polylink_data2_segments;
}

static uint32_t ksx_get_header_t_num_unknown(ksx_header_t* data)
{
    return data->num_unknown;
}

static uint16_t ksx_get_resource_0x34_t_unknown0(ksx_resource_0x34_t* data)
{
    return data->unknown0;
}

static ks_array_uint64_t* ksx_get_resource_0x34_t_bitmap(ksx_resource_0x34_t* data)
{
    return data->bitmap;
}

static int16_t ksx_get_entity_polymover_t_polylink_id(ksx_entity_polymover_t* data)
{
    return data->polylink_id;
}

static ks_array_int16_t* ksx_get_entity_polymover_t_data(ksx_entity_polymover_t* data)
{
    return data->data;
}

static uint32_t ksx_get_len_and_unknown_t_len_data(ksx_len_and_unknown_t* data)
{
    return data->len_data;
}

static ks_bytes* ksx_get_len_and_unknown_t_data(ksx_len_and_unknown_t* data)
{
    return data->data;
}

static ks_array_uint8_t* ksx_get_quad_t_vertex_indices(ksx_quad_t* data)
{
    return data->vertex_indices;
}

static uint8_t ksx_get_quad_t_texture_index(ksx_quad_t* data)
{
    return data->texture_index;
}

static ksx_array_palette_entry_t* ksx_get_texture_t_palette(ksx_texture_t* data)
{
    return data->palette;
}

static ks_array_uint64_t* ksx_get_texture_t_bitmap(ksx_texture_t* data)
{
    return data->bitmap;
}

static ks_bool ksx_get_palette_entry_t_a(ksx_palette_entry_t* data)
{
    return data->a;
}

static uint64_t ksx_get_palette_entry_t_b(ksx_palette_entry_t* data)
{
    return data->b;
}

static uint64_t ksx_get_palette_entry_t_g(ksx_palette_entry_t* data)
{
    return data->g;
}

static uint64_t ksx_get_palette_entry_t_r(ksx_palette_entry_t* data)
{
    return data->r;
}

static ks_array_uint8_t* ksx_get_entity_polylink_data1_t_data(ksx_entity_polylink_data1_t* data)
{
    return data->data;
}

static ks_array_uint8_t* ksx_get_entity_polylink_data2_t_data(ksx_entity_polylink_data2_t* data)
{
    return data->data;
}

static uint8_t ksx_get_resource_t_flags(ksx_resource_t* data)
{
    return data->flags;
}

static uint8_t ksx_get_resource_t_resource_type(ksx_resource_t* data)
{
    return data->resource_type;
}

static ks_usertype_generic* ksx_get_resource_t_data(ksx_resource_t* data)
{
    return data->data;
}

static ks_array_uint8_t* ksx_get_tile_t_get_color_data(ksx_tile_t* data)
{
    ks_stream* stream = HANDLE(data)->stream;
    KS_CHECK(ksx_read_tile_t_instance_get_color_data(ks_stream_get_root(stream), (void*)ks_usertype_get_root((void*)data), stream, data), data->get_color_data);
    return data->get_color_data;
}

static ks_array_uint8_t* ksx_get_tile_t_get_tile_texture_data(ksx_tile_t* data)
{
    ks_stream* stream = HANDLE(data)->stream;
    KS_CHECK(ksx_read_tile_t_instance_get_tile_texture_data(ks_stream_get_root(stream), (void*)ks_usertype_get_root((void*)data), stream, data), data->get_tile_texture_data);
    return data->get_tile_texture_data;
}

static uint16_t ksx_get_tile_t_ofs_texture_data(ksx_tile_t* data)
{
    return data->ofs_texture_data;
}

static uint8_t ksx_get_tile_t_width(ksx_tile_t* data)
{
    return data->width;
}

static uint8_t ksx_get_tile_t_height(ksx_tile_t* data)
{
    return data->height;
}

static uint16_t ksx_get_tile_t_ofs_color_data(ksx_tile_t* data)
{
    return data->ofs_color_data;
}

static uint16_t ksx_get_tile_t_unknown(ksx_tile_t* data)
{
    return data->unknown;
}

static ks_array_int32_t* ksx_get_tile_t_horizontal_vector(ksx_tile_t* data)
{
    return data->horizontal_vector;
}

static ks_array_int32_t* ksx_get_tile_t_vertical_vector(ksx_tile_t* data)
{
    return data->vertical_vector;
}

static ks_array_int32_t* ksx_get_tile_t_base_vector(ksx_tile_t* data)
{
    return data->base_vector;
}

static ks_array_uint8_t* ksx_get_entity_polylink_t_getdata1(ksx_entity_polylink_t* data)
{
    ks_stream* stream = HANDLE(data)->stream;
    KS_CHECK(ksx_read_entity_polylink_t_instance_getdata1(ks_stream_get_root(stream), (void*)ks_usertype_get_root((void*)data), stream, data), data->getdata1);
    return data->getdata1;
}

static ks_array_uint8_t* ksx_get_entity_polylink_t_getdata2(ksx_entity_polylink_t* data)
{
    ks_stream* stream = HANDLE(data)->stream;
    KS_CHECK(ksx_read_entity_polylink_t_instance_getdata2(ks_stream_get_root(stream), (void*)ks_usertype_get_root((void*)data), stream, data), data->getdata2);
    return data->getdata2;
}

static uint16_t ksx_get_entity_polylink_t_lead(ksx_entity_polylink_t* data)
{
    return data->lead;
}

static ks_array_uint16_t* ksx_get_entity_polylink_t_ofs_entity_polylink_data1(ksx_entity_polylink_t* data)
{
    return data->ofs_entity_polylink_data1;
}

static ks_array_uint16_t* ksx_get_entity_polylink_t_ofs_entity_polylink_data2(ksx_entity_polylink_t* data)
{
    return data->ofs_entity_polylink_data2;
}

static uint16_t ksx_get_entity_polylink_t_unknown(ksx_entity_polylink_t* data)
{
    return data->unknown;
}

static ks_array_uint16_t* ksx_get_entity_polylink_t_reserved(ksx_entity_polylink_t* data)
{
    return data->reserved;
}

static ks_array_uint16_t* ksx_get_plane_t_vertex_indices(ksx_plane_t* data)
{
    return data->vertex_indices;
}

static uint16_t ksx_get_plane_t_sector_index(ksx_plane_t* data)
{
    return data->sector_index;
}

static uint16_t ksx_get_plane_t_flags(ksx_plane_t* data)
{
    return data->flags;
}

static uint16_t ksx_get_plane_t_collision_flags(ksx_plane_t* data)
{
    return data->collision_flags;
}

static uint16_t ksx_get_plane_t_tile_index(ksx_plane_t* data)
{
    return data->tile_index;
}

static uint16_t ksx_get_plane_t_unknown_index(ksx_plane_t* data)
{
    return data->unknown_index;
}

static uint16_t ksx_get_plane_t_quad_start_index(ksx_plane_t* data)
{
    return data->quad_start_index;
}

static uint16_t ksx_get_plane_t_quad_end_index(ksx_plane_t* data)
{
    return data->quad_end_index;
}

static uint16_t ksx_get_plane_t_vertex_start_index(ksx_plane_t* data)
{
    return data->vertex_start_index;
}

static uint16_t ksx_get_plane_t_vertex_end_index(ksx_plane_t* data)
{
    return data->vertex_end_index;
}

static ks_array_int16_t* ksx_get_plane_t_normal(ksx_plane_t* data)
{
    return data->normal;
}

static int16_t ksx_get_plane_t_distance(ksx_plane_t* data)
{
    return data->distance;
}

static int16_t ksx_get_plane_t_angle(ksx_plane_t* data)
{
    return data->angle;
}

static ks_array_uint16_t* ksx_get_plane_t_reserved(ksx_plane_t* data)
{
    return data->reserved;
}

static ks_bytes* ksx_get_sky_bitmap_t_image(ksx_sky_bitmap_t* data)
{
    return data->image;
}

static int16_t ksx_get_entity_generic_t_start(ksx_entity_generic_t* data)
{
    return data->start;
}

static ks_array_int16_t* ksx_get_entity_generic_t_coords(ksx_entity_generic_t* data)
{
    return data->coords;
}

static uint16_t ksx_get_resource_0x6a_t_unknown0(ksx_resource_0x6a_t* data)
{
    return data->unknown0;
}

static uint16_t ksx_get_resource_0x6a_t_len_data(ksx_resource_0x6a_t* data)
{
    return data->len_data;
}

static ks_bytes* ksx_get_resource_0x6a_t_data(ksx_resource_0x6a_t* data)
{
    return data->data;
}

static ksx_array_palette_entry_t* ksx_get_sky_data_t_palette(ksx_sky_data_t* data)
{
    return data->palette;
}

static ksx_array_sky_bitmap_t* ksx_get_sky_data_t_bitmaps(ksx_sky_data_t* data)
{
    return data->bitmaps;
}

static ks_bytes* ksx_get_tile_color_data_t_data(ksx_tile_color_data_t* data)
{
    return data->data;
}

static ksx_sky_data_t* ksx_get_lev_quake_sky_data(ksx_lev_quake* data)
{
    return (ksx_sky_data_t*)data->sky_data;
}

static ksx_header_t* ksx_get_lev_quake_header(ksx_lev_quake* data)
{
    return (ksx_header_t*)data->header;
}

static ksx_array_sector_t* ksx_get_lev_quake_sectors(ksx_lev_quake* data)
{
    return data->sectors;
}

static ksx_array_plane_t* ksx_get_lev_quake_planes(ksx_lev_quake* data)
{
    return data->planes;
}

static ksx_array_tile_t* ksx_get_lev_quake_tiles(ksx_lev_quake* data)
{
    return data->tiles;
}

static ksx_array_vertex_t* ksx_get_lev_quake_vertices(ksx_lev_quake* data)
{
    return data->vertices;
}

static ksx_array_quad_t* ksx_get_lev_quake_quads(ksx_lev_quake* data)
{
    return data->quads;
}

static ksx_array_entity_t* ksx_get_lev_quake_entities(ksx_lev_quake* data)
{
    return data->entities;
}

static ksx_array_entity_polylink_t* ksx_get_lev_quake_entity_polylinks(ksx_lev_quake* data)
{
    return data->entity_polylinks;
}

static ksx_entity_polylink_data1_t* ksx_get_lev_quake_entity_polylink_data1(ksx_lev_quake* data)
{
    return (ksx_entity_polylink_data1_t*)data->entity_polylink_data1;
}

static ksx_entity_polylink_data2_t* ksx_get_lev_quake_entity_polylink_data2(ksx_lev_quake* data)
{
    return (ksx_entity_polylink_data2_t*)data->entity_polylink_data2;
}

static ksx_entity_data_t* ksx_get_lev_quake_entity_data(ksx_lev_quake* data)
{
    return (ksx_entity_data_t*)data->entity_data;
}

static ksx_tile_texture_data_t* ksx_get_lev_quake_tile_texture_data(ksx_lev_quake* data)
{
    return (ksx_tile_texture_data_t*)data->tile_texture_data;
}

static ksx_tile_color_data_t* ksx_get_lev_quake_tile_color_data(ksx_lev_quake* data)
{
    return (ksx_tile_color_data_t*)data->tile_color_data;
}

static ks_array_bytes* ksx_get_lev_quake_unknown(ksx_lev_quake* data)
{
    return data->unknown;
}

static ksx_resources_t* ksx_get_lev_quake_resources(ksx_lev_quake* data)
{
    return (ksx_resources_t*)data->resources;
}

static ksx_len_and_unknown_t* ksx_get_lev_quake_unknown0(ksx_lev_quake* data)
{
    return (ksx_len_and_unknown_t*)data->unknown0;
}

static ks_string* ksx_get_lev_quake_level_name(ksx_lev_quake* data)
{
    return data->level_name;
}

static ks_array_uint32_t* ksx_get_lev_quake_unknown1(ksx_lev_quake* data)
{
    return data->unknown1;
}

static ksx_len_and_unknown_t* ksx_get_lev_quake_unknown2(ksx_lev_quake* data)
{
    return (ksx_len_and_unknown_t*)data->unknown2;
}

static ksx_len_and_unknown_t* ksx_get_lev_quake_unknown3(ksx_lev_quake* data)
{
    return (ksx_len_and_unknown_t*)data->unknown3;
}

static void ksx_fill_tile_texture_data_t_instances(ksx_tile_texture_data_t* data)
{
    ksx_tile_texture_data_t_internal* internal = (ksx_tile_texture_data_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_data = ksx_get_tile_texture_data_t_data;
}

static void ksx_read_tile_texture_data_t_instances(ksx_tile_texture_data_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_tile_texture_data_t_internal* internal = (ksx_tile_texture_data_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_entity_data_t_instances(ksx_entity_data_t* data)
{
    ksx_entity_data_t_internal* internal = (ksx_entity_data_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_data = ksx_get_entity_data_t_data;
}

static void ksx_read_entity_data_t_instances(ksx_entity_data_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_entity_data_t_internal* internal = (ksx_entity_data_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_resource_0x6c_t_instances(ksx_resource_0x6c_t* data)
{
    ksx_resource_0x6c_t_internal* internal = (ksx_resource_0x6c_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_unknown0 = ksx_get_resource_0x6c_t_unknown0;
    internal->_get_len_data = ksx_get_resource_0x6c_t_len_data;
    internal->_get_data = ksx_get_resource_0x6c_t_data;
}

static void ksx_read_resource_0x6c_t_instances(ksx_resource_0x6c_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_resource_0x6c_t_internal* internal = (ksx_resource_0x6c_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_sector_t_instances(ksx_sector_t* data)
{
    ksx_sector_t_internal* internal = (ksx_sector_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_reserved = ksx_get_sector_t_reserved;
    internal->_get_position = ksx_get_sector_t_position;
    internal->_get_distance = ksx_get_sector_t_distance;
    internal->_get_plane_start_index = ksx_get_sector_t_plane_start_index;
    internal->_get_plane_end_index = ksx_get_sector_t_plane_end_index;
    internal->_get_unknown = ksx_get_sector_t_unknown;
}

static void ksx_read_sector_t_instances(ksx_sector_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_sector_t_internal* internal = (ksx_sector_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_resources_prefix_t_instances(ksx_resources_prefix_t* data)
{
    ksx_resources_prefix_t_internal* internal = (ksx_resources_prefix_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_num_values = ksx_get_resources_prefix_t_num_values;
    internal->_get_values = ksx_get_resources_prefix_t_values;
}

static void ksx_read_resources_prefix_t_instances(ksx_resources_prefix_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_resources_prefix_t_internal* internal = (ksx_resources_prefix_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_sound_t_instances(ksx_sound_t* data)
{
    ksx_sound_t_internal* internal = (ksx_sound_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_len_samples = ksx_get_sound_t_len_samples;
    internal->_get_maybe_pitch_adjust = ksx_get_sound_t_maybe_pitch_adjust;
    internal->_get_bits = ksx_get_sound_t_bits;
    internal->_get_loop_point = ksx_get_sound_t_loop_point;
    internal->_get_samples = ksx_get_sound_t_samples;
}

static void ksx_read_sound_t_instances(ksx_sound_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_sound_t_internal* internal = (ksx_sound_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_entity_t_instances(ksx_entity_t* data)
{
    ksx_entity_t_internal* internal = (ksx_entity_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_get_entity_data = ksx_get_entity_t_get_entity_data;
    internal->_get_ent_type = ksx_get_entity_t_ent_type;
    internal->_get_ofs_entity_data = ksx_get_entity_t_ofs_entity_data;
    internal->_get_index = ksx_get_entity_t_index;
}

static void ksx_read_entity_t_instances(ksx_entity_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_entity_t_internal* internal = (ksx_entity_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    internal->_get_get_entity_data(data);
    if (data->_is_valid_get_entity_data)
    {
        if (internal->_read_instances_get_entity_data)
        {
            KS_CHECK_VOID(internal->_read_instances_get_entity_data(data->get_entity_data));
        }
    }
}

static void ksx_fill_resources_t_instances(ksx_resources_t* data)
{
    ksx_resources_t_internal* internal = (ksx_resources_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_prefix = ksx_get_resources_t_prefix;
    internal->_get_num_sounds = ksx_get_resources_t_num_sounds;
    internal->_get_sounds = ksx_get_resources_t_sounds;
    internal->_get_len_palette = ksx_get_resources_t_len_palette;
    internal->_get_palette = ksx_get_resources_t_palette;
    internal->_get_num_resources = ksx_get_resources_t_num_resources;
    internal->_get_resources = ksx_get_resources_t_resources;
}

static void ksx_read_resources_t_instances(ksx_resources_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_resources_t_internal* internal = (ksx_resources_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    KS_CHECK_VOID(ksx_read_resources_prefix_t_instances(data->prefix));
    for (i = 0; i < data->sounds->size; i++)
    {
        KS_CHECK_VOID(ksx_read_sound_t_instances(data->sounds->data[i]));
    }
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_VOID(ksx_read_palette_entry_t_instances(data->palette->data[i]));
    }
    for (i = 0; i < data->resources->size; i++)
    {
        KS_CHECK_VOID(ksx_read_resource_t_instances(data->resources->data[i]));
    }
}

static void ksx_fill_vertex_t_instances(ksx_vertex_t* data)
{
    ksx_vertex_t_internal* internal = (ksx_vertex_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_coords = ksx_get_vertex_t_coords;
    internal->_get_color_lookup = ksx_get_vertex_t_color_lookup;
    internal->_get_reserved = ksx_get_vertex_t_reserved;
}

static void ksx_read_vertex_t_instances(ksx_vertex_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_vertex_t_internal* internal = (ksx_vertex_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_header_t_instances(ksx_header_t* data)
{
    ksx_header_t_internal* internal = (ksx_header_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_unknown_01 = ksx_get_header_t_unknown_01;
    internal->_get_unknown_02 = ksx_get_header_t_unknown_02;
    internal->_get_num_sectors = ksx_get_header_t_num_sectors;
    internal->_get_num_planes = ksx_get_header_t_num_planes;
    internal->_get_num_vertices = ksx_get_header_t_num_vertices;
    internal->_get_num_quads = ksx_get_header_t_num_quads;
    internal->_get_len_tile_texture_data = ksx_get_header_t_len_tile_texture_data;
    internal->_get_num_tiles = ksx_get_header_t_num_tiles;
    internal->_get_len_tile_color_data = ksx_get_header_t_len_tile_color_data;
    internal->_get_num_entities = ksx_get_header_t_num_entities;
    internal->_get_len_entity_data = ksx_get_header_t_len_entity_data;
    internal->_get_num_entity_polylinks = ksx_get_header_t_num_entity_polylinks;
    internal->_get_num_entity_polylink_data1_segments = ksx_get_header_t_num_entity_polylink_data1_segments;
    internal->_get_num_entity_polylink_data2_segments = ksx_get_header_t_num_entity_polylink_data2_segments;
    internal->_get_num_unknown = ksx_get_header_t_num_unknown;
}

static void ksx_read_header_t_instances(ksx_header_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_header_t_internal* internal = (ksx_header_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_resource_0x34_t_instances(ksx_resource_0x34_t* data)
{
    ksx_resource_0x34_t_internal* internal = (ksx_resource_0x34_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_unknown0 = ksx_get_resource_0x34_t_unknown0;
    internal->_get_bitmap = ksx_get_resource_0x34_t_bitmap;
}

static void ksx_read_resource_0x34_t_instances(ksx_resource_0x34_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_resource_0x34_t_internal* internal = (ksx_resource_0x34_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_entity_polymover_t_instances(ksx_entity_polymover_t* data)
{
    ksx_entity_polymover_t_internal* internal = (ksx_entity_polymover_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_polylink_id = ksx_get_entity_polymover_t_polylink_id;
    internal->_get_data = ksx_get_entity_polymover_t_data;
}

static void ksx_read_entity_polymover_t_instances(ksx_entity_polymover_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_entity_polymover_t_internal* internal = (ksx_entity_polymover_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_len_and_unknown_t_instances(ksx_len_and_unknown_t* data)
{
    ksx_len_and_unknown_t_internal* internal = (ksx_len_and_unknown_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_len_data = ksx_get_len_and_unknown_t_len_data;
    internal->_get_data = ksx_get_len_and_unknown_t_data;
}

static void ksx_read_len_and_unknown_t_instances(ksx_len_and_unknown_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_len_and_unknown_t_internal* internal = (ksx_len_and_unknown_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_quad_t_instances(ksx_quad_t* data)
{
    ksx_quad_t_internal* internal = (ksx_quad_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_vertex_indices = ksx_get_quad_t_vertex_indices;
    internal->_get_texture_index = ksx_get_quad_t_texture_index;
}

static void ksx_read_quad_t_instances(ksx_quad_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_quad_t_internal* internal = (ksx_quad_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_texture_t_instances(ksx_texture_t* data)
{
    ksx_texture_t_internal* internal = (ksx_texture_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_palette = ksx_get_texture_t_palette;
    internal->_get_bitmap = ksx_get_texture_t_bitmap;
}

static void ksx_read_texture_t_instances(ksx_texture_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_texture_t_internal* internal = (ksx_texture_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_VOID(ksx_read_palette_entry_t_instances(data->palette->data[i]));
    }
}

static void ksx_fill_palette_entry_t_instances(ksx_palette_entry_t* data)
{
    ksx_palette_entry_t_internal* internal = (ksx_palette_entry_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_a = ksx_get_palette_entry_t_a;
    internal->_get_b = ksx_get_palette_entry_t_b;
    internal->_get_g = ksx_get_palette_entry_t_g;
    internal->_get_r = ksx_get_palette_entry_t_r;
}

static void ksx_read_palette_entry_t_instances(ksx_palette_entry_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_palette_entry_t_internal* internal = (ksx_palette_entry_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_entity_polylink_data1_t_instances(ksx_entity_polylink_data1_t* data)
{
    ksx_entity_polylink_data1_t_internal* internal = (ksx_entity_polylink_data1_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_data = ksx_get_entity_polylink_data1_t_data;
}

static void ksx_read_entity_polylink_data1_t_instances(ksx_entity_polylink_data1_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_entity_polylink_data1_t_internal* internal = (ksx_entity_polylink_data1_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_entity_polylink_data2_t_instances(ksx_entity_polylink_data2_t* data)
{
    ksx_entity_polylink_data2_t_internal* internal = (ksx_entity_polylink_data2_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_data = ksx_get_entity_polylink_data2_t_data;
}

static void ksx_read_entity_polylink_data2_t_instances(ksx_entity_polylink_data2_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_entity_polylink_data2_t_internal* internal = (ksx_entity_polylink_data2_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_resource_t_instances(ksx_resource_t* data)
{
    ksx_resource_t_internal* internal = (ksx_resource_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_flags = ksx_get_resource_t_flags;
    internal->_get_resource_type = ksx_get_resource_t_resource_type;
    internal->_get_data = ksx_get_resource_t_data;
}

static void ksx_read_resource_t_instances(ksx_resource_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_resource_t_internal* internal = (ksx_resource_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    if (data->_is_valid_data)
    {
        if (internal->_read_instances_data)
        {
            KS_CHECK_VOID(internal->_read_instances_data(data->data));
        }
    }
}

static void ksx_fill_tile_t_instances(ksx_tile_t* data)
{
    ksx_tile_t_internal* internal = (ksx_tile_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_get_color_data = ksx_get_tile_t_get_color_data;
    internal->_get_get_tile_texture_data = ksx_get_tile_t_get_tile_texture_data;
    internal->_get_ofs_texture_data = ksx_get_tile_t_ofs_texture_data;
    internal->_get_width = ksx_get_tile_t_width;
    internal->_get_height = ksx_get_tile_t_height;
    internal->_get_ofs_color_data = ksx_get_tile_t_ofs_color_data;
    internal->_get_unknown = ksx_get_tile_t_unknown;
    internal->_get_horizontal_vector = ksx_get_tile_t_horizontal_vector;
    internal->_get_vertical_vector = ksx_get_tile_t_vertical_vector;
    internal->_get_base_vector = ksx_get_tile_t_base_vector;
}

static void ksx_read_tile_t_instances(ksx_tile_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_tile_t_internal* internal = (ksx_tile_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    internal->_get_get_color_data(data);
    internal->_get_get_tile_texture_data(data);
}

static void ksx_fill_entity_polylink_t_instances(ksx_entity_polylink_t* data)
{
    ksx_entity_polylink_t_internal* internal = (ksx_entity_polylink_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_getdata1 = ksx_get_entity_polylink_t_getdata1;
    internal->_get_getdata2 = ksx_get_entity_polylink_t_getdata2;
    internal->_get_lead = ksx_get_entity_polylink_t_lead;
    internal->_get_ofs_entity_polylink_data1 = ksx_get_entity_polylink_t_ofs_entity_polylink_data1;
    internal->_get_ofs_entity_polylink_data2 = ksx_get_entity_polylink_t_ofs_entity_polylink_data2;
    internal->_get_unknown = ksx_get_entity_polylink_t_unknown;
    internal->_get_reserved = ksx_get_entity_polylink_t_reserved;
}

static void ksx_read_entity_polylink_t_instances(ksx_entity_polylink_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_entity_polylink_t_internal* internal = (ksx_entity_polylink_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    internal->_get_getdata1(data);
    internal->_get_getdata2(data);
}

static void ksx_fill_plane_t_instances(ksx_plane_t* data)
{
    ksx_plane_t_internal* internal = (ksx_plane_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_vertex_indices = ksx_get_plane_t_vertex_indices;
    internal->_get_sector_index = ksx_get_plane_t_sector_index;
    internal->_get_flags = ksx_get_plane_t_flags;
    internal->_get_collision_flags = ksx_get_plane_t_collision_flags;
    internal->_get_tile_index = ksx_get_plane_t_tile_index;
    internal->_get_unknown_index = ksx_get_plane_t_unknown_index;
    internal->_get_quad_start_index = ksx_get_plane_t_quad_start_index;
    internal->_get_quad_end_index = ksx_get_plane_t_quad_end_index;
    internal->_get_vertex_start_index = ksx_get_plane_t_vertex_start_index;
    internal->_get_vertex_end_index = ksx_get_plane_t_vertex_end_index;
    internal->_get_normal = ksx_get_plane_t_normal;
    internal->_get_distance = ksx_get_plane_t_distance;
    internal->_get_angle = ksx_get_plane_t_angle;
    internal->_get_reserved = ksx_get_plane_t_reserved;
}

static void ksx_read_plane_t_instances(ksx_plane_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_plane_t_internal* internal = (ksx_plane_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_sky_bitmap_t_instances(ksx_sky_bitmap_t* data)
{
    ksx_sky_bitmap_t_internal* internal = (ksx_sky_bitmap_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_image = ksx_get_sky_bitmap_t_image;
}

static void ksx_read_sky_bitmap_t_instances(ksx_sky_bitmap_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_sky_bitmap_t_internal* internal = (ksx_sky_bitmap_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_entity_generic_t_instances(ksx_entity_generic_t* data)
{
    ksx_entity_generic_t_internal* internal = (ksx_entity_generic_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_start = ksx_get_entity_generic_t_start;
    internal->_get_coords = ksx_get_entity_generic_t_coords;
}

static void ksx_read_entity_generic_t_instances(ksx_entity_generic_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_entity_generic_t_internal* internal = (ksx_entity_generic_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_resource_0x6a_t_instances(ksx_resource_0x6a_t* data)
{
    ksx_resource_0x6a_t_internal* internal = (ksx_resource_0x6a_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_unknown0 = ksx_get_resource_0x6a_t_unknown0;
    internal->_get_len_data = ksx_get_resource_0x6a_t_len_data;
    internal->_get_data = ksx_get_resource_0x6a_t_data;
}

static void ksx_read_resource_0x6a_t_instances(ksx_resource_0x6a_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_resource_0x6a_t_internal* internal = (ksx_resource_0x6a_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_sky_data_t_instances(ksx_sky_data_t* data)
{
    ksx_sky_data_t_internal* internal = (ksx_sky_data_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_palette = ksx_get_sky_data_t_palette;
    internal->_get_bitmaps = ksx_get_sky_data_t_bitmaps;
}

static void ksx_read_sky_data_t_instances(ksx_sky_data_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_sky_data_t_internal* internal = (ksx_sky_data_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    for (i = 0; i < data->palette->size; i++)
    {
        KS_CHECK_VOID(ksx_read_palette_entry_t_instances(data->palette->data[i]));
    }
    for (i = 0; i < data->bitmaps->size; i++)
    {
        KS_CHECK_VOID(ksx_read_sky_bitmap_t_instances(data->bitmaps->data[i]));
    }
}

static void ksx_fill_tile_color_data_t_instances(ksx_tile_color_data_t* data)
{
    ksx_tile_color_data_t_internal* internal = (ksx_tile_color_data_t_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_data = ksx_get_tile_color_data_t_data;
}

static void ksx_read_tile_color_data_t_instances(ksx_tile_color_data_t* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_tile_color_data_t_internal* internal = (ksx_tile_color_data_t_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
}

static void ksx_fill_lev_quake_instances(ksx_lev_quake* data)
{
    ksx_lev_quake_internal* internal = (ksx_lev_quake_internal*)HANDLE(data)->internal_read;
    (void)internal;
    internal->_get_sky_data = ksx_get_lev_quake_sky_data;
    internal->_get_header = ksx_get_lev_quake_header;
    internal->_get_sectors = ksx_get_lev_quake_sectors;
    internal->_get_planes = ksx_get_lev_quake_planes;
    internal->_get_tiles = ksx_get_lev_quake_tiles;
    internal->_get_vertices = ksx_get_lev_quake_vertices;
    internal->_get_quads = ksx_get_lev_quake_quads;
    internal->_get_entities = ksx_get_lev_quake_entities;
    internal->_get_entity_polylinks = ksx_get_lev_quake_entity_polylinks;
    internal->_get_entity_polylink_data1 = ksx_get_lev_quake_entity_polylink_data1;
    internal->_get_entity_polylink_data2 = ksx_get_lev_quake_entity_polylink_data2;
    internal->_get_entity_data = ksx_get_lev_quake_entity_data;
    internal->_get_tile_texture_data = ksx_get_lev_quake_tile_texture_data;
    internal->_get_tile_color_data = ksx_get_lev_quake_tile_color_data;
    internal->_get_unknown = ksx_get_lev_quake_unknown;
    internal->_get_resources = ksx_get_lev_quake_resources;
    internal->_get_unknown0 = ksx_get_lev_quake_unknown0;
    internal->_get_level_name = ksx_get_lev_quake_level_name;
    internal->_get_unknown1 = ksx_get_lev_quake_unknown1;
    internal->_get_unknown2 = ksx_get_lev_quake_unknown2;
    internal->_get_unknown3 = ksx_get_lev_quake_unknown3;
}

static void ksx_read_lev_quake_instances(ksx_lev_quake* data)
{
    int64_t i;
    ks_stream* stream = HANDLE(data)->stream;
    ksx_lev_quake_internal* internal = (ksx_lev_quake_internal*)HANDLE(data)->internal_read;
    (void)i;
    (void)stream;
    (void)internal;
    KS_CHECK_VOID(ksx_read_sky_data_t_instances(data->sky_data));
    KS_CHECK_VOID(ksx_read_header_t_instances(data->header));
    for (i = 0; i < data->sectors->size; i++)
    {
        KS_CHECK_VOID(ksx_read_sector_t_instances(data->sectors->data[i]));
    }
    for (i = 0; i < data->planes->size; i++)
    {
        KS_CHECK_VOID(ksx_read_plane_t_instances(data->planes->data[i]));
    }
    for (i = 0; i < data->tiles->size; i++)
    {
        KS_CHECK_VOID(ksx_read_tile_t_instances(data->tiles->data[i]));
    }
    for (i = 0; i < data->vertices->size; i++)
    {
        KS_CHECK_VOID(ksx_read_vertex_t_instances(data->vertices->data[i]));
    }
    for (i = 0; i < data->quads->size; i++)
    {
        KS_CHECK_VOID(ksx_read_quad_t_instances(data->quads->data[i]));
    }
    for (i = 0; i < data->entities->size; i++)
    {
        KS_CHECK_VOID(ksx_read_entity_t_instances(data->entities->data[i]));
    }
    for (i = 0; i < data->entity_polylinks->size; i++)
    {
        KS_CHECK_VOID(ksx_read_entity_polylink_t_instances(data->entity_polylinks->data[i]));
    }
    KS_CHECK_VOID(ksx_read_entity_polylink_data1_t_instances(data->entity_polylink_data1));
    KS_CHECK_VOID(ksx_read_entity_polylink_data2_t_instances(data->entity_polylink_data2));
    KS_CHECK_VOID(ksx_read_entity_data_t_instances(data->entity_data));
    KS_CHECK_VOID(ksx_read_tile_texture_data_t_instances(data->tile_texture_data));
    KS_CHECK_VOID(ksx_read_tile_color_data_t_instances(data->tile_color_data));
    KS_CHECK_VOID(ksx_read_resources_t_instances(data->resources));
    KS_CHECK_VOID(ksx_read_len_and_unknown_t_instances(data->unknown0));
    KS_CHECK_VOID(ksx_read_len_and_unknown_t_instances(data->unknown2));
    KS_CHECK_VOID(ksx_read_len_and_unknown_t_instances(data->unknown3));
}

