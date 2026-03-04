#pragma author erysdren
#pragma description GoldSrc Model
#pragma endian little

import type.magic;

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

struct BBox {
	Vec3 min, max;
};

struct Header {
	type::Magic<"IDST"> magic;
	s32 version;
	char name[64];
	s32 filesize;
	Vec3 eyeposition;
	BBox hull;
	BBox view;
	s32 flags;
	s32 num_bones;
	s32 ofs_bones;
	s32 num_bonecontrollers;
	s32 ofs_bonecontrollers;
	s32 num_hitboxes;
	s32 ofs_hitboxes;
	s32 num_sequences;
	s32 ofs_sequences;
	s32 num_sequencegroups;
	s32 ofs_sequencegroups;
	s32 num_textures;
	s32 ofs_textures;
	s32 ofs_texturedata;
	s32 num_skinrefs;
	s32 num_skinfamilies;
	s32 ofs_skinfamilies;
	s32 num_bodyparts;
	s32 ofs_bodyparts;
	s32 num_attachments;
	s32 ofs_attachments;
	s32 soundtable;
	s32 soundindex;
	s32 soundgroups;
	s32 soundgroupindex;
	s32 numtransitions;
	s32 transitionindex;
};

struct Texture {
	char name[64];
	s32 flags;
	s32 width;
	s32 height;
	s32 offset;

	u8 data[width * height] @ offset;
	u8 palette[768] @ offset + (width * height);
};

struct TriangleVertex {
	s32 ofs_vertex;
	s32 ofs_normal;
	s32 s;
	s32 t;
	float u;
	float v;
};

struct TriangleCommandVertex {
	s16 ofs_vertex;
	s16 ofs_normal;
	s16 s;
	s16 t;
};

struct TriangleCommand {
	s16 count;
	if (count == 0) {
		// done
		break;
	} else if (count < 0) {
		// fan
		TriangleCommandVertex vertices[-count];
	} else {
		// strip
		TriangleCommandVertex vertices[count];
	}
};

struct Mesh {
	s32 num_triangles;
	s32 ofs_triangle_commands;
	s32 skinref_index;
	s32 num_normals;
	s32 ofs_normals;

	TriangleCommand triangles[2048] @ ofs_triangle_commands;
};

struct SequenceGroup {
	char label[32];
	char name[64];
	u32 cache;
	s32 data;
};

struct SkinFamily {
	s16 skinrefs[header.num_skinrefs];
};

struct Model {
	char name[64];
	s32 type;
	float bounding_radius;
	s32 num_meshes;
	s32 ofs_meshes;
	s32 num_vertices;
	s32 ofs_vertexinfo;
	s32 ofs_vertices;
	s32 num_normals;
	s32 ofs_normalinfo;
	s32 ofs_normals;
	s32 num_groups;
	s32 ofs_groups;

	Vec3 vertices[num_vertices] @ ofs_vertices;
	u8 vertexinfo[num_vertices] @ ofs_vertexinfo;
	Vec3 normals[num_normals] @ ofs_normals;
	u8 normalinfo[num_normals] @ ofs_normalinfo;
	Mesh meshes[num_meshes] @ ofs_meshes;
};

struct BodyPart {
	char name[64];
	s32 num_models;
	s32 base;
	s32 ofs_models;

	Model models[num_models] @ ofs_models;
};

Header header @ 0x00;
Texture textures[header.num_textures] @ header.ofs_textures;
BodyPart bodyparts[header.num_bodyparts] @ header.ofs_bodyparts;
SequenceGroup sequencegroups[header.num_sequencegroups] @ header.ofs_sequencegroups;
SkinFamily skinfamilies[header.num_skinfamilies] @ header.ofs_skinfamilies;
