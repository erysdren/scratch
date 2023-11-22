#pragma author erysdren
#pragma description Rise of the Triad Level Format
#pragma endian little

// magic identifiers
enum LevelMagics : u32 {
    RTL = 0x4C5452,
    RTC = 0x435452,
    RXL = 0x4C5852,
    RXC = 0x435852
};

// map header
struct MapHeader {
    u32 used;
    u32 crc;
    u32 rle_tag;
    u32 flags;
    u32 ofs_walls;
    u32 ofs_sprites;
    u32 ofs_infos;
    u32 len_walls;
    u32 len_sprites;
    u32 len_infos;
    u8 name[24];

    u16 walls[len_walls / 2] @ ofs_walls;
    u16 sprites[len_sprites / 2] @ ofs_sprites;
    u16 infos[len_infos / 2] @ ofs_infos;
};

// info header
struct InfoHeader {
    u8 magic[16];
    u64 ofs_data;
    u64 len_data;

    u8 data[len_data] @ ofs_data;
};

// level structure
struct Level {

    // file header
    u32 magic;
    u32 version;

    if (magic == LevelMagics::RXL || magic == LevelMagics::RXC)
    {
        // special parsing if it's from RottEX
        u64 ofs_info_headers;
        u64 num_info_headers;
        InfoHeader info_headers[num_info_headers] @ ofs_info_headers;
    }
    else
    {
        // otherwise 100 map headers
        MapHeader maps[100];
    }
};

// begin parsing
Level level @ 0x00;
