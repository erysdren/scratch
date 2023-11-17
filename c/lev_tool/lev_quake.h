/* This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild */

#ifndef KAITAI_LEV_QUAKE_H
#define KAITAI_LEV_QUAKE_H

#include "kaitaistruct.h"

/* Forward declarations */

/* Main struct */
#ifndef HAVE_DECL_lev_quake
#define HAVE_DECL_lev_quake
typedef struct ksx_lev_quake ksx_lev_quake;
#endif
typedef struct ksx_array_lev_quake ksx_array_lev_quake;
typedef struct ksx_lev_quake_internal ksx_lev_quake_internal;
typedef struct ksx_tile_texture_data_t ksx_tile_texture_data_t;
typedef struct ksx_array_tile_texture_data_t ksx_array_tile_texture_data_t;
typedef struct ksx_tile_texture_data_t_internal ksx_tile_texture_data_t_internal;
typedef struct ksx_entity_data_t ksx_entity_data_t;
typedef struct ksx_array_entity_data_t ksx_array_entity_data_t;
typedef struct ksx_entity_data_t_internal ksx_entity_data_t_internal;
typedef struct ksx_resource_0x6c_t ksx_resource_0x6c_t;
typedef struct ksx_array_resource_0x6c_t ksx_array_resource_0x6c_t;
typedef struct ksx_resource_0x6c_t_internal ksx_resource_0x6c_t_internal;
typedef struct ksx_sector_t ksx_sector_t;
typedef struct ksx_array_sector_t ksx_array_sector_t;
typedef struct ksx_sector_t_internal ksx_sector_t_internal;
typedef struct ksx_resources_prefix_t ksx_resources_prefix_t;
typedef struct ksx_array_resources_prefix_t ksx_array_resources_prefix_t;
typedef struct ksx_resources_prefix_t_internal ksx_resources_prefix_t_internal;
typedef struct ksx_sound_t ksx_sound_t;
typedef struct ksx_array_sound_t ksx_array_sound_t;
typedef struct ksx_sound_t_internal ksx_sound_t_internal;
typedef struct ksx_entity_t ksx_entity_t;
typedef struct ksx_array_entity_t ksx_array_entity_t;
typedef struct ksx_entity_t_internal ksx_entity_t_internal;
typedef struct ksx_resources_t ksx_resources_t;
typedef struct ksx_array_resources_t ksx_array_resources_t;
typedef struct ksx_resources_t_internal ksx_resources_t_internal;
typedef struct ksx_vertex_t ksx_vertex_t;
typedef struct ksx_array_vertex_t ksx_array_vertex_t;
typedef struct ksx_vertex_t_internal ksx_vertex_t_internal;
typedef struct ksx_header_t ksx_header_t;
typedef struct ksx_array_header_t ksx_array_header_t;
typedef struct ksx_header_t_internal ksx_header_t_internal;
typedef struct ksx_resource_0x34_t ksx_resource_0x34_t;
typedef struct ksx_array_resource_0x34_t ksx_array_resource_0x34_t;
typedef struct ksx_resource_0x34_t_internal ksx_resource_0x34_t_internal;
typedef struct ksx_entity_polymover_t ksx_entity_polymover_t;
typedef struct ksx_array_entity_polymover_t ksx_array_entity_polymover_t;
typedef struct ksx_entity_polymover_t_internal ksx_entity_polymover_t_internal;
typedef struct ksx_len_and_unknown_t ksx_len_and_unknown_t;
typedef struct ksx_array_len_and_unknown_t ksx_array_len_and_unknown_t;
typedef struct ksx_len_and_unknown_t_internal ksx_len_and_unknown_t_internal;
typedef struct ksx_quad_t ksx_quad_t;
typedef struct ksx_array_quad_t ksx_array_quad_t;
typedef struct ksx_quad_t_internal ksx_quad_t_internal;
typedef struct ksx_texture_t ksx_texture_t;
typedef struct ksx_array_texture_t ksx_array_texture_t;
typedef struct ksx_texture_t_internal ksx_texture_t_internal;
typedef struct ksx_palette_entry_t ksx_palette_entry_t;
typedef struct ksx_array_palette_entry_t ksx_array_palette_entry_t;
typedef struct ksx_palette_entry_t_internal ksx_palette_entry_t_internal;
typedef struct ksx_entity_polylink_data1_t ksx_entity_polylink_data1_t;
typedef struct ksx_array_entity_polylink_data1_t ksx_array_entity_polylink_data1_t;
typedef struct ksx_entity_polylink_data1_t_internal ksx_entity_polylink_data1_t_internal;
typedef struct ksx_entity_polylink_data2_t ksx_entity_polylink_data2_t;
typedef struct ksx_array_entity_polylink_data2_t ksx_array_entity_polylink_data2_t;
typedef struct ksx_entity_polylink_data2_t_internal ksx_entity_polylink_data2_t_internal;
typedef struct ksx_resource_t ksx_resource_t;
typedef struct ksx_array_resource_t ksx_array_resource_t;
typedef struct ksx_resource_t_internal ksx_resource_t_internal;
typedef struct ksx_tile_t ksx_tile_t;
typedef struct ksx_array_tile_t ksx_array_tile_t;
typedef struct ksx_tile_t_internal ksx_tile_t_internal;
typedef struct ksx_entity_polylink_t ksx_entity_polylink_t;
typedef struct ksx_array_entity_polylink_t ksx_array_entity_polylink_t;
typedef struct ksx_entity_polylink_t_internal ksx_entity_polylink_t_internal;
typedef struct ksx_plane_t ksx_plane_t;
typedef struct ksx_array_plane_t ksx_array_plane_t;
typedef struct ksx_plane_t_internal ksx_plane_t_internal;
typedef struct ksx_sky_bitmap_t ksx_sky_bitmap_t;
typedef struct ksx_array_sky_bitmap_t ksx_array_sky_bitmap_t;
typedef struct ksx_sky_bitmap_t_internal ksx_sky_bitmap_t_internal;
typedef struct ksx_entity_generic_t ksx_entity_generic_t;
typedef struct ksx_array_entity_generic_t ksx_array_entity_generic_t;
typedef struct ksx_entity_generic_t_internal ksx_entity_generic_t_internal;
typedef struct ksx_resource_0x6a_t ksx_resource_0x6a_t;
typedef struct ksx_array_resource_0x6a_t ksx_array_resource_0x6a_t;
typedef struct ksx_resource_0x6a_t_internal ksx_resource_0x6a_t_internal;
typedef struct ksx_sky_data_t ksx_sky_data_t;
typedef struct ksx_array_sky_data_t ksx_array_sky_data_t;
typedef struct ksx_sky_data_t_internal ksx_sky_data_t_internal;
typedef struct ksx_tile_color_data_t ksx_tile_color_data_t;
typedef struct ksx_array_tile_color_data_t ksx_array_tile_color_data_t;
typedef struct ksx_tile_color_data_t_internal ksx_tile_color_data_t_internal;

