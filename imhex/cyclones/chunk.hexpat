#pragma author erysdren
#pragma description CyClones Chunk Format
#pragma endian little

#include <std/mem.pat>

// map structure
struct Chunk {
    u8 magic[4];
    u16 unknown;
    u32 len;
    u8 data[len];
};

// begin parsing
Chunk chunks[while($ < std::mem::size())] @ 0x00;
