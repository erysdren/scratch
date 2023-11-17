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

#include <zlib.h>

#include "tth.h"

/* tth magic bytes */
static const char tth_magic[4] = {'T', 'T', 'H', 0x00};

/* load from file */
tth_t *tth_from_file(const char *tth_filename, const char *ttz_filename)
{
    /* variables */
    tth_t *tth;
    FILE *tth_file, *ttz_file;

    /* open tth file */
    tth_file = fopen(tth_filename, "rb");
    if (!tth_file)
        return NULL;

    /* allocate structure */
    tth = calloc(1, sizeof(tth_t));
    if (!tth)
        return NULL;

    /* read and test magic */
    fread(tth->magic, sizeof(char), 4, tth_file);
    if (memcmp(tth_magic, tth->magic, 4) != 0)
        return NULL;

    /* read the rest of the structure */
    fread(tth->version, sizeof(uint8_t), 2, tth_file);
    fread(&tth->num_mipmaps, sizeof(uint8_t), 1, tth_file);
    fread(&tth->aspect_flag, sizeof(uint8_t), 1, tth_file);
    fread(&tth->len_vtf_chunk, sizeof(int32_t), 1, tth_file);

    /* allocate and read mipmap flags */
    if (tth->num_mipmaps)
    {
        tth->mipmap_flags = calloc(tth->num_mipmaps, sizeof(uint64_t));
        fread(tth->mipmap_flags, sizeof(uint64_t), tth->num_mipmaps, tth_file);
    }

    /* read more data */
    fread(&tth->len_vtf_file, sizeof(int32_t), 1, tth_file);
    fread(&tth->len_ttz_tail, sizeof(int32_t), 1, tth_file);

    /* read vtf chunk */
    if (tth->len_vtf_chunk)
    {
        tth->vtf_chunk = calloc(tth->len_vtf_chunk, sizeof(uint8_t));
        fread(tth->vtf_chunk, sizeof(uint8_t), tth->len_vtf_chunk, tth_file);
    }

    /* read compressed ttz data */
    if (tth->len_ttz_tail)
    {
        /* allocate space for compressed data */
        tth->ttz_compressed = calloc(tth->len_ttz_tail, sizeof(uint8_t));

        /* open compressed file */
        ttz_file = fopen(ttz_filename, "rb");
        if (!ttz_file)
            return NULL;

        /* read compressed data */
        fread(tth->ttz_compressed, sizeof(uint8_t), tth->len_ttz_tail, ttz_file);

        /* close file */
        fclose(ttz_file);
    }

    /* close file */
    fclose(tth_file);

    /* return ptr */
    return tth;
}

/* decompress with zlib */
int tth_decompress_ttz(tth_t *tth)
{
    z_stream stream;
    int result;

    /* no compressed data to process */
    if (tth->ttz_compressed == NULL)
        return 0;

    /* it's already been done? */
    if (tth->ttz_uncompressed != NULL)
        return 0;

    /* allocate uncompressed buffer */
    tth->ttz_uncompressed = calloc(tth->len_vtf_file - tth->len_vtf_chunk, sizeof(uint8_t));

    /* setup zlib stream */
    memset(&stream, 0, sizeof(z_stream));
    stream.next_in = tth->ttz_compressed;
    stream.avail_in = tth->len_ttz_tail;
    stream.next_out = tth->ttz_uncompressed;
    stream.avail_out = tth->len_vtf_file - tth->len_vtf_chunk;

    /* initialize zlib */
    result = inflateInit(&stream);
    if (result < 0)
        return 0;

    /* do inflate */
    result = inflate(&stream, Z_FINISH);
    if (result < 0)
        return 0;

    /* clean up stream */
    result = inflateEnd(&stream);
    if (result < 0)
        return 0;

    /* return success */
    return 1;
}

/* write decompressed vtf to disk */
int tth_write_vtf(tth_t *tth, const char *vtf_filename)
{
    FILE *vtf;

    /* open output filename */
    vtf = fopen(vtf_filename, "wb");
    if (!vtf)
        return 0;

    /* write vtf chunk */
    if (tth->vtf_chunk)
        fwrite(tth->vtf_chunk, sizeof(uint8_t), tth->len_vtf_chunk, vtf);

    /* write uncompressed data */
    if (tth->ttz_uncompressed)
        fwrite(tth->ttz_uncompressed, sizeof(uint8_t), tth->len_vtf_file - tth->len_vtf_chunk, vtf);

    /* close */
    fclose(vtf);

    /* return success */
    return 1;
}

/* free memory */
void tth_free(tth_t *tth)
{
    if (tth)
    {
        if (tth->mipmap_flags)
            free(tth->mipmap_flags);

        if (tth->vtf_chunk)
            free(tth->vtf_chunk);

        if (tth->ttz_compressed)
            free(tth->ttz_compressed);

        if (tth->ttz_uncompressed)
            free(tth->ttz_uncompressed);

        free(tth);
    }
}
