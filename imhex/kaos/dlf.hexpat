#pragma author erysdren
#pragma description Kaos (1997) Level File
#pragma endian little

struct Map {
    u8 i;
    u8 name[24];
    u8 backnum;
    u8 map[0x2000];
    u8 floormap[0x1000];
    u8 ceilmap[0x1000];
};

struct Level {
    u8 magic[8];
    u8 num_maps;
    Map maps[num_maps];
};

// begin parsing
Level level @ 0x00;
