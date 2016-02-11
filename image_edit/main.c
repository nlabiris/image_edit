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


#define _CRT_SECURE_NO_WARNINGS // Disabled deprication warnings for scanf, fopen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_edit.h"


int main() {
    FILE *fp_in = NULL;					// File Pointer for image_in
    FILE *fp_out = NULL;				// File Pointer for image_out
    FILE *fp_out2 = NULL;				// File Pointer for histogram
    unsigned char **image_in = NULL;	// Image input array
    unsigned char **image_in1 = NULL;	// Image input 1 for summarize - subtract
    unsigned char **image_in2 = NULL;	// Image input 2 for summarize - subtract
    unsigned char **image_out = NULL;	// Image output array
    unsigned char **image_in_r = NULL;	// Image input array (Red)
    unsigned char **image_in_g = NULL;	// Image input array (Green)
    unsigned char **image_in_b = NULL;	// Image input array (Blue)
    unsigned char **image_in1_r = NULL;	// Image input 1 for summarize - subtract (Red)
    unsigned char **image_in1_g = NULL;	// Image input 1 for summarize - subtract (Green)
    unsigned char **image_in1_b = NULL;	// Image input 1 for summarize - subtract (Blue)
    unsigned char **image_in2_r = NULL;	// Image input 2 for summarize - subtract (Red)
    unsigned char **image_in2_g = NULL;	// Image input 2 for summarize - subtract (Green)
    unsigned char **image_in2_b = NULL;	// Image input 2 for summarize - subtract (Blue)
    unsigned char **image_out_r = NULL;	// Image output array (Red)
    unsigned char **image_out_g = NULL;	// Image output array (Green)
    unsigned char **image_out_b = NULL;	// Image output array (Blue)
    char release_mem = 0;				// Check if entered choice 1
    char release_mem_sum_sub = 0;		// Check if entered choice 13, 14
    char filename_in[20];				// Filename for input image
    char filename_out[20];				// Filename for output image
    char filename_out2[20];				// Filename for histogram
    float possibility[256];				// Possibilities each hue (Red)
    float possibility_r[256];			// Possibilities each hue (Red)
    float possibility_g[256];			// Possibilities each hue (Green)
    float possibility_b[256];			// Possibilities each hue (Blue)
    float mean = 0.0;					// Mean value
    float variance = 0.0;				// Variance 
    float a = 0.0;						// Brightness
    float b = 0.0;						// Contrast
    //float **w = NULL;					// Mask array
    float **wx = NULL;					// Mask array X-Axis
    float **wy = NULL;					// Mask array Y-Axis
    int choice = 0;						// What edit want to do?
    char answer[4];						// Yes/no if colored
    char degree[6];						// Left or right rotation
    int is_colored = 0;					// Is the image colored?
    int hist[256];						// Histogram array
    int hist_r[256];					// Histogram array (Red)
    int hist_g[256];					// Histogram array (Green)
    int hist_b[256];					// Histogram array (Blue)
    int i = 0;							// Line counter
    int j = 0;							// Column counter
    int n = 0;							// Number of bits to shift
    int threshold = 0;					// Image threshold
    int min = 0;						// Minimum value of hue
    int min_r = 0;						// Minimum value of hue (Red)
    int min_g = 0;						// Minimum value of hue (Green)
    int min_b = 0;						// Minimum value of hue (Blue)
    int max = 0;						// Maximum value of hue
    int max_r = 0;						// Maximum value of hue (Red)
    int max_g = 0;						// Maximum value of hue (Green
    int max_b = 0;						// Maximum value of hue (Blue)
    int min_pos = 0;					// Minimum hue population
    int min_pos_r = 0;					// Minimum hue population (Red)
    int min_pos_g = 0;					// Minimum hue population (Green)
    int min_pos_b = 0;					// Minimum hue population (Blue)
    int max_pos = 0;					// Maximum hue population
    int max_pos_r = 0;					// Maximum hue population (Red)
    int max_pos_g = 0;					// Maximum hue population (Green)
    int max_pos_b = 0;					// Maximum hue population (Blue)
    int size = 0;						// Size of mask array, either one mask or X-Axis, Y-Axis mask


    while (1) {
        system("cls");
        printf("0. Exit\n");
        printf("1. Read from file\n");
        printf("2. Write to file\n");
        printf("3. Shift\n");
        printf("4. Threshold\n");
        printf("5. Negative\n");
        printf("6. Sqrt\n");
        printf("7. Contrast Enhancement\n");
        printf("8. Brightness\n");
        printf("9. Contrast\n");
        printf("10. Rotate\n");
        printf("11. Histogram stats\n");
        printf("12. Histogram equalization [RGB]\n");
        printf("13. Histogram equalization [HSV]\n");
        printf("14. Histogram equalization [YUV]\n");
        printf("15. Image summarization\n");
        printf("16. Image subtraction\n");
        printf("17. Image convolution with 2 masks\n\n\n");

        printf("Enter a number (0-17): ");
        scanf("%d", &choice);

        switch (choice) {
            case 0: // Exit
                system("cls");
                printf("Exiting the program...\n\n\n\n");

                if (release_mem && !is_colored) {
                    release_memory_bw(&image_in, &image_out);
                } else if (release_mem && is_colored) {
                    release_memory_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                }

                if (release_mem_sum_sub && !is_colored) {
                    release_memory_sum_sub_bw(&image_in, &image_in1, &image_in2, &image_out);
                } else if (release_mem_sum_sub && is_colored) {
                    release_memory_sum_sub_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, &image_in1_r, &image_in1_g, &image_in1_b, &image_in2_r, &image_in2_g, &image_in2_b);
                }

                return EXIT_SUCCESS;
            case 1: // Read from file
                system("cls");

                printf("Colored image? (Y/N): ");
                scanf("%s", answer);

                if (strcmp("y", answer) == 0 || strcmp("Y", answer) == 0 || strcmp("yes", answer) == 0 || strcmp("YES", answer) == 0) {
                    is_colored = 1;
                    read_file_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, filename_in, fp_in);
                    release_mem = 1;
                } else if (strcmp("n", answer) == 0 || strcmp("N", answer) == 0 || strcmp("no", answer) == 0 || strcmp("NO", answer) == 0) {
                    is_colored = 0;
                    read_file_bw(&image_in, &image_out, filename_in, fp_in);
                    release_mem = 1;
                } else {
                    printf("Wrong answer!");
                    system("pause");
                    return EXIT_SUCCESS;
                }

                release_mem = 1;
                system("pause");
                break;
            case 2: // Write to file
                system("cls");

                if (is_colored) {
                    write_file_color(&image_out_r, &image_out_g, &image_out_b, filename_out, fp_out);
                } else {
                    write_file_bw(&image_out, filename_out, fp_out);
                }

                release_mem = 1;
                break;
            case 3: // Shift
                system("cls");

                printf("Enter number of bits (0-7): ");
                scanf("%d", &n);

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    image_shift_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, n);
                } else {
                    image_shift_bw(&image_in, &image_out, n);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 4: // Threshold
                system("cls");

                printf("Enter threshold: ");
                scanf("%d", &threshold);

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    image_threshold_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, threshold);
                } else {
                    image_threshold_bw(&image_in, &image_out, threshold);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 5: // Negative
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    image_negative_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                } else {
                    image_negative_bw(&image_in, &image_out);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 6: // Sqrt
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    image_sqrt_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                } else {
                    image_sqrt_bw(&image_in, &image_out);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 7: // Contrast Enhancement
                system("cls");

                printf("Brightness: ");
                scanf("%f", &a);

                printf("Contrast: ");
                scanf("%f", &b);

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    image_contrast_enhancement_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, a, b);
                } else {
                    image_contrast_enhancement_bw(&image_in, &image_out, a, b);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 8: //Brightness
                system("cls");

                printf("Brightness: ");
                scanf("%f", &a);

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    image_brightness_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, a);
                } else {
                    image_brightness_bw(&image_in, &image_out, a);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 9: // Contrast
                system("cls");

                printf("Contrast: ");
                scanf("%f", &b);

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    image_contrast_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, b);
                } else {
                    image_contrast_bw(&image_in, &image_out, b);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 10: // Rotate
                system("cls");

                printf("(L)eft or (R)ight rotation? (L/R): ");
                scanf("%s", degree);

                if (strcmp("l", degree) == 0 || strcmp("L", degree) == 0 || strcmp("left", degree) == 0 || strcmp("LEFT", degree) == 0) {
                    printf("\n\nImage editing...\n");
                    if (is_colored) {
                        image_rotation_counterclockwise_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                    } else {
                        image_rotation_counterclockwise_bw(&image_in, &image_out);
                    }
                    printf("\nEditing complete.\n\n");
                    printf("Rotated left by 90 degrees\n\n");
                } else if (strcmp("r", degree) == 0 || strcmp("R", degree) == 0 || strcmp("right", degree) == 0 || strcmp("RIGHT", degree) == 0) {
                    printf("\n\nImage editing...\n");
                    if (is_colored) {
                        image_rotation_clockwise_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                    } else {
                        image_rotation_clockwise_bw(&image_in, &image_out);
                    }
                    printf("\nEditing complete.\n\n");
                    printf("Rotated right by 90 degrees\n\n");
                } else {
                    printf("Wrong answer!");
                    system("pause");
                    break;
                }

                release_mem = 1;
                system("pause");
                break;
            case 11: // Histogram values
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    histogram_color(&image_in_r, &image_in_g, &image_in_b, hist_r, hist_g, hist_b);
                    histogram_min_color(hist_r, hist_g, hist_b, &min_r, &min_g, &min_b, &min_pos_r, &min_pos_g, &min_pos_b);
                    histogram_max_color(hist_r, hist_g, hist_b, &max_r, &max_g, &max_b, &max_pos_r, &max_pos_g, &max_pos_b);
                    histogram_possibility_color(hist_r, hist_g, hist_b, possibility_r, possibility_g, possibility_b);
                    mean = histogram_mean_color(hist_r, hist_g, hist_b);
                    variance = histogram_variance_color(hist_r, hist_g, hist_b, mean);
                } else {
                    histogram_bw(&image_in, hist);
                    histogram_min_bw(hist, &min, &min_pos);
                    histogram_max_bw(hist, &max, &max_pos);
                    histogram_possibility_bw(hist, possibility);
                    mean = histogram_mean_bw(hist);
                    variance = histogram_variance_bw(hist, mean);

                    write_file_histogram_bw(filename_out2, fp_out2, hist, possibility, mean, variance, &min, &max, &min_pos, &max_pos);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 12: // Histogram equalization [RGB]
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    histogram_color(&image_in_r, &image_in_g, &image_in_b, hist_r, hist_g, hist_b);
                    histogram_possibility_color(hist_r, hist_g, hist_b, possibility_r, possibility_g, possibility_b);
                    histogram_equalization_rgb_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, possibility_r, possibility_g, possibility_b);
                } else {
                    histogram_bw(&image_in, hist);
                    histogram_possibility_bw(hist, possibility);
                    histogram_equalization_bw(&image_in, &image_out, possibility);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 13: // Histogram equalization [HSV]
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    histogram_equalization_hsv_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 14: // Histogram equalization [YUV]
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    histogram_equalization_yuv_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                }
                printf("\nEditing complete.\n\n");

                release_mem = 1;
                system("pause");
                break;
            case 15: // Image summarization
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    read_file_sum_sub_color(&image_in1_r, &image_in1_g, &image_in1_b, &image_in2_r, &image_in2_g, &image_in2_b, filename_in, fp_in);
                    image_sum_color(&image_in1_r, &image_in1_g, &image_in1_b, &image_in2_r, &image_in2_g, &image_in2_b, &image_out_r, &image_out_g, &image_out_b);
                } else {
                    read_file_sum_sub_bw(&image_in1, &image_in2, filename_in, fp_in);
                    image_sum_bw(&image_in1, &image_in2, &image_out);
                }
                printf("\nEditing complete.\n\n");

                release_mem_sum_sub = 1;
                system("pause");
                break;
            case 16: // Image subtraction
                system("cls");

                printf("\n\nImage editing...\n");
                if (is_colored) {
                    read_file_sum_sub_color(&image_in1_r, &image_in1_g, &image_in1_b, &image_in2_r, &image_in2_g, &image_in2_b, filename_in, fp_in);
                    image_sub_color(&image_in1_r, &image_in1_g, &image_in1_b, &image_in2_r, &image_in2_g, &image_in2_b, &image_out_r, &image_out_g, &image_out_b);
                } else {
                    read_file_sum_sub_bw(&image_in1, &image_in2, filename_in, fp_in);
                    image_sub_bw(&image_in1, &image_in2, &image_out);
                }
                printf("\nEditing complete.\n\n");

                release_mem_sum_sub = 1;
                system("pause");
                break;
            case 17: // Image convolution with 2 masks
                system("cls");

                printf("Enter size of mask: ");
                scanf("%d", &size);

                printf("\n\nMemory allocation...\n");
                wx = (float**)malloc((size)*sizeof(float*));
                for (i = 0; i < size; i++) {
                    wx[i] = (float*)malloc((size)*sizeof(float));
                }

                wy = (float**)malloc((size)*sizeof(float*));
                for (i = 0; i < size; i++) {
                    wy[i] = (float*)malloc((size)*sizeof(float));
                }

                printf("\n\nImage editing...\n");
                printf("\nEnter wx mask:\n\n");
                for (i = 0; i < size; i++) {
                    for (j = 0; j < size; j++) {
                        printf("wx[%d][%d] = ", i, j);
                        scanf("%f", &wx[i][j]);
                    }
                    printf("\n");
                }

                printf("\nEnter wy mask:\n\n");
                for (i = 0; i < size; i++) {
                    for (j = 0; j < size; j++) {
                        printf("wy[%d][%d] = ", i, j);
                        scanf("%f", &wy[i][j]);
                    }
                    printf("\n");
                }

                if (is_colored) {
                    image_convolution_2d_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b, wx, wy, size);
                } else {
                    image_convolution_2d_bw(&image_in, &image_out, wx, wy, size);
                }
                printf("\nEditing complete.\n\n");

                for (i = 0; i < size; i++) {
                    free(wx[i]);
                    free(wy[i]);
                }
                free(wx);
                free(wy);
                wx = NULL;
                wy = NULL;

                system("pause");
                break;
            default:
                system("cls");
                printf("WRONG CHOICE! Enter a different number! (0-13)\n\n\n");
                system("pause");
        }
    }
}
