/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdint.h>

/* macros */
#define DEBUG 1
#define MZ_MAGIC "MZ"
#define NE_OFFSET 60
#define NE_MAGIC "NE"

/* zero alloc */
#define zalloc(s) calloc(1, s)

/* error print */
#define eprint(...) fprintf(stderr, __VA_ARGS__)

/* debug print */
#if DEBUG
#define dprint(...) fprintf(stdout, __VA_ARGS__)
#else
#define dprint(...)
#endif

/* windows types */
typedef char CHAR;
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;

/* windows ne header */
typedef struct NeHeader
{
    CHAR sig[2];             //"NE"
    BYTE MajLinkerVersion;   // The major linker version
    BYTE MinLinkerVersion;   // The minor linker version
    WORD EntryTableOffset;   // Offset of entry table, see below
    WORD EntryTableLength;   // Length of entry table in bytes
    DWORD FileLoadCRC;       // 32-bit CRC of entire contents of file
    BYTE ProgFlags;          // Program flags, bitmapped
    BYTE ApplFlags;          // Application flags, bitmapped
    WORD AutoDataSegIndex;   // The automatic data segment index
    WORD InitHeapSize;       // The initial local heap size
    WORD InitStackSize;      // The initial stack size
    DWORD EntryPoint;        // CS:IP entry point, CS is index into segment table
    DWORD InitStack;         // SS:SP initial stack pointer, SS is index into segment
                             // table
    WORD SegCount;           // Number of segments in segment table
    WORD ModRefs;            // Number of module references (DLLs)
    WORD NoResNamesTabSiz;   // Size of non-resident names table, in bytes
                             // (Please clarify non-resident names table)
    WORD SegTableOffset;     // Offset of Segment table
    WORD ResTableOffset;     // Offset of resources table
    WORD ResidNamTable;      // Offset of resident names table
    WORD ModRefTable;        // Offset of module reference table
    WORD ImportNameTable;    // Offset of imported names table (array of counted
                             // strings, terminated with string of length 00h)
    DWORD OffStartNonResTab; // Offset from start of file to non-resident
                             // names table
    WORD MovEntryCount;      // Count of moveable entry point listed in entry table
    WORD FileAlnSzShftCnt;   // File alignment size shift count (0=9(default
                             // 512 byte pages))
    WORD nResTabEntries;     // Number of resource table entries
    BYTE targOS;             // Target OS
    BYTE OS2EXEFlags;        // Other OS/2 flags
    WORD retThunkOffset;     // Offset to return thunks or start of gangload
                             // area - what is gangload?
    WORD segrefthunksoff;    // Offset to segment reference thunks or size of
                             // gangload area
    WORD mincodeswap;        // Minimum code swap area size
    BYTE expctwinver[2];     // Expected windows version (minor first)
} NeHeader;

/* name info */
typedef struct NeNameInfo
{
    WORD rnOffset;
    WORD rnLength;
    WORD rnFlags;
    WORD rnID;
    WORD rnHandle;
    WORD rnUsage;
} NeNameInfo;

/* resource */
typedef struct NeResource
{
    WORD rtTypeID;
    WORD rtResourceCount;
    DWORD rtReserved;
    NeNameInfo *rtNameInfo;
} NeResource;

/* resource table */
typedef struct NeResourceTable
{
    WORD rscAlignShift;
    NeResource *rscTypes;
    WORD rscEndTypes;
    BYTE *rscResourceNames;
    BYTE rscEndNames;
} NeResourceTable;
