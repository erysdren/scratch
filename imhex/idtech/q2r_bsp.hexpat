#pragma author erysdren
#pragma description Quake II Remastered BSP Format
#pragma endian little

#include <std/core.pat>
#include <std/io.pat>

// i don't wanna use an enum for this
u32 LUMP_ENTITIES = 0;
u32 LUMP_PLANES = 1;
u32 LUMP_VERTEXES = 2;
u32 LUMP_VISIBILITY = 3;
u32 LUMP_NODES = 4;
u32 LUMP_TEXINFO = 5;
u32 LUMP_FACES = 6;
u32 LUMP_LIGHTING = 7;
u32 LUMP_LEAFS = 8;
u32 LUMP_LEAFFACES = 9;
u32 LUMP_LEAFBRUSHES = 10;
u32 LUMP_EDGES = 11;
u32 LUMP_SURFEDGES = 12;
u32 LUMP_MODELS = 13;
u32 LUMP_BRUSHES = 14;
u32 LUMP_BRUSHSIDES = 15;
u32 LUMP_POP = 16;
u32 LUMP_AREAS = 17;
u32 LUMP_AREAPORTALS = 18;
u32 NUM_LUMPS = 19;

struct Vec3f {
	float x, y, z;
};

struct Vec3s {
	s16 x, y, z;
};

struct Plane {
	Vec3f normal;
	float distance;
	u32 type;
};

struct VisCluster {
	u32 pvs;
	u32 phs;
};

struct Vis {
	u32 num_clusters;
	VisCluster clusters[num_clusters];
};

struct Node {
	u32 plane;
	s32 front_child;
	s32 back_child;
	Vec3s minsize;
	Vec3s maxsize;
	u16 first_face;
	u16 num_face;
};

struct Texinfo {
	Vec3f u_axis;
	float u_offset;
	Vec3f v_axis;
	float v_offset;
	u32 flags;
	u32 value;
	char texture_name[32];
	u32 next_texinfo;
};

struct Face {
	u16 plane;
	u16 plane_side;
	u32 first_edge;
	u16 num_edges;
	u16 texinfo;
	u8 lightmap_styles[4];
	u32 lightmap_offset;
};

struct Leaf {
	u32 brush_or;
	u16 cluster;
	u16 area;
	Vec3s minsize;
	Vec3s maxsize;
	u16 first_leaf_face;
	u16 num_leaf_faces;
	u16 first_leaf_brush;
	u16 num_leaf_brushes;
};

struct Lump {
	u32 offset;
	u32 size;

	match (std::core::array_index()) {
		(LUMP_ENTITIES): char entities[size] @ offset;
		(LUMP_PLANES): Plane planes[size / sizeof(Plane)] @ offset;
		(LUMP_VERTEXES): Vec3f vertexes[size / sizeof(Vec3f)] @ offset;
		(LUMP_VISIBILITY): Vis vis @ offset;
		(LUMP_NODES): Node nodes[size / sizeof(Node)] @ offset;
		(LUMP_TEXINFO): Texinfo texinfo[size / sizeof(Texinfo)] @ offset;
		(LUMP_FACES): Face faces[size / sizeof(Face)] @ offset;
		(LUMP_LIGHTING): u8 lightmap[size] @ offset;
		(LUMP_LEAFS): Leaf leafs[size / sizeof(Leaf)] @ offset;
		(LUMP_LEAFFACES): u16 leaf_faces[size / sizeof(u16)] @ offset;
		// (_): u8 data[size] @ offset;
	}
};

struct BSP {
	u32 magic;
	u32 version;
	Lump lumps[NUM_LUMPS];
};

BSP bsp @ 0x00;