/* Enums */

/* Main structures */

ksx_lev_quake* ksx_read_lev_quake_from_stream(ks_stream* stream, ks_error* error);

struct ksx_tile_texture_data_t
{
    ks_usertype_generic kaitai_base;
    ks_bytes* data;
};

struct ksx_entity_data_t
{
    ks_usertype_generic kaitai_base;
    ks_bytes* data;
};

struct ksx_resource_0x6c_t
{
    ks_usertype_generic kaitai_base;
    uint16_t unknown0;
    uint16_t len_data;
    ks_bytes* data;
};

struct ksx_sector_t
{
    ks_usertype_generic kaitai_base;
    ks_array_uint16_t* reserved;
    ks_array_uint16_t* position;
    uint16_t distance;
    uint16_t plane_start_index;
    uint16_t plane_end_index;
    ks_array_uint16_t* unknown;
};

struct ksx_resources_prefix_t
{
    ks_usertype_generic kaitai_base;
    uint32_t num_values;
    ks_array_int16_t* values;
};

struct ksx_sound_t
{
    ks_usertype_generic kaitai_base;
    int32_t len_samples;
    int32_t maybe_pitch_adjust;
    int32_t bits;
    int32_t loop_point;
    ks_bytes* samples;
};

struct ksx_entity_t
{
    ks_usertype_generic kaitai_base;
    ks_bool _is_valid_get_entity_data;
    ks_usertype_generic* get_entity_data;
    uint16_t ent_type;
    uint16_t ofs_entity_data;
    int32_t index;
};

