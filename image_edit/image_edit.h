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

void release_memory(unsigned char ***image_in, unsigned char ***image_out);											// Release memory (choice 1)
void release_memory_sum_sub(unsigned char ***image_in, unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out);	// Release memory (choices 12, 13)
void read_file(unsigned char ***image_in, unsigned char ***image_out, char filename_in[], FILE *fp_in);				// Open file for reading
void read_file_sum_sub(unsigned char ***image_in1, unsigned char ***image_in2, char filename_in[], FILE *fp_in);	// Open file for reading (Image summarization & Image subtraction)
void write_file(unsigned char ***image_in, unsigned char ***image_out, char filename_out[], FILE *fp_out);			// Open file for writing
void write_file_histogram(char filename_out2[], FILE *fp_out2, int hist[], float possibility[], float mean, float variance, int *min, int *max, int *min_pos, int *max_pos);								// Open file for writing (Histogram only)
void image_shift(unsigned char ***image_in, unsigned char ***image_out, int n);										// Shift bit, hue reduction
void image_threshold(unsigned char ***image_in, unsigned char ***image_out, int threshold);							// Image threshold
void image_negative(unsigned char ***image_in, unsigned char ***image_out);											// Negative Image creation
void image_sqrt(unsigned char ***image_in, unsigned char ***image_out);												// Square root calculation
void image_contrast_enhancement(unsigned char ***image_in, unsigned char ***image_out, float a, float b);			// Contrast enhancement, Brightness and Contrast together
void image_brightness(unsigned char ***image_in, unsigned char ***image_out, float a);								// Change Brightness
void image_contrast(unsigned char ***image_in, unsigned char ***image_out, float b);								// Change Contrast
void histogram(unsigned char ***image_in, int hist[]);																// Histogram creation
void histogram_min(int hist[], int *min, int *min_pos);																// Max values histogram
void histogram_max(int hist[], int *max, int *max_pos);																// Min values histogram
float histogram_mean(int hist[]);																					// Mean value calculation
float histogram_variance(int hist[], float mean);																	// Variance value calculation
void histogram_possibility(int hist[], float possibility[]);														// Possibility Calculation
void histogram_equalization_rgb(unsigned char ***image_in, unsigned char ***image_out, float possibility[]);		// Histogram Equalization
void image_sum(unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out);					// Image Summarization
void image_sub(unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out);					// Image Subtract
void image_convolution(unsigned char ***image_in, unsigned char ***image_out, float **w, int size);					// Image Convolution with one mask
void image_convolution_2d(unsigned char ***image_in, unsigned char ***image_out, float **wx, float **wy, int size);	// Image Convolution with 2 mask, X-Axis and Y-Axis

#endif