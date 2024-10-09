#pragma author erysdren
#pragma description Quake II Remastered BSP Format
#pragma endian little

#include <std/core.pat>
#include <std/io.pat>

struct IqmHeader {
	char magic[16];
	u32 version;
	u32 filesize;
	u32 flags;
	u32 num_text, ofs_text;
	u32 num_meshes, ofs_meshes;
	u32 num_vertexarrays, num_vertexes, ofs_vertexarrays;
	u32 num_triangles, ofs_triangles, ofs_adjacency;
	u32 num_joints, ofs_joints;
	u32 num_poses, ofs_poses;
	u32 num_anims, ofs_anims;
	u32 num_frames, num_framechannels, ofs_frames, ofs_bounds;
	u32 num_comment, ofs_comment;
	u32 num_extensions, ofs_extensions;
};

struct IqmMesh {
	u32 ofs_name;
	u32 ofs_material;
	u32 first_vertex, num_vertexes;
	u32 first_triangle, num_triangles;

	char name[] @ parent.header.ofs_text + ofs_name;
	char material[] @ parent.header.ofs_text + ofs_material;
};

struct Iqm {
	IqmHeader header;
	char text[header.num_text] @ header.ofs_text;
	IqmMesh meshes[header.num_meshes] @ header.ofs_meshes;
};

Iqm iqm @ 0x00;
