/*
 * SPDX-FileCopyrightText: 2021 CSC - IT Center for Science Ltd. <www.csc.fi>
 *
 * SPDX-License-Identifier: MIT
 */

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "pngwriter.h"

/* Datatype for RGB pixel */
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

void cmap(const int value, const int max_val, pixel_t *pix);

/* Heat colormap from black to white */
// *INDENT-OFF*
static int heat_colormap[256][3] = {
    {  0,   0,   0}, { 35,   0,   0}, { 52,   0,   0}, { 60,   0,   0},
    { 63,   1,   0}, { 64,   2,   0}, { 68,   5,   0}, { 69,   6,   0},
    { 72,   8,   0}, { 74,  10,   0}, { 77,  12,   0}, { 78,  14,   0},
    { 81,  16,   0}, { 83,  17,   0}, { 85,  19,   0}, { 86,  20,   0},
    { 89,  22,   0}, { 91,  24,   0}, { 92,  25,   0}, { 94,  26,   0},
    { 95,  28,   0}, { 98,  30,   0}, {100,  31,   0}, {102,  33,   0},
    {103,  34,   0}, {105,  35,   0}, {106,  36,   0}, {108,  38,   0},
    {109,  39,   0}, {111,  40,   0}, {112,  42,   0}, {114,  43,   0},
    {115,  44,   0}, {117,  45,   0}, {119,  47,   0}, {119,  47,   0},
    {120,  48,   0}, {122,  49,   0}, {123,  51,   0}, {125,  52,   0},
    {125,  52,   0}, {126,  53,   0}, {128,  54,   0}, {129,  56,   0},
    {129,  56,   0}, {131,  57,   0}, {132,  58,   0}, {134,  59,   0},
    {134,  59,   0}, {136,  61,   0}, {137,  62,   0}, {137,  62,   0},
    {139,  63,   0}, {139,  63,   0}, {140,  65,   0}, {142,  66,   0},  
    {148,  71,   0}, {149,  72,   0}, {149,  72,   0}, {151,  73,   0},
    {151,  73,   0}, {153,  75,   0}, {153,  75,   0}, {154,  76,   0},
    {154,  76,   0}, {154,  76,   0}, {156,  77,   0}, {156,  77,   0},
    {157,  79,   0}, {157,  79,   0}, {159,  80,   0}, {159,  80,   0},
    {159,  80,   0}, {160,  81,   0}, {160,  81,   0}, {162,  82,   0},
    {162,  82,   0}, {163,  84,   0}, {163,  84,   0}, {165,  85,   0},
    {165,  85,   0}, {166,  86,   0}, {166,  86,   0}, {166,  86,   0},
    {168,  87,   0}, {168,  87,   0}, {170,  89,   0}, {170,  89,   0},
    {171,  90,   0}, {171,  90,   0}, {173,  91,   0}, {173,  91,   0},
    {174,  93,   0}, {174,  93,   0}, {176,  94,   0}, {176,  94,   0},
    {177,  95,   0}, {177,  95,   0}, {179,  96,   0}, {179,  96,   0},
    {180,  98,   0}, {182,  99,   0}, {182,  99,   0}, {183, 100,   0},
    {183, 100,   0}, {185, 102,   0}, {185, 102,   0}, {187, 103,   0},
    {187, 103,   0}, {188, 104,   0}, {188, 104,   0}, {190, 105,   0},
    {191, 107,   0}, {191, 107,   0}, {193, 108,   0}, {193, 108,   0},
    {194, 109,   0}, {196, 110,   0}, {196, 110,   0}, {197, 112,   0},
    {197, 112,   0}, {199, 113,   0}, {200, 114,   0}, {200, 114,   0},
    {202, 116,   0}, {202, 116,   0}, {204, 117,   0}, {205, 118,   0},
    {205, 118,   0}, {207, 119,   0}, {208, 121,   0}, {208, 121,   0},
    {210, 122,   0}, {211, 123,   0}, {211, 123,   0}, {213, 124,   0},
    {214, 126,   0}, {214, 126,   0}, {216, 127,   0}, {217, 128,   0},
    {217, 128,   0}, {219, 130,   0}, {221, 131,   0}, {221, 131,   0},
    {222, 132,   0}, {224, 133,   0}, {224, 133,   0}, {225, 135,   0},
    {227, 136,   0}, {227, 136,   0}, {228, 137,   0}, {230, 138,   0},
    {230, 138,   0}, {231, 140,   0}, {233, 141,   0}, {233, 141,   0},
    {234, 142,   0}, {236, 144,   0}, {236, 144,   0}, {238, 145,   0},
    {239, 146,   0}, {241, 147,   0}, {241, 147,   0}, {242, 149,   0},
    {244, 150,   0}, {244, 150,   0}, {245, 151,   0}, {247, 153,   0},
    {247, 153,   0}, {248, 154,   0}, {250, 155,   0}, {251, 156,   0},
    {251, 156,   0}, {253, 158,   0}, {255, 159,   0}, {255, 159,   0},
    {255, 160,   0}, {255, 161,   0}, {255, 163,   0}, {255, 163,   0},
    {255, 164,   0}, {255, 165,   0}, {255, 167,   0}, {255, 167,   0},
    {255, 168,   0}, {255, 169,   0}, {255, 169,   0}, {255, 170,   0},
    {255, 172,   0}, {255, 173,   0}, {255, 173,   0}, {255, 174,   0},
    {255, 175,   0}, {255, 177,   0}, {255, 178,   0}, {255, 179,   0},
    {255, 181,   0}, {255, 181,   0}, {255, 182,   0}, {255, 183,   0},
    {255, 184,   0}, {255, 187,   7}, {255, 188,  10}, {255, 189,  14},
    {255, 191,  18}, {255, 192,  21}, {255, 193,  25}, {255, 195,  29},
    {255, 197,  36}, {255, 198,  40}, {255, 200,  43}, {255, 202,  51},
    {255, 204,  54}, {255, 206,  61}, {255, 207,  65}, {255, 210,  72},
    {255, 211,  76}, {255, 214,  83}, {255, 216,  91}, {255, 219,  98},
    {255, 221, 105}, {255, 223, 109}, {255, 225, 116}, {255, 228, 123},
    {255, 232, 134}, {255, 234, 142}, {255, 237, 149}, {255, 239, 156},
    {255, 240, 160}, {255, 243, 167}, {255, 246, 174}, {255, 248, 182},
    {255, 249, 185}, {255, 252, 193}, {255, 253, 196}, {255, 255, 204},
    {255, 255, 207}, {255, 255, 211}, {255, 255, 218}, {255, 255, 222},
    {255, 255, 225}, {255, 255, 229}, {255, 255, 233}, {255, 255, 236},
    {255, 255, 240}, {255, 255, 244}, {255, 255, 247}, {255, 255, 255}
};
// *INDENT-ON*
/* Save the two dimensional array as a png image
 * Arguments:
 *   double *data is a pointer to an array of nx*ny values
 *   int nx is the number of COLUMNS to be written
 *   int ny is the number of ROWS to be written
 *   char *fname is the name of the picture
 *   char lang is either 'c' or 'f' denoting the memory
 *             layout. That is, if 'f' is given, then rows
 *             and columns are swapped.
 */
