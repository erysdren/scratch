#pragma author erysdren
#pragma description Rise of the Triad Level Format
#pragma endian little

// File structure
struct File {
	u8 name[0x30];
	u32 len;
	u32 ofs;
	u32 idk;
};

// P4CK structure
struct P4CK {
    u32 magic;
    u32 ofs_files;
    u32 len_files;
    File files[len_files / sizeof(File)] @ ofs_files;
};

// begin parsing
P4CK p4ck @ 0x00;
