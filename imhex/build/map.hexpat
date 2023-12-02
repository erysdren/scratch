#pragma author erysdren
#pragma description BUILD Engine MAP Format
#pragma endian little

// sector structure
struct Sector {
    u16 ofs_walls;;
    u16 num_walls;
    s32 ceiling_height;
    s32 floor_height;
    u16 ceiling_stat;
    u16 floor_stat;
    u16 ceiling_texture;
    u16 ceiling_hei_num;
    s8 ceiling_shade;
    u8 ceiling_pal;
    u8 ceiling_panning[2];
    u16 floor_texture;
    u16 floorhei_num;
    s8 floor_shade;
    u8 floor_pal;
    u8 floor_panning[2];
    u8 visibility;
    padding[1];
    u16 lotag;
    u16 hitag;
    u16 extra;
};

// sector structure
struct Wall {
    s32 origin[2];
    s16 next_point;
    s16 next_wall;
    s16 next_sector;
    s16 cstat;
    s16 picnum;
    s16 overpicnum;
    s8 shade;
    u8 pal;
    u8 repeat[2];
    u8 padding[2];
    s16 lotag;
    s16 hitag;
    s16 extra;
};

// sprite structure
struct Sprite {
    s32 origin[3];
    s16 cstat;
    s16 picnum;
    s8 shade;
    u8 pal;
    u8 clipdist;
    u8 filler;
    u8 repeat[2];
    s8 offset[2];
    s16 sectnum;
    s16 statnum;
    s16 ang;
    s16 owner;
    s16 velocity[3];
    s16 lotag;
    s16 hitag;
    s16 extra;
} spritetype;

// map structure
struct MAP {
    u32 version;
    s32 start_position[3];
    s16 start_angle;
    s16 start_sector;
    u16 num_sectors;
    Sector sectors[num_sectors];
    u16 num_walls;
    Wall walls[num_walls];
    u16 num_sprites;
    Sprite sprites[num_sprites];
};

// begin parsing
MAP map @ 0x00;
