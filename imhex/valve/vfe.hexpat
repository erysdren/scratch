#pragma author erysdren
#pragma description Source Engine Flex Expressions
#pragma endian little

#pragma magic [ 45 46 56 00 ] @ 0x00

import type.magic;

enum FlexSettingType : s32 {
	Normal = 0,
	Markov = 1
};

struct FlexMarkovSetting {
	s32 setting;
	s32 weight;
};

struct FlexWeight {
	s32 key;
	float weight;
	float influence;
};

struct FlexSetting {
	s32 ofs_name;
	FlexSettingType type;
	s32 num_data;
	s32 index;
	s32 ofs_current;
	s32 ofs_data;

	char name[] @ addressof(this) + ofs_name;

	if (type == FlexSettingType::Normal) {
		FlexWeight weights[num_data] @ addressof(this) + ofs_data;
	} else if (type == FlexSettingType::Markov) {
		FlexMarkovSetting markovsettings[num_data] @ addressof(this) + ofs_data;
	}
};

struct KeyName {
	s32 ofs_name;

	char name[] @ ofs_name;
};

struct Header {
	type::Magic<"EFV\0"> magic;
	s32 version;
	char name[64];
	s32 filesize;
	s32 num_flexsettings;
	s32 ofs_flexsettings;
	s32 ofs_name;
	s32 num_indices;
	s32 ofs_indices;
	s32 num_keys;
	s32 ofs_keynames;
	s32 ofs_keyremap;
};

Header header @ 0x00;
s32 indices[header.num_indices] @ header.ofs_indices;
FlexSetting flexsettings[header.num_flexsettings] @ header.ofs_flexsettings;
KeyName keynames[header.num_keys] @ header.ofs_keynames;
s32 keyremap[header.num_keys] @ header.ofs_keyremap;
