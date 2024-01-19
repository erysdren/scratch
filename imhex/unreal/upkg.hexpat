#pragma author erysdren
#pragma description Unreal Engine 1 Package Format
#pragma endian little

struct Generation {
	s32 num_exports;
	s32 num_names;
};

struct Name {
	u8 len_name;
	char name[len_name];
	u32 flags;
};

struct CompactInt {
	u8 a;
	if ((a & 0x40) != 0)
	{
		u8 b;
		if ((b & 0x80) != 0)
		{
			u8 c;
			if ((c & 0x80) != 0)
			{
				u8 d;
			}
		}
	}
};

struct Export {
	CompactInt class_index;
	CompactInt super_index;
	s32 package_index;
	CompactInt object_name;
	u32 object_flags;
	CompactInt len_serial;
	CompactInt ofs_serial;
};

struct Import {
	CompactInt class_package;
	CompactInt class_name;
	s32 package_index;
	CompactInt object_name;
};

struct UPKG {
	u32 tag;
	u16 format_version;
	u16 licensee_version;
	u32 package_flags;
	s32 num_names;
	s32 ofs_names;
	s32 num_exports;
	s32 ofs_exports;
	s32 num_imports;
	s32 ofs_imports;
	u32 guid[4];
	s32 num_generations;
	Generation generations[num_generations];
	Name names[num_names] @ ofs_names;
	Export exports[num_exports] @ ofs_exports;
	Import imports[num_imports] @ ofs_imports;
};

// begin parsing
UPKG upkg @ 0x00;
