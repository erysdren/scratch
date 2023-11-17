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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vtf.h"

#include "dxt.h"

/* vtf magic bytes */
static const char vtf_magic[4] = {'V', 'T', 'F', 0x00};

/* load from file */
vtf_t *vtf_from_file(const char *vtf_filename)
{
    /* variables */
    vtf_t *vtf;
    FILE *vtf_file;

    /* open vtf file */
    vtf_file = fopen(vtf_filename, "rb");
    if (!vtf_file)
        return NULL;

    /* allocate structure */
    vtf = calloc(1, sizeof(vtf_t));
    if (!vtf)
        return NULL;

    /* read and test magic */
    fread(vtf->magic, sizeof(char), 4, vtf_file);
    if (memcmp(vtf_magic, vtf->magic, 4) != 0)
        return NULL;

    /* read the rest of the header */
    fread(vtf->version, sizeof(uint32_t), 2, vtf_file);
    fread(&vtf->len_header, sizeof(uint32_t), 1, vtf_file);
    fread(&vtf->width, sizeof(uint16_t), 1, vtf_file);
    fread(&vtf->height, sizeof(uint16_t), 1, vtf_file);
    fread(&vtf->flags, sizeof(uint32_t), 1, vtf_file);
    fread(&vtf->num_frames, sizeof(uint16_t), 1, vtf_file);
    fread(&vtf->first_frame, sizeof(int16_t), 1, vtf_file);

    /* seek past padding */
    fseek(vtf_file, 4, SEEK_CUR);

    /* read more header */
    fread(vtf->reflectivity, sizeof(float), 3, vtf_file);

    /* seek past padding */
    fseek(vtf_file, 4, SEEK_CUR);

    /* read more header */
    fread(&vtf->bumpmap_scale, sizeof(float), 1, vtf_file);
    fread(&vtf->format, sizeof(uint32_t), 1, vtf_file);
    fread(&vtf->num_mipmaps, sizeof(uint8_t), 1, vtf_file);
    fread(&vtf->thumbnail_format, sizeof(uint32_t), 1, vtf_file);
    fread(&vtf->thumbnail_width, sizeof(uint8_t), 1, vtf_file);
    fread(&vtf->thumbnail_height, sizeof(uint8_t), 1, vtf_file);

    /* seek past header */
    fseek(vtf_file, vtf->len_header, SEEK_SET);

    /* read thumbnail */
    vtf->len_thumbnail = (vtf->thumbnail_width * vtf->thumbnail_height * 4) / 8;
    vtf->thumbnail = calloc(vtf->len_thumbnail, sizeof(uint8_t));
    fread(vtf->thumbnail, sizeof(uint8_t), vtf->len_thumbnail, vtf_file);

    /* decompress thumbnail */
    vtf->len_thumbnail_uncompressed = vtf->len_thumbnail * 8;
    vtf->thumbnail_uncompressed = calloc(vtf->len_thumbnail_uncompressed, sizeof(uint8_t));

    for (int y = 0; y < vtf->thumbnail_height; y++)
    {
        for (int x = 0; x < vtf->thumbnail_width; x++)
        {
            DecompressBlockBC1(x, y, vtf->thumbnail_width, vtf->thumbnail, vtf->thumbnail_uncompressed);
        }
    }

    /* close file */
    fclose(vtf_file);

    /* return ptr */
    return vtf;
}

/* free memory */
void vtf_free(vtf_t *vtf)
{
    if (vtf)
    {
        if (vtf->thumbnail)
            free(vtf->thumbnail);

        if (vtf->thumbnail_uncompressed)
            free(vtf->thumbnail_uncompressed);

        free(vtf);
    }
}
