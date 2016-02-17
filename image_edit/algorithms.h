/*
Basic image processing software
<https://github.com/nlabiris/image_edit>

Copyright (C) 2015  Nikos Labiris

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef ALGORITHMS_
#define ALGORITHMS_

/**** Variables ****/

int lines;                      // Lines
int columns;                    // Columns
unsigned char **image_in;       // Image input array
unsigned char **image_out;      // Image output array
unsigned char **image_in_r;     // Image input array (Red)
unsigned char **image_in_g;     // Image input array (Green)
unsigned char **image_in_b;     // Image input array (Blue)
unsigned char **image_out_r;    // Image output array (Red)
unsigned char **image_out_g;    // Image output array (Green)
unsigned char **image_out_b;    // Image output array (Blue)
char release_mem;               // If this flag is set release memory
float possibility[256];         // Possibilities each hue (Red)
float possibility_r[256];       // Possibilities each hue (Red)
float possibility_g[256];       // Possibilities each hue (Green)
float possibility_b[256];       // Possibilities each hue (Blue)
int hist[256];                  // Histogram array
int hist_r[256];                // Histogram array (Red)
int hist_g[256];                // Histogram array (Green)
int hist_b[256];                // Histogram array (Blue)



/****************************** BW ******************************/


/**** Helper functions ****/

/* Release memory */
void free_memory_bw(
    unsigned char ***image_in, unsigned char ***image_out
    );

/* Open file for reading */
void read_file_bw(
    unsigned char ***image_in, unsigned char ***image_out, char filename_in[], FILE *fp_in
    );

/* Open file for writing */
void write_file_bw(
    unsigned char ***image_out, char filename_out[], FILE *fp_out
    );

/* Open file for writing (Histogram only) */
void write_file_histogram_bw(
    char filename_out2[], FILE *fp_out2, int hist[], float possibility[],
    float mean, float variance, int *min, int *max, int *min_pos, int *max_pos
    );


/**** Algorithms ****/

/* Shift bit, hue reduction */
void image_shift_bw(
    unsigned char ***image_in, unsigned char ***image_out, int n
    );

/* Image threshold */
void image_threshold_bw(
    unsigned char ***image_in, unsigned char ***image_out, int threshold
    );

/* Negative Image creation */
void image_negative_bw(
    unsigned char ***image_in, unsigned char ***image_out
    );

/* Square root calculation */
void image_sqrt_bw(
    unsigned char ***image_in, unsigned char ***image_out
    );

/* Contrast enhancement, Brightness and Contrast together */
void image_contrast_enhancement_bw(
    unsigned char ***image_in, unsigned char ***image_out, float a, float b
    );

/* Change Brightness */
void image_brightness_bw(
    unsigned char ***image_in, unsigned char ***image_out, float a
    );

/* Change Contrast */
void image_contrast_bw(
    unsigned char ***image_in, unsigned char ***image_out, float b
    );

/* Histogram creation */
void histogram_bw(
    unsigned char ***image_in, int hist[]
    );

/* Max values histogram */
void histogram_min_bw(
    int hist[], int *min, int *min_pos
    );

/* Min values histogram */
void histogram_max_bw(
    int hist[], int *max, int *max_pos
    );

/* Mean value calculation */
float histogram_mean_bw(
    int hist[]
    );

/* Variance value calculation */
float histogram_variance_bw(
    int hist[], float mean
    );

/* Possibility Calculation */
void histogram_possibility_bw(
    int hist[], float possibility[]
    );

/* Histogram Equalization */
void histogram_equalization_bw(
    unsigned char ***image_in, unsigned char ***image_out, float possibility[]
    );

/* Image Convolution with one mask */
void image_convolution_bw(
    unsigned char ***image_in, unsigned char ***image_out, float **w, int size, double factor, double bias
    );

/* Image Convolution with 2 mask, X-Axis and Y-Axis */
void image_convolution_2d_bw(
    unsigned char ***image_in, unsigned char ***image_out, float **wx, float **wy, int size, double factor, double bias
    );

/* Image rotation (clockwise) */
void image_rotation_clockwise_bw(
    unsigned char ***image_in, unsigned char ***image_out
    );

/* Image rotation (counter-clockwise) */
void image_rotation_counterclockwise_bw(
    unsigned char ***image_in, unsigned char ***image_out
    );




/****************************** COLOR ******************************/


/**** Helper functions ****/

/* Release memory */
void free_memory_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Open file for reading */
void read_file_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    char filename_in[], FILE *fp_in
    );

/* Open file for writing */
void write_file_color(
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    char filename_out[], FILE *fp_out
    );

/* Open file for writing (Histogram only) */
/*void write_file_histogram_color (
char filename_out2[], FILE *fp_out2, int hist[], float possibility[],
float mean, float variance, int *min, int *max, int *min_pos, int *max_pos
);*/


/**** Algorithms ****/

/* Shift bit, hue reduction */
void image_shift_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    int n
    );

/* Image threshold */
void image_threshold_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    int threshold
    );

/* Negative Image creation */
void image_negative_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Square root calculation */
void image_sqrt_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Contrast enhancement, Brightness and Contrast together */
void image_contrast_enhancement_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float a, float b
    );

/* Change Brightness */
void image_brightness_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float a
    );

/* Change Contrast */
void image_contrast_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float b
    );

/* Histogram creation */
void histogram_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    int hist_r[], int hist_g[], int hist_b[]
    );

/* Max values histogram */
void histogram_min_color(
    int hist_r[], int hist_g[], int hist_b[],
    int *min_r, int *min_g, int *min_b,
    int *min_pos_r, int *min_pos_g, int *min_pos_b
    );

/* Min values histogram */
void histogram_max_color(
    int hist_r[], int hist_g[], int hist_b[],
    int *max_r, int *max_g, int *max_b,
    int *max_pos_r, int *max_pos_g, int *max_pos_b
    );

/* Mean value calculation */
float histogram_mean_color(
    int hist_r[], int hist_g[], int hist_b[]
    );

/* Variance value calculation */
float histogram_variance_color(
    int hist_r[], int hist_g[], int hist_b[], float mean
    );

/* Possibility Calculation */
void histogram_possibility_color(
    int hist_r[], int hist_g[], int hist_b[],
    float possibility_r[], float possibility_g[], float possibility_b[]
    );

/* Histogram Equalization [RGB] */
void histogram_equalization_rgb_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float possibility_r[], float possibility_g[], float possibility_b[]
    );

/* Histogram Equalization [HSV] */
void histogram_equalization_hsv_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Histogram Equalization [YUV] */
void histogram_equalization_yuv_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Image Convolution with one mask */
void image_convolution_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float **w, int size, double factor, double bias
    );

/* Image Convolution with 2 mask, X-Axis and Y-Axis */
void image_convolution_2d_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float **wx, float **wy, int size, double factor, double bias
    );

/* Image rotation (clockwise) */
void image_rotation_clockwise_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Image rotation (counter-clockwise) */
void image_rotation_counterclockwise_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Color to grayscale */
void color_to_grayscale(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

/* Sepia tone */
void sepia_tone(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    );

#endif
