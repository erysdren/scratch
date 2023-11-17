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

#include "tth.h"
#include "vtf.h"

#include "stb_image_write.h"

int main(int argc, char *argv[])
{
    tth_t *tth;
    vtf_t *vtf;

    /* very specific use case */
    if (argc != 4)
    {
        printf("troika texture tool usage:\nttt <texture.tth> <texture.ttz> <texture.vtf>\n");
        return 0;
    }

    /* load tth from disk */
    tth = tth_from_file(argv[1], argv[2]);
    if (tth == NULL)
    {
        printf("failed to open %s\n", argv[1]);
        return 1;
    }
    else
    {
        printf("successfully opened %s\n", argv[1]);
    }

    /* decompress vtf data */
    if (!tth_decompress_ttz(tth))
    {
        printf("failed to decompress %s\n", argv[2]);
        return 1;
    }
    else
    {
        printf("successfully decompressed %s\n", argv[2]);
    }

    /* write vtf to disk */
    if (!tth_write_vtf(tth, argv[3]))
    {
        printf("failed to write %s\n", argv[3]);
        return 1;
    }
    else
    {
        printf("successfully wrote %s\n", argv[3]);
    }

    /* free tth memory */
    tth_free(tth);

    /* return success */
    return 0;
}
