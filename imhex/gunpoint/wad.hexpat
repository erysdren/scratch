#pragma author erysdren
#pragma description Gunpoint WAD Format
#pragma endian little

struct File {
	u32 len_name;
	char name[len_name];
	u32 len_data;
	u32 ofs_data;

	u8 data[len_data] @ ofs_data;
};

u32 len_header @ 0x00;
u32 num_files @ $;
File files[num_files] @ $;
