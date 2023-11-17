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

/*
 * http://fileformats.archiveteam.org/wiki/New_Executable
 * https://wiki.osdev.org/NE
 * http://web.archive.org/web/20041124165645/http://www.csn.ul.ie/~caolan/pub/winresdump/winresdump/doc/winexe.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main(int argc, char *argv[])
{
    NeHeader *header;
    char magic[2];
    DWORD offset;
    FILE *file;

    /* open file */
    file = fopen(argv[1], "rb");
    dprint("Successfully opened \"%s\"\n", argv[1]);

    /* check if its mz */
    dprint("Checking if \"%s\" is a valid MZ executable...\n", argv[1]);
    fread(magic, sizeof(char), 2, file);
    if (memcmp(magic, MZ_MAGIC, 2) != 0)
    {
        eprint("\"%s\" is not a valid MZ executable\n", argv[1]);
        fclose(file);
        return 1;
    }
    dprint("\"%s\" is a valid MZ executable\n", argv[1]);

    /* seek to ne header */
    fseek(file, NE_OFFSET, SEEK_SET);
    fread(&offset, sizeof(DWORD), 1, file);
    fseek(file, offset, SEEK_SET);

    /* check if its ne */
    dprint("Checking if \"%s\" is a valid NE executable...\n", argv[1]);
    fread(magic, sizeof(char), 2, file);
    if (memcmp(magic, NE_MAGIC, 2) != 0)
    {
        eprint("\"%s\" is not a valid NE executable\n", argv[1]);
        fclose(file);
        return 1;
    }
    dprint("\"%s\" is a valid NE executable\n", argv[1]);

    /* allocate header */
    header = zalloc(sizeof(NeHeader));

    /* read header */
    fseek(file, offset, SEEK_SET);
    fread(header, sizeof(NeHeader), 1, file);

    /* seek to resource table */
    fseek(file, offset + header->ResTableOffset, SEEK_SET);

    /* close file and free memory */
    fclose(file);
    free(header);

    /* return happily */
    return 0;
}
