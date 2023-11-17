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

#ifndef _TTH_H_
#define _TTH_H_
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/**
 * TTH/TTZ file pair representation in memory.
 */
typedef struct tth_t
{
    /**
     * TTH file magic.
     */
    char magic[4];

    /**
     * TTH file version.
     */
    uint8_t version[2];

    /**
     * Number of mipmaps in the output VTF.
     */
    uint8_t num_mipmaps;

    /**
     * Aspect ratio flag.
     */
    uint8_t aspect_flag;

    /**
     * Size of uncompressed VTF data after TTH header.
     */
    int32_t len_vtf_chunk;

    /**
     * Mipmap flags.
     */
    uint64_t *mipmap_flags;

    /**
     * Size of uncompressed VTF file.
     */
    int32_t len_vtf_file;

    /**
     * Size of compressed TTZ file.
     */
    int32_t len_ttz_tail;

    /**
     * Pointer to uncompressed VTF chunk.
     */
    void *vtf_chunk;

    /**
     * Pointer to compressed TTZ data.
     */
    void *ttz_compressed;

    /**
     * Pointer to uncompressed TTZ data. Only valid after calling tth_decompress_ttz.
     */
    void *ttz_uncompressed;
} tth_t;

/**
 * Assemble a TTH structure from a TTH and TTZ file pair.
 *
 * @param tth_filename The name of the TTH file.
 *
 * @param ttz_filename The name of the TTZ file.
 */
tth_t *tth_from_file(const char *tth_filename, const char *ttz_filename);

/**
 * Assemble VTF data from TTH structure and write it to disk.
 *
 * @param tth The TTH structure to use.
 *
 * @param vtf_filename The name of the output file.
 */
int tth_write_vtf(tth_t *tth, const char *vtf_filename);

/**
 * Decompress the TTZ data stored in the TTH structure.
 *
 * @param tth The TTH structure to decompress.
 */
int tth_decompress_ttz(tth_t *tth);

/**
 * Free all memory associated with a TTH structure.
 *
 * @param tth The TTH structure to free.
 */
void tth_free(tth_t *tth);

#ifdef __cplusplus
}
#endif
#endif /* _TTH_H_ */
