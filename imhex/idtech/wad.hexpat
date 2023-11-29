#pragma author erysdren
#pragma description idTech WAD Format
#pragma endian little

// magic identifiers
enum WADMagics : u32 {
    IWAD = 0x44415749,
    PWAD = 0x44415750,
    WAD2 = 0x32444157,
    WAD3 = 0x33444157
};

// lump v1 structure
struct LumpV1 {
    u32 ofs_data;
    u32 len_data;
    u8 name[8];

    u8 data[len_data] @ ofs_data;
};

// lump v2+ structure
struct LumpV2 {
    u32 ofs_data;
    u32 len_data_compressed;
    u32 len_data_uncompressed;
    u8 type;
    u8 compressed;
    padding[2];
    u8 name[16];

    u8 data[len_data_compressed] @ ofs_data;
};

// wad structure
struct WAD {

    // file header
    u32 magic;
    u32 num_lumps;
    u32 ofs_lumps;

    // lump table
    match (magic)
    {
        (WADMagics::IWAD): LumpV1 lumps[num_lumps] @ ofs_lumps;
        (WADMagics::PWAD): LumpV1 lumps[num_lumps] @ ofs_lumps;
        (WADMagics::WAD2): LumpV2 lumps[num_lumps] @ ofs_lumps;
        (WADMagics::WAD3): LumpV2 lumps[num_lumps] @ ofs_lumps;
    }
};

// begin parsing
WAD wad @ 0x00;
