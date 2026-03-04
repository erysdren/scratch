#pragma author erysdren
#pragma description Inter-Quake Model
#pragma endian little

#include <std/core.pat>
#include <std/io.pat>

import type.magic;

struct Mesh {
	u32 ofs_name;
	u32 ofs_material;
	u32 first_vertex;
	u32 num_vertices;
	u32 first_triangle;
	u32 num_triangles;

	char name[] @ header.ofs_text + ofs_name;
	char material[] @ header.ofs_text + ofs_material;
};

struct VertexArray {
	u32 type;
	u32 flags;
	u32 format;
	u32 size;
	u32 offset;
};

struct Triangle {
	u32 vertices[3];
};

struct Adjacency {
	u32 triangles[3];
};

struct Joint {
	u32 ofs_name;
	s32 parent_index;
	float translate[3];
	float rotate[4];
	float scale[3];

	char name[] @ header.ofs_text + ofs_name;
};

struct Pose {
	s32 parent_index;
	u32 channelmask;
	float channeloffset[10];
	float channelscale[10];
};

struct Anim {
	u32 ofs_name;
	u32 first_frame;
	u32 num_frames;
	float framerate;
	u32 flags;

	char name[] @ header.ofs_text + ofs_name;
};

struct Bounds {
	float bbmins[3];
	float bbmaxs[3];
	float xyradius;
	float radius;
};

struct VertexAnimationVertex {
	u32 vertex_index;
	float position[3];
	float normal[3];
};

struct VertexAnimationQuantisedVertex {
	u32 vertex_index;
	s16 position[3];
	s8 normal[3];
	padding[3];
};

struct VertexAnimationMeshFrame {
	u32 ofs_name;
	u32 first_vertex;
	u32 num_vertices;
	float scale;
	float weight;
	float epsilon;

	char name[] @ header.ofs_text + ofs_name;
};

bitfield VertexAnimationFlags {
	quantised : 1;
	deltas : 1;
	padding : 30;
};

struct VertexAnimations {
	VertexAnimationFlags flags;
	u32 num_vertices;
	u32 num_mesh_frames;
	u32 num_mesh_frames_per_mesh[header.num_meshes];
	u32 mesh_frame_start_indices[header.num_meshes];
	VertexAnimationMeshFrame mesh_frames[num_mesh_frames];

	if (flags.quantised) {
		VertexAnimationQuantisedVertex vertices[num_vertices];
	} else {
		VertexAnimationVertex vertices[num_vertices];
	}
};

struct TriangleStripsStrip {
	u32 first_index;
	u32 num_indices;
};

struct TriangleStripsMeshStrip {
	u32 first_strip;
	u32 num_strips;
};

struct TriangleStrips {
	u32 num_strips;
	u32 num_strip_indices;
	TriangleStripsMeshStrip mesh_strips[header.num_meshes];
	TriangleStripsStrip strips[num_strips];
	u16 strip_indices[num_strip_indices];
};

struct Extension {
	u32 ofs_name;
	u32 num_data;
	u32 ofs_data;
	u32 ofs_next;

	char name[] @ header.ofs_text + ofs_name;

	if (ofs_next > 0) {
		Extension next @ ofs_next;
	}

	if (name == "VERTEXANIMATIONS\0")
	{
		VertexAnimations vertexanimations @ ofs_data;
	}
	else if (name == "TRIANGLESTRIPS\0")
	{
		TriangleStrips trianglestrips @ ofs_data;
	}
};

struct Header {
	type::Magic<"INTERQUAKEMODEL\0"> magic;
	u32 version;
	u32 filesize;
	u32 flags;
	u32 num_text, ofs_text;
	u32 num_meshes, ofs_meshes;
	u32 num_vertex_arrays, num_vertices, ofs_vertex_arrays;
	u32 num_triangles, ofs_triangles, ofs_adjacency;
	u32 num_joints, ofs_joints;
	u32 num_poses, ofs_poses;
	u32 num_anims, ofs_anims;
	u32 num_frames, num_framechannels, ofs_frames, ofs_bounds;
	u32 num_comment, ofs_comment;
	u32 num_extensions, ofs_extensions;
};

// begin parsing
Header header @ 0x00;
char text[header.num_text] @ header.ofs_text;
Mesh meshes[header.num_meshes] @ header.ofs_meshes;
VertexArray vertexarrays[header.num_vertex_arrays] @ header.ofs_vertex_arrays;
Triangle triangles[header.num_triangles] @ header.ofs_triangles;
Extension extensions @ header.ofs_extensions;
