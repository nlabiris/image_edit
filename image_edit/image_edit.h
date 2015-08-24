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


#ifndef IMAGE_EDIT_
#define IMAGE_EDIT_

int lines;
int columns;




/****************************** BW ******************************/

void release_memory_bw	// Release memory (choice 1)
(
unsigned char ***image_in, unsigned char ***image_out
);

void release_memory_sum_sub_bw	// Release memory (choices 12, 13)
(
unsigned char ***image_in, unsigned char ***image_in1, unsigned char ***image_in2,
unsigned char ***image_out
);

void read_file_bw	// Open file for reading
(
unsigned char ***image_in, unsigned char ***image_out, char filename_in[], FILE *fp_in
);

void read_file_sum_sub_bw	// Open file for reading (Image summarization & Image subtraction)
(
unsigned char ***image_in1, unsigned char ***image_in2, char filename_in[], FILE *fp_in
);

void write_file_bw	// Open file for writing
(
unsigned char ***image_out, char filename_out[], FILE *fp_out
);

void write_file_histogram_bw	// Open file for writing (Histogram only)
(
char filename_out2[], FILE *fp_out2, int hist[], float possibility[],
float mean, float variance, int *min, int *max, int *min_pos, int *max_pos
);

void image_shift_bw	// Shift bit, hue reduction
(
unsigned char ***image_in, unsigned char ***image_out, int n
);

void image_threshold_bw	// Image threshold
(
unsigned char ***image_in, unsigned char ***image_out, int threshold
);

void image_negative_bw	// Negative Image creation
(
unsigned char ***image_in, unsigned char ***image_out
);

void image_sqrt_bw	// Square root calculation
(
unsigned char ***image_in, unsigned char ***image_out
);

void image_contrast_enhancement_bw	// Contrast enhancement, Brightness and Contrast together
(
unsigned char ***image_in, unsigned char ***image_out, float a, float b
);

void image_brightness_bw	// Change Brightness
(
unsigned char ***image_in, unsigned char ***image_out, float a
);

void image_contrast_bw	// Change Contrast
(
unsigned char ***image_in, unsigned char ***image_out, float b
);

void histogram_bw	// Histogram creation
(
unsigned char ***image_in, int hist[]
);

void histogram_min_bw	// Max values histogram
(
int hist[], int *min, int *min_pos
);

void histogram_max_bw	// Min values histogram
(
int hist[], int *max, int *max_pos
);

float histogram_mean_bw	// Mean value calculation
(
int hist[]
);

float histogram_variance_bw	// Variance value calculation
(
int hist[], float mean
);

void histogram_possibility_bw	// Possibility Calculation
(
int hist[], float possibility[]
);

void histogram_equalization_bw	// Histogram Equalization
(
unsigned char ***image_in, unsigned char ***image_out, float possibility[]
);

void image_sum_bw	// Image Summarization
(
unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out
);

void image_sub_bw	// Image Subtract
(
unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out
);

void image_convolution_bw	// Image Convolution with one mask
(
unsigned char ***image_in, unsigned char ***image_out, float **w, int size
);

void image_convolution_2d_bw	// Image Convolution with 2 mask, X-Axis and Y-Axis
(
unsigned char ***image_in, unsigned char ***image_out, float **wx, float **wy, int size
);

void image_rotation_clockwise_bw
(
unsigned char ***image_in, unsigned char ***image_out
);

void image_rotation_counterclockwise_bw
(
unsigned char ***image_in, unsigned char ***image_out
);




/****************************** COLOR ******************************/

void release_memory_color	// Release memory (choice 1)
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void release_memory_sum_sub_color	// Release memory (choices 12, 13)
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
unsigned char ***image_in1_r, unsigned char ***image_in1_g, unsigned char ***image_in1_b,
unsigned char ***image_in2_r, unsigned char ***image_in2_g, unsigned char ***image_in2_b
);

void read_file_color	// Open file for reading
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
char filename_in[], FILE *fp_in
);

void read_file_sum_sub_color	// Open file for reading (Image summarization & Image subtraction)
(
unsigned char ***image_in1_r, unsigned char ***image_in1_g, unsigned char ***image_in1_b,
unsigned char ***image_in2_r, unsigned char ***image_in2_g, unsigned char ***image_in2_b,
char filename_in[], FILE *fp_in
);

void write_file_color	// Open file for writing
(
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
char filename_out[], FILE *fp_out
);

/*void write_file_histogram_color	// Open file for writing (Histogram only)
(
char filename_out2[], FILE *fp_out2, int hist[], float possibility[],
float mean, float variance, int *min, int *max, int *min_pos, int *max_pos
);*/

void image_shift_color	// Shift bit, hue reduction
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
int n
);

void image_threshold_color	// Image threshold
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
int threshold
);

void image_negative_color	// Negative Image creation
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void image_sqrt_color	// Square root calculation
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void image_contrast_enhancement_color	// Contrast enhancement, Brightness and Contrast together
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
float a, float b
);

void image_brightness_color	// Change Brightness
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
float a
);

void image_contrast_color	// Change Contrast
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
float b
);

void histogram_color	// Histogram creation
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
int hist_r[], int hist_g[], int hist_b[]
);

void histogram_min_color	// Max values histogram
(
int hist_r[], int hist_g[], int hist_b[],
int *min_r, int *min_g, int *min_b,
int *min_pos_r, int *min_pos_g, int *min_pos_b
);

void histogram_max_color	// Min values histogram
(
int hist_r[], int hist_g[], int hist_b[],
int *max_r, int *max_g, int *max_b,
int *max_pos_r, int *max_pos_g, int *max_pos_b
);

float histogram_mean_color	// Mean value calculation
(
int hist_r[], int hist_g[], int hist_b[]
);

float histogram_variance_color	// Variance value calculation
(
int hist_r[], int hist_g[], int hist_b[], float mean
);

void histogram_possibility_color	// Possibility Calculation
(
int hist_r[], int hist_g[], int hist_b[],
float possibility_r[], float possibility_g[], float possibility_b[]
);

void histogram_equalization_rgb_color	// Histogram Equalization [RGB]
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
float possibility_r[], float possibility_g[], float possibility_b[]
);

void histogram_equalization_hsv_color	// Histogram Equalization [HSV]
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void histogram_equalization_yuv_color	// Histogram Equalization [YUV]
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void image_sum_color	// Image Summarization
(
unsigned char ***image_in1_r, unsigned char ***image_in1_g, unsigned char ***image_in1_b,
unsigned char ***image_in2_r, unsigned char ***image_in2_g, unsigned char ***image_in2_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void image_sub_color	// Image Subtract
(
unsigned char ***image_in1_r, unsigned char ***image_in1_g, unsigned char ***image_in1_b,
unsigned char ***image_in2_r, unsigned char ***image_in2_g, unsigned char ***image_in2_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void image_convolution_color	// Image Convolution with one mask
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
float **w, int size
);

void image_convolution_2d_color	// Image Convolution with 2 mask, X-Axis and Y-Axis
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
float **wx, float **wy, int size
);

void image_rotation_clockwise_color
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

void image_rotation_counterclockwise_color
(
unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
);

#endif