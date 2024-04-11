#pragma author erysdren
#pragma description BRender Datafile
#pragma endian big

import std.mem;

//
// Chunk enums
//

enum BrChunkType : u32 {
	END,
	IMAGE_PLANE,
	RLE_IMAGE_PLANE,
	OLD_PIXELMAP,
	MATERIAL_OLDEST,
	ADD_MATERIAL,
	OLD_ACTOR,
	OLD_ADD_SIBLING,
	OLD_ADD_CHILD,
	OLD_MATERIAL_INDEX,
	OLD_VERTICES,
	OLD_VERTICES_UV,
	OLD_FACES,
	OLD_MODEL,
	ADD_MODEL,
	ANIM,
	ANIM_TRANSFORM,
	ANIM_RATE,
	FILE_INFO,
	OLD_LIGHT,
	OLD_CAMERA,
	PIVOT,
	MATERIAL_INDEX,
	VERTICES,
	VERTEX_UV,
	OLD_FACES_1,
	FACE_MATERIAL,
	OLD_MODEL_1,
	COLOUR_MAP_REF,
	OPACITY_MAP_REF,
	INDEX_BLEND_REF,
	INDEX_SHADE_REF,
	SCREENDOOR_REF,
	PIXELS,
	ADD_MAP,
	ACTOR,
	ACTOR_MODEL,
	ACTOR_TRANSFORM,
	ACTOR_MATERIAL,
	ACTOR_LIGHT,
	ACTOR_CAMERA,
	ACTOR_BOUNDS,
	ACTOR_ADD_CHILD,
	TRANSFORM_MATRIX34,
	TRANSFORM_MATRIX34_LP,
	TRANSFORM_QUAT,
	TRANSFORM_EULER,
	TRANSFORM_LOOK_UP,
	TRANSFORM_TRANSLATION,
	TRANSFORM_IDENTITY,
	BOUNDS,
	LIGHT_OLD,
	CAMERA,
	FACES,
	OLD_MODEL_2,
	ACTOR_CLIP_PLANE,
	PLANE,
	SATURN_FACES,
	SATURN_MODEL,
	INDEX_FOG_REF,
	MATERIAL_OLD,
	PIXELMAP,
	MATERIAL,
	LIGHT,
	MODEL,
	VERTEX_COLOUR,
	VERTEX_NORMAL,
	FACE_COLOUR,
	FACE_EQUATION
};

enum BrFileInfoType : u32 {
	NONE,
	ACTORS,
	PIXELMAP,
	LIGHT,
	CAMERA,
	MATERIAL_OLD,
	MATERIAL,
	MODEL = 0xFACE,
	ANIMATION = 0x0A11,
	TREE = 0x5EED
};

enum BrPixelmapType : u8 {
	BR_PMT_INDEX_1,
	BR_PMT_INDEX_2,
	BR_PMT_INDEX_4,
	BR_PMT_INDEX_8,
	BR_PMT_RGB_555,
	BR_PMT_RGB_565,
	BR_PMT_RGB_888,
	BR_PMT_RGBX_888,
	BR_PMT_RGBA_8888,
	BR_PMT_YUYV_8888,
	BR_PMT_YUV_888,
	BR_PMT_DEPTH_16,
	BR_PMT_DEPTH_32,
	BR_PMT_ALPHA_8,
	BR_PMT_INDEXA_88
};

struct BrChunkHeader {
	BrChunkType Type;
	u32 Size;
};

union BrScalar {
	float f;
	u32 x;
};

struct BrVector2 {
	BrScalar x, y;
};

struct BrVector3 {
	BrScalar x, y, z;
};

struct BrColour {
	u8 Red;
	u8 Green;
	u8 Blue;
};

struct BrVertexColour {
	u8 Index;
	u8 Red;
	u8 Green;
	u8 Blue;
};

struct BrFace {
	u16 Vertices[3];
	u16 Smoothing;
	u8 Flags;
};

