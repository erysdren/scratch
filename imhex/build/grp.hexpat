#pragma author erysdren
#pragma description BUILD Engine GRP Format
#pragma endian little

// grp file structure
struct GRP_File {
    u8 filename[12];
    u32 len_file;
};

// grp structure
struct GRP {
    u8 magic[12];
    u32 num_files;
    GRP_File files[num_files];
};

// begin parsing
GRP grp @ 0x00;
