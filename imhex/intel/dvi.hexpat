#pragma author erysdren
#pragma description Intel DVI video format
#pragma endian little

import std.mem;

enum StreamType : u16 {
	CompressedAudioStream = 2,
	CompressedImageStream = 3,
	AssociatedPerFrameData = 5,
	UncompressedImageStream = 6,
	PadStream = 7
};

enum VideoSubStreamType : u16 {
	YChannelData = 1,
	UChannelData = 11,
	VChannelData = 12,
	YvuData = 13,
	YuvData = 14
};

struct DviHeader {
	char FileId[4];       /* Magic number (56445649h) of DVI file */
	s16 HeaderSize;       /* Size of this header structure */
	s16 HeaderVersion;    /* Version of this header structure */
	u32 AnnotationOffset; /* Location of annotation data */
};

struct AvlHeader {
	char HeaderId[4];          /* Header ID value (41565353h) */
	s16 HeaderSize;            /* Size of this header structure */
	s16 HeaderVersion;         /* Format of this header structure */
	s16 StreamGroupCount;      /* Number of stream groups in the file */
	s16 StreamGroupSize;       /* Size of each stream group */
	u32 StreamGroupOffset;     /* Location of the first stream group */
	s16 StreamGroupVersion;    /* Format of each stream group */
	s16 StreamSize;            /* Size of the stream header */
	s16 StreamVersion;         /* Format of the stream header */
	s16 StreamCount;           /* Number of stream headers in the file */
	u32 StreamOffset;          /* Location of stream structures array */
	u32 HeaderPoolOffset;      /* Location of substream headers */
	s32 LabelCount;            /* Number of labels in the file */
	u32 LabelOffset;           /* Location of the first label */
	s16 LabelSize;             /* Size of each label */
	s16 LabelVersion;          /* Format of each label */
	u32 VideoSeqHeaderOffset;  /* Location of video sequence header */
	u16 VideoSeqHeaderSize;    /* Size of video sequence header */
	s16 FrameVersion;          /* Version of frame headers in file */
	s32 FrameCount;            /* Number of frame headers in file */
	s32 FrameSize;             /* Size of frame header and data */
	u32 FirstFrameOffset;      /* Location of the first frame */
	u32 EndOfFrameOffset;      /* Location of last frame byte + 1 */
	s16 FrameHeaderSize;       /* Size of frame header */
	s16 FrameDirectorySize;    /* Size of the frame directory */
	u32 FrameDirectoryOffset;  /* Location of the frame directory */
	s16 FrameDirectoryVersion; /* Format of the frame directory */
	s16 FramesPerSecond;       /* Frame rate of the data */
	u32 UpdateFlag;            /* Data is updating or complete */
	u32 FreeBlockOffset;       /* Not used */
	char Patch[32];             /* Not used */
};

struct StreamHeader {
	char HeaderId[4];       /* Header ID value (5354524Dh) */
	StreamType Type;        /* The type of data stream */
	u16 SubType;            /* The subtype of data stream  */
	s16 HeaderCount;        /* Number of substream headers */
	s32 NextStreamNumber;   /* ID of the next stream */
	s16 StreamGroupNumber;  /* The group ID for this stream */
	u32 Flag;               /* Variable frame size flag */
	s32 FrameSize;          /* Maximum amount of data per frame */
	u32 FirstHeaderOffset;  /* Location of first substream header */
	char StreamName[16];    /* Name of the stream */
};

struct AudioSubStreamHeader {
	char HeaderId[4];       /* Header ID value (41554449h) */
	s16 HeaderSize;         /* Size of this header structure */
	s16 HeaderVersion;      /* Format of this header structure */
	char OriginalFile[80];  /* Name of file stream is derived from */
	s32 OriginalFrame;      /* Original frame ID */
	s16 OriginalStream;     /* Original stream ID */
	s16 Pad;                /* Pad value */
	s32 FrameCount;         /* The number of frames */
	u32 NextHeaderOffset;   /* Location of next substream header */
	char LibraryName[16];   /* Name of library stream if from */
	char AlgorithmName[16]; /* Audio compression algorithm used */
	s32 DataRate;           /* Audio data rate in bits/sec */
	s16 CutoffFrequency;    /* Filter cutoff frequency */
	s16 Parameter3;         /* Not used */
	s16 LeftVolume;         /* Loudness of left audio channel */
	s16 RightVolume;        /* Loudness of right audio channel */
	s32 LoopOffset;         /* Not used */
	s32 StartingFrame;      /* ID of the first frame in the stream */
	u32 Flag;               /* Mono/Stereo flag */
	s16 FrameRate;          /* The playback rate for this stream */
	s16 Pad2;               /* Pad value */
	s32 DCFId;              /* Digital Compression Facility ID */
};

struct VideoSubStreamHeader {
	char HeaderId[4];      /* Header ID value (h) */
	s16 HeaderSize;        /* Size of this header structure */
	s16 HeaderVersion;     /* Format of this header structure */
	char OriginalFile[80]; /* Name of file stream is derived from */
	s32 OriginalFrame;     /* Original frame ID */
	s16 OriginalStream;    /* Original stream ID */
	s16 Pad;               /* Pad value */
	s32 FrameCount;        /* Number of frames until next header */
	u32 NextHeaderOffset;  /* Location of next substream header */
	s16 XPosition;         /* X coordinate top-left corner of image */
	s16 YPosition;         /* Y coordinate top-left corner of image */
	s16 XLength;           /* Width of image */
	s16 YLength;           /* Height of image */
	s16 XCrop;             /* X cropping coordinate */
	s16 YCrop;             /* Y cropping coordinate */
	s16 DropFrame;         /* Not used */
	s16 DropPhrase;        /* Not used */
	s32 StillPeriod;       /* Frequency of intraframe images */
	s16 BufferMinimum;     /* Minimum buffer size required */
	s16 BufferMaximum;     /* Maximum buffer size required */
	s16 DecodeAlgorithm;   /* ID of the decompression algorithm */
	s16 Pad2;              /* Pad value */
	s32 DCFId;             /* Digital Compression Facility ID */
};

struct Stream {
	StreamHeader header;
	match (header.Type) {
		(StreamType::CompressedAudioStream): AudioSubStreamHeader substreams[header.HeaderCount] @ header.FirstHeaderOffset;
		(StreamType::CompressedImageStream): VideoSubStreamHeader substreams[header.HeaderCount] @ header.FirstHeaderOffset;
	}
};

struct FrameHeader {
	s32 FrameNumber;       /* Sequence number of this frame */
	s32 PreviousOffset;    /* Location of previous frame */
	s32 Checksum;          /* Checksum value for this frame */
	s32 StreamFrameSize[]; /* Array of all frame sizes */
};

struct FrameDirectory {
	u32 FrameOffset;      /* Location of the frame for this directory */
};

struct DviFile {
	DviHeader dvi_header;
	AvlHeader avl_header;
	Stream streams[avl_header.StreamCount] @ avl_header.StreamOffset;
	if (dvi_header.AnnotationOffset > 0)
	{
		char AnnotationData[] @ dvi_header.AnnotationOffset;
	}
};

DviFile dvi @ 0x00;