using BrUV = BrVector2;
using BrVertex = BrVector3;
using BrVertexNormal = BrVector3;
using BrUFraction = BrScalar;
using BrAngle = u16;

//
// Chunk data
//

// OLD_PIXELMAP
struct BrOldPixelmapChunk {
	BrPixelmapType Type;
	u16 RowBytes;
	u16 Width;
	u16 Height;
	u16 Origin[2];
	char Identifier[];
};

// FILE_INFO
struct BrFileInfoChunk {
	BrFileInfoType Type;
	u32 Version;
};

// VERTICES
struct BrVerticesChunk {
	u32 NumVertices;
	BrVertex Vertices[NumVertices];
};

// VERTEX_UV
struct BrVertexUvChunk {
	u32 NumUVs;
	BrUV UVs[NumUVs];
};

// COLOUR_MAP_REF
struct BrColourMapRefChunk {
	char Identifier[];
};

// PIXELS
struct BrPixelsChunk {
	u32 NumPixels;
	u32 PixelSize;
	match (PixelSize) {
		(1): u8 PixelData[NumPixels];
		(2): u16 PixelData[NumPixels];
		(3): u24 PixelData[NumPixels];
		(4): u32 PixelData[NumPixels];
	}
};

// PIXELMAP
struct BrPixelmapChunk {
	BrPixelmapType Type;
	u16 RowBytes;
	u16 Width;
	u16 Height;
	u16 Origin[2];
	u16 MipOffset;
	char Identifier[];
};

// MATERIAL
struct BrMaterialChunk {
	BrColour Colour;
	u8 Opacity;
	BrUFraction ka;
	BrUFraction kd;
	BrUFraction ks;
	BrScalar Power;
	u32 Flags;
	BrVector2 TransformMap[3];
	u16 Mode;
	u8 IndexBase;
	u8 IndexRange;
	BrScalar FogMin;
	BrScalar FogMax;
	BrColour FogColour;
	s32 SubdivideTolerance;
	char Identifier[];
};

// FACES
struct BrFacesChunk {
	u32 NumFaces;
	BrFace Faces[NumFaces];
};

// MODEL
struct BrModelChunk {
	u16 Flags;
	BrVector3 Pivot;
	BrAngle CreaseAngle;
	BrScalar Radius;
	BrVector3 MinBounds;
	BrVector3 MaxBounds;
	char Identifier[];
};

// VERTEX_COLOUR
struct BrVertexColourChunk {
	u32 NumVertexColours;
	BrVertexColour VertexColours[NumVertexColours];
};

// VERTEX_NORMAL
struct BrVertexNormalChunk {
	u32 NumVertexNormals;
	BrVertexNormal VertexNormals[NumVertexNormals];
};

//
// Main chunk structure
//

struct BrChunk {
	BrChunkHeader Header;
	match (Header.Type) {
		(BrChunkType::OLD_PIXELMAP): BrOldPixelmapChunk;
		(BrChunkType::FILE_INFO): BrFileInfoChunk;
		(BrChunkType::VERTICES): BrVerticesChunk;
		(BrChunkType::VERTEX_UV): BrVertexUvChunk;
		(BrChunkType::COLOUR_MAP_REF): BrColourMapRefChunk;
		(BrChunkType::PIXELS): BrPixelsChunk;
		(BrChunkType::PIXELMAP): BrPixelmapChunk;
		(BrChunkType::MATERIAL): BrMaterialChunk;
		(BrChunkType::FACES): BrFacesChunk;
		(BrChunkType::MODEL): BrModelChunk;
		(BrChunkType::VERTEX_COLOUR): BrVertexColourChunk;
		(BrChunkType::VERTEX_NORMAL): BrVertexNormalChunk;
		(_): padding[Header.Size];
	}
};

BrChunk chunks[while (!std::mem::eof())] @ 0x00;
