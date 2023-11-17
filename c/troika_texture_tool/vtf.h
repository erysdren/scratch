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

#ifndef _VTF_H_
#define _VTF_H_
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/**
 * VTF image formats;
 */
enum
{
    VTF_FORMAT_NONE = -1,
    VTF_FORMAT_RGBA8888 = 0,
    VTF_FORMAT_ABGR8888,
    VTF_FORMAT_RGB888,
    VTF_FORMAT_BGR888,
    VTF_FORMAT_RGB565,
    VTF_FORMAT_I8,
    VTF_FORMAT_IA88,
    VTF_FORMAT_P8,
    VTF_FORMAT_A8,
    VTF_FORMAT_RGB888_BLUESCREEN,
    VTF_FORMAT_BGR888_BLUESCREEN,
    VTF_FORMAT_ARGB8888,
    VTF_FORMAT_BGRA8888,
    VTF_FORMAT_DXT1,
    VTF_FORMAT_DXT3,
    VTF_FORMAT_DXT5,
    VTF_FORMAT_BGRX8888,
    VTF_FORMAT_BGR565,
    VTF_FORMAT_BGRX5551,
    VTF_FORMAT_BGRA4444,
    VTF_FORMAT_DXT1_ONEBITALPHA,
    VTF_FORMAT_BGRA5551,
    VTF_FORMAT_UV88,
    VTF_FORMAT_UVWQ8888,
    VTF_FORMAT_RGBA16161616F,
    VTF_FORMAT_RGBA16161616,
    VTF_FORMAT_UVLX8888
};

/**
 * VTF file representation in memory.
 */
typedef struct vtf_t
{
    /**
     * VTF file magic.
     */
    char magic[4];

    /**
     * VTF file version.
     */
    uint32_t version[2];

    /**
     * Length of header. 16 byte aligned.
     */
    uint32_t len_header;

    /**
     * Width of the largest mipmap.
     */
    uint16_t width;

    /**
     * Height of the largest mipmap.
     */
    uint16_t height;

    /**
     * VTF flags.
     */
    uint32_t flags;

    /**
     * Number of animation frames.
     */
    uint16_t num_frames;

    /**
     * First frame in animation.
     */
    int16_t first_frame;

    /**
     * Reflectivity vector.
     */
    float reflectivity[3];

    /**
     * Bumpmap scale.
     */
    float bumpmap_scale;

    /**
     * VTF format.
     */
    uint32_t format;

    /**
     * Number of mipmaps.
     */
    uint8_t num_mipmaps;

    /**
     * VTF thumbnail format.
     */
    uint32_t thumbnail_format;

    /**
     * Thumbnail width.
     */
    uint8_t thumbnail_width;

    /**
     * Thumbnail height.
     */
    uint8_t thumbnail_height;

    /**
     * Size of thumbnail buffer;
     */
    uint32_t len_thumbnail;

    /**
     * Thumbnail buffer.
     */
    void *thumbnail;

    /**
     * Size of uncompressed thumbnail buffer;
     */
    uint32_t len_thumbnail_uncompressed;

    /**
     * Uncompressed thumbnail buffer.
     */
    void *thumbnail_uncompressed;

} vtf_t;

/**
 * Assemble a VTF structure from a VTF file.
 *
 * @param vtf_filename The name of the VTF file.
 */
vtf_t *vtf_from_file(const char *vtf_filename);

/**
 * Free all memory associated with a VTF structure.
 *
 * @param vtf The VTF structure to free.
 */
void vtf_free(vtf_t *vtf);

#ifdef __cplusplus
}
#endif
#endif /* _VTF_H_ */
