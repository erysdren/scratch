#pragma author erysdren
#pragma description BUILD Engine ART Format
#pragma endian little

// art structure
struct ART {
    u32 version;
    u32 num_tiles;
    u32 tile_id_start;
    u32 tile_id_end;
    u16 tile_sizes_x[tile_id_start + tile_id_end + 1];
    u16 tile_sizes_y[tile_id_start + tile_id_end + 1];
    u32 tile_attributes[tile_id_start + tile_id_end + 1];
};

// begin parsing
ART art @ 0x00;