int save_png(int *data, const int height, const int width, const char *fname)
{
    FILE *fp;
    png_structp pngstruct_ptr = NULL;
    png_infop pnginfo_ptr = NULL;
    png_byte **row_pointers = NULL;
    int i, j, max_value;

    /* Determine the maximum value */
    max_value = INT_MIN;
    for (i = 0; i < height * width; i++) {
        max_value = data[i] > max_value ? data[i] : max_value;
    }

    /* Default return status is failure */
    int status = -1;

    int pixel_size = 3;
    int depth = 8;

    fp = fopen(fname, "wb");
    if (fp == NULL) {
        goto fopen_failed;
    }

    pngstruct_ptr =
        png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (pngstruct_ptr == NULL) {
        goto pngstruct_create_failed;
    }

    pnginfo_ptr = png_create_info_struct(pngstruct_ptr);

    if (pnginfo_ptr == NULL) {
        goto pnginfo_create_failed;
    }

    if (setjmp(png_jmpbuf(pngstruct_ptr))) {
        goto setjmp_failed;
    }

    png_set_IHDR(pngstruct_ptr, pnginfo_ptr, (size_t) width,
                 (size_t) height, depth, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    row_pointers = png_malloc(pngstruct_ptr, height * sizeof(png_byte *));

    for (i = 0; i < height; i++) {
        png_byte *row = png_malloc(pngstruct_ptr,
                                   sizeof(uint8_t) * width * pixel_size);
        row_pointers[i] = row;

        // Branch according to the memory layout
        for (j = 0; j < width; j++) {
            pixel_t pixel;
            // Scale the values so that values between
            // 0 and 100 degrees are mapped to values
            // between 0 and 255
            cmap(data[j + i * width], max_value, &pixel);
            *row++ = pixel.red;
            *row++ = pixel.green;
            *row++ = pixel.blue;
        }
    }

    png_init_io(pngstruct_ptr, fp);
    png_set_rows(pngstruct_ptr, pnginfo_ptr, row_pointers);
    png_write_png(pngstruct_ptr, pnginfo_ptr,
                  PNG_TRANSFORM_IDENTITY, NULL);

    status = 0;

    for (i = 0; i < height; i++) {
        png_free(pngstruct_ptr, row_pointers[i]);
    }
    png_free(pngstruct_ptr, row_pointers);

setjmp_failed:
pnginfo_create_failed:
    png_destroy_write_struct(&pngstruct_ptr, &pnginfo_ptr);
pngstruct_create_failed:
    fclose(fp);
fopen_failed:
    return status;
}

/* This routine sets the RGB values for the pixel_t structure using
 * the colormap data heat_colormap. If the value is outside the
 * acceptable png values 0,255 blue or red color is used instead. */
void cmap(const int value, const int max_value, pixel_t *pix)
{
    int ival;

    ival = ((double) value / (double) max_value) * 255;
    /* Check for wrong values */
    if (ival > 255) {
        ival = 255;
    }
    if (ival < 0) {
        ival = 0;
    }

    /* Pick color from heat_colormap */
    pix->red = heat_colormap[ival][0];
    pix->green = heat_colormap[ival][1];
    pix->blue = heat_colormap[ival][2];
}
