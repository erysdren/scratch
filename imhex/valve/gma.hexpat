#pragma author erysdren
#pragma description Garry's Mod Addon package format
#pragma endian little

#include <std/mem.pat>

struct File {
	u32 id;
	char path[];
	u64 size;
	u32 crc;
};

struct GMA {
	char magic[4];
	u8 version;
	u64 steamid;
	u64 timestamp;
	padding[1];
	char addon_name[];
	char addon_description[];
	char addon_author[];
	u32 addon_version;
	File file_table[while(std::mem::read_unsigned($, 4) != 0x00)];
	padding[4];
	u8 file_data[while($ < std::mem::size() - sizeof(u32))];
	u32 crc;
};

GMA gma @ 0x00;