struct ksx_resources_t
{
    ks_usertype_generic kaitai_base;
    ksx_resources_prefix_t* prefix;
    uint32_t num_sounds;
    ksx_array_sound_t* sounds;
    uint32_t len_palette;
    ksx_array_palette_entry_t* palette;
    uint32_t num_resources;
    ksx_array_resource_t* resources;
};

struct ksx_vertex_t
{
    ks_usertype_generic kaitai_base;
    ks_array_int16_t* coords;
    uint8_t color_lookup;
    uint8_t reserved;
};

struct ksx_header_t
{
    ks_usertype_generic kaitai_base;
    uint32_t unknown_01;
    uint32_t unknown_02;
    uint32_t num_sectors;
    uint32_t num_planes;
    uint32_t num_vertices;
    uint32_t num_quads;
    uint32_t len_tile_texture_data;
    uint32_t num_tiles;
    uint32_t len_tile_color_data;
    uint32_t num_entities;
    uint32_t len_entity_data;
    uint32_t num_entity_polylinks;
    uint32_t num_entity_polylink_data1_segments;
    uint32_t num_entity_polylink_data2_segments;
    uint32_t num_unknown;
};

struct ksx_resource_0x34_t
{
    ks_usertype_generic kaitai_base;
    uint16_t unknown0;
    ks_array_uint64_t* bitmap;
};

struct ksx_entity_polymover_t
{
    ks_usertype_generic kaitai_base;
    int16_t polylink_id;
    ks_array_int16_t* data;
};

struct ksx_len_and_unknown_t
{
    ks_usertype_generic kaitai_base;
    uint32_t len_data;
    ks_bytes* data;
};

struct ksx_quad_t
{
    ks_usertype_generic kaitai_base;
    ks_array_uint8_t* vertex_indices;
    uint8_t texture_index;
};

struct ksx_texture_t
{
    ks_usertype_generic kaitai_base;
    ksx_array_palette_entry_t* palette;
    ks_array_uint64_t* bitmap;
};

struct ksx_palette_entry_t
{
    ks_usertype_generic kaitai_base;
    ks_bool a;
    uint64_t b;
    uint64_t g;
    uint64_t r;
};

struct ksx_entity_polylink_data1_t
{
    ks_usertype_generic kaitai_base;
    ks_array_uint8_t* data;
};

struct ksx_entity_polylink_data2_t
{
    ks_usertype_generic kaitai_base;
    ks_array_uint8_t* data;
};

struct ksx_resource_t
{
    ks_usertype_generic kaitai_base;
    uint8_t flags;
    uint8_t resource_type;
    ks_bool _is_valid_data;
    ks_usertype_generic* data;
};

struct ksx_tile_t
{
    ks_usertype_generic kaitai_base;
    ks_array_uint8_t* get_color_data;
    ks_array_uint8_t* get_tile_texture_data;
    uint16_t ofs_texture_data;
    uint8_t width;
    uint8_t height;
    uint16_t ofs_color_data;
    uint16_t unknown;
    ks_array_int32_t* horizontal_vector;
    ks_array_int32_t* vertical_vector;
    ks_array_int32_t* base_vector;
};

struct ksx_entity_polylink_t
{
    ks_usertype_generic kaitai_base;
    ks_array_uint8_t* getdata1;
    ks_array_uint8_t* getdata2;
    uint16_t lead;
    ks_array_uint16_t* ofs_entity_polylink_data1;
    ks_array_uint16_t* ofs_entity_polylink_data2;
    uint16_t unknown;
    ks_array_uint16_t* reserved;
};

struct ksx_plane_t
{
    ks_usertype_generic kaitai_base;
    ks_array_uint16_t* vertex_indices;
    uint16_t sector_index;
    uint16_t flags;
    uint16_t collision_flags;
    uint16_t tile_index;
    uint16_t unknown_index;
    uint16_t quad_start_index;
    uint16_t quad_end_index;
    uint16_t vertex_start_index;
    uint16_t vertex_end_index;
    ks_array_int16_t* normal;
    int16_t distance;
    int16_t angle;
    ks_array_uint16_t* reserved;
};

