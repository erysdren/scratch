#pragma author erysdren
#pragma description Microsoft 3D Movie Maker Kauai format
#pragma endian little

// file index structure
struct FileIndex {
	u16 byte_order;
	u16 author_system;
	u16 num_chunks;
	u16 len_chunks;
	padding[8];
};

// header structure
struct Header {
	char magic[4];
	char author_program[4];
	u16 chunk_version_current;
	u16 chunk_version_min;
	u16 byte_order;
	u16 author_system;
	u32 len_file;
	u32 ofs_file_index;
	u32 len_file_index;
	u32 ofs_free_space_map;
	u32 len_free_space_map;
	padding[92];
};

// kauai structure
struct Kauai {
	Header header;
	FileIndex file_index @ header.ofs_file_index;
};

// begin parsing
Kauai kauai @ 0x00;
