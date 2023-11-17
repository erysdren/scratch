#include <stdio.h>
#include "kaitaistruct.h"
#include "lev_quake.h"
#include "pic.h"
#include "stb_image_write.h"

/* global macros */
#define LEV_TEXTURE_WIDTH  64
#define LEV_TEXTURE_HEIGHT 64

/* kaitai struct log function */
static void ks_log_func(const char *message)
{
    printf("Kaitai Struct: %s\n", message);
}

/* check extension of string */
static int check_extension(const char *string, const char *extension)
{
    if(strcmp(string + strlen(string) - strlen(extension), extension) == 0)
        return 1;
    else
        return 0;
}

/* process lev */
static void process_lev(const char *filename)
{
    ks_stream     *lev_ks_stream;
    ks_config     *lev_ks_config;
    FILE          *lev_file;
    ksx_lev_quake *lev_quake;
    ks_error       lev_ks_error;

    /* open file */
    lev_file = fopen(filename, "rb");
    if(lev_file == NULL) {
        printf("Failed to open \"%s\" for reading\n", filename);
        return;
    }

    /* open config */
    lev_ks_config = ks_config_create(ks_log_func);
    if(lev_ks_config == NULL) {
        printf("Failed to create ks_config\n");
        return;
    }

    /* open stream */
    lev_ks_stream = ks_stream_create_from_file(lev_file, lev_ks_config);
    if(lev_ks_stream == NULL) {
        printf("Failed to open \"%s\" as ks_stream\n", filename);
        return;
    }

    /* open lev */
    lev_quake = ksx_read_lev_quake_from_stream(lev_ks_stream, &lev_ks_error);
    if(lev_quake == NULL) {
        printf("Failed to read \"%s\" with error: %d\n", filename, lev_ks_error);
        return;
    }

    /* write out resources */
    for(int i = 0; i < lev_quake->resources->num_resources; i++) {

        /* get resource ptr */
        ksx_resource_t *resource = lev_quake->resources->resources->data[i];

        /* if it's a texture */
        if(resource->resource_type == 0x82) {
            ksx_texture_t       *texture;
            ksx_palette_entry_t *entry;
            char                 name[256];
            uint8_t              palette[768];
            uint8_t              pixels[LEV_TEXTURE_WIDTH * LEV_TEXTURE_HEIGHT * 3];

            /* get texture ptr */
            texture = (ksx_texture_t *)resource->data;

            /* assemble palette */
            for(int p = 0; p < texture->palette->size; p++) {
                entry                = texture->palette->data[p];
                palette[p * 3]       = entry->r * (float)(255 / 31);
                palette[(p * 3) + 1] = entry->g * (float)(255 / 31);
                palette[(p * 3) + 2] = entry->b * (float)(255 / 31);
            }

            /* assemble image */
            for(int y = 0; y < LEV_TEXTURE_HEIGHT; y++) {
                for(int x = 0; x < LEV_TEXTURE_WIDTH; x++) {
                    int pos = y * LEV_TEXTURE_WIDTH + x;

                    pixels[pos * 3]     = palette[texture->bitmap->data[pos] * 3];
                    pixels[pos * 3 + 1] = palette[texture->bitmap->data[pos] * 3 + 1];
                    pixels[pos * 3 + 2] = palette[texture->bitmap->data[pos] * 3 + 2];
                }
            }

            snprintf(name, sizeof(name), "%s_%03d.png", filename, i);
            stbi_write_png(name, LEV_TEXTURE_WIDTH, LEV_TEXTURE_HEIGHT, 3, pixels, LEV_TEXTURE_WIDTH * 3);

            printf("Successfully wrote \"%s\"\n", name);
        }
    }

    /* clean up */
    fclose(lev_file);
}

/* process pic */
void process_pic(const char *filename)
{
    ks_stream    *pic_ks_stream;
    ks_config    *pic_ks_config;
    FILE         *pic_file;
    ksx_pic      *pic;
    ks_error      pic_ks_error;
    ksx_abgr1555 *entry;
    uint8_t       palette[768];
    uint8_t      *pixels;
    char          name[256];

    /* open file */
    pic_file = fopen(filename, "rb");
    if(pic_file == NULL) {
        printf("Failed to open \"%s\" for reading\n", filename);
        return;
    }

    /* open config */
    pic_ks_config = ks_config_create(ks_log_func);
    if(pic_ks_config == NULL) {
        printf("Failed to create ks_config\n");
        return;
    }

    /* open stream */
    pic_ks_stream = ks_stream_create_from_file(pic_file, pic_ks_config);
    if(pic_ks_stream == NULL) {
        printf("Failed to open \"%s\" as ks_stream\n", filename);
        return;
    }

    /* open pic */
    pic = ksx_read_pic_from_stream(pic_ks_stream, &pic_ks_error);
    if(pic == NULL) {
        printf("Failed to read \"%s\" with error: %d\n", filename, pic_ks_error);
        return;
    }

    /* assemble palette */
    for(int p = 0; p < pic->palette->size; p++) {
        entry                = pic->palette->data[p];
        palette[p * 3]       = entry->r * (float)(255 / 31);
        palette[(p * 3) + 1] = entry->g * (float)(255 / 31);
        palette[(p * 3) + 2] = entry->b * (float)(255 / 31);
    }

    /* assemble image */
    pixels = calloc(pic->width * pic->height * 3, sizeof(uint8_t));
    for(int y = 0; y < pic->height; y++) {
        for(int x = 0; x < pic->width; x++) {
            int pos = y * pic->width + x;

            pixels[pos * 3]     = palette[pic->bitmap->data[pos] * 3];
            pixels[pos * 3 + 1] = palette[pic->bitmap->data[pos] * 3 + 1];
            pixels[pos * 3 + 2] = palette[pic->bitmap->data[pos] * 3 + 2];
        }
    }

    /* write image */
    snprintf(name, sizeof(name), "%s.png", filename);
    stbi_write_png(name, pic->width, pic->height, 3, pixels, pic->width * 3);
    printf("Successfully wrote \"%s\"\n", name);

    /* clean up */
    free(pixels);
    fclose(pic_file);
}

/* main */
int main(int argc, char *argv[])
{
    /* process all files given on cmd */
    for(int i = 1; i < argc; i++) {
        if(check_extension(argv[i], ".LEV") || check_extension(argv[i], ".lev")) {
            process_lev(argv[i]);
        } else if(check_extension(argv[i], ".PIC") || check_extension(argv[i], ".pic")) {
            process_pic(argv[i]);
        } else {
            printf("\"%s\" does not have a recognized file extension\n", argv[i]);
            return 1;
        }
    }

    /* return success */
    return 0;
}