struct ksx_sky_bitmap_t
{
    ks_usertype_generic kaitai_base;
    ks_bytes* image;
};

struct ksx_entity_generic_t
{
    ks_usertype_generic kaitai_base;
    int16_t start;
    ks_array_int16_t* coords;
};

struct ksx_resource_0x6a_t
{
    ks_usertype_generic kaitai_base;
    uint16_t unknown0;
    uint16_t len_data;
    ks_bytes* data;
};

struct ksx_sky_data_t
{
    ks_usertype_generic kaitai_base;
    ksx_array_palette_entry_t* palette;
    ksx_array_sky_bitmap_t* bitmaps;
};

struct ksx_tile_color_data_t
{
    ks_usertype_generic kaitai_base;
    ks_bytes* data;
};

struct ksx_lev_quake
{
    ks_usertype_generic kaitai_base;
    ksx_sky_data_t* sky_data;
    ksx_header_t* header;
    ksx_array_sector_t* sectors;
    ksx_array_plane_t* planes;
    ksx_array_tile_t* tiles;
    ksx_array_vertex_t* vertices;
    ksx_array_quad_t* quads;
    ksx_array_entity_t* entities;
    ksx_array_entity_polylink_t* entity_polylinks;
    ksx_entity_polylink_data1_t* entity_polylink_data1;
    ksx_entity_polylink_data2_t* entity_polylink_data2;
    ksx_entity_data_t* entity_data;
    ksx_tile_texture_data_t* tile_texture_data;
    ksx_tile_color_data_t* tile_color_data;
    ks_array_bytes* unknown;
    ksx_resources_t* resources;
    ksx_len_and_unknown_t* unknown0;
    ks_string* level_name;
    ks_array_uint32_t* unknown1;
    ksx_len_and_unknown_t* unknown2;
    ksx_len_and_unknown_t* unknown3;
};

/* Array structures */

struct ksx_array_lev_quake
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_lev_quake** data;
};

struct ksx_array_tile_texture_data_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_tile_texture_data_t** data;
};

struct ksx_array_entity_data_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_entity_data_t** data;
};

struct ksx_array_resource_0x6c_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_resource_0x6c_t** data;
};

struct ksx_array_sector_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_sector_t** data;
};

struct ksx_array_resources_prefix_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_resources_prefix_t** data;
};

struct ksx_array_sound_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_sound_t** data;
};

struct ksx_array_entity_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_entity_t** data;
};

struct ksx_array_resources_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_resources_t** data;
};

struct ksx_array_vertex_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_vertex_t** data;
};

struct ksx_array_header_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_header_t** data;
};

struct ksx_array_resource_0x34_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_resource_0x34_t** data;
};

struct ksx_array_entity_polymover_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_entity_polymover_t** data;
};

struct ksx_array_len_and_unknown_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_len_and_unknown_t** data;
};

struct ksx_array_quad_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_quad_t** data;
};

struct ksx_array_texture_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_texture_t** data;
};

struct ksx_array_palette_entry_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_palette_entry_t** data;
};

struct ksx_array_entity_polylink_data1_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_entity_polylink_data1_t** data;
};

struct ksx_array_entity_polylink_data2_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_entity_polylink_data2_t** data;
};

struct ksx_array_resource_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_resource_t** data;
};

struct ksx_array_tile_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_tile_t** data;
};

struct ksx_array_entity_polylink_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_entity_polylink_t** data;
};

struct ksx_array_plane_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_plane_t** data;
};

struct ksx_array_sky_bitmap_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_sky_bitmap_t** data;
};

struct ksx_array_entity_generic_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_entity_generic_t** data;
};

struct ksx_array_resource_0x6a_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_resource_0x6a_t** data;
};

struct ksx_array_sky_data_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_sky_data_t** data;
};

struct ksx_array_tile_color_data_t
{
    ks_usertype_generic kaitai_base;
    int64_t size;
    ksx_tile_color_data_t** data;
};

#endif
