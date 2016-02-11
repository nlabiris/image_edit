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

#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS // Disabled deprication warnings for scanf, fopen
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_edit.h"


int main() {
    int choice;
    int is_colored;

    while (1) {
    menu:
        system("cls");
        printf("0. Exit\n\n\n"
               "1. Read from file\n"
               "2. Write to file\n"
               "3. Algorithms\n\n\n"
               "Enter a number (0-3): ");

        scanf("%d", &choice);

        switch (choice) {
            case 0:
                system("cls");
                printf("Exiting the program...\n\n\n\n");

                if (release_mem && !is_colored) {
                    free_memory_bw(&image_in, &image_out);
                } else if (release_mem && is_colored) {
                    free_memory_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                }

                return EXIT_SUCCESS;
                break;
            case 1: // Read from file
                system("cls");

                FILE *fp_in = NULL;     // File Pointer for image_in
                char answer[4];
                char filename_in[20];   // Filename for input image

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

                system("pause");
                break;
            case 2: // Write to file
                system("cls");

                FILE *fp_out = NULL;   // File Pointer for image_out
                char filename_out[20]; // Filename for output image
                
                if (is_colored) {
                    write_file_color(&image_out_r, &image_out_g, &image_out_b, filename_out, fp_out);
                } else {
                    write_file_bw(&image_out, filename_out, fp_out);
                }

                release_mem = 1;
                break;
            case 3: // Algorithms
                break;
            default:
                system("cls");
                printf("WRONG CHOICE! Enter a different number! (0-3)\n\n\n");
                system("pause");
        }

        if (choice == 1 || choice == 2) {
            goto menu;
        }

        while (1) {
            system("cls");
            printf("0. Back\n\n\n"
                   "1. Shift\n"
                   "2. Threshold\n"
                   "3. Negative\n"
                   "4. Sqrt\n"
                   "5. Contrast Enhancement\n"
                   "6. Brightness\n"
                   "7. Contrast\n"
                   "8. Rotate\n"
                   "9. Histogram stats\n"
                   "10. Histogram equalization [RGB]\n"
                   "11. Histogram equalization [HSV]\n"
                   "12. Histogram equalization [YUV]\n"
                   "13. Image convolution with 2 masks\n"
                   "14. Color to grayscale\n"
                   "15. Sepia tone\n\n\n"
                   "Enter a number (0-15): ");

            scanf("%d", &choice);

            switch (choice) {
                case 0: // Back
                    goto menu;
                case 1: // Shift
                    system("cls");

                    int n; // Number of bits to shift

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
                case 2: // Threshold
                    system("cls");

                    int threshold; // Image threshold

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
                case 3: // Negative
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
                case 4: // Sqrt
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
                case 5: // Contrast Enhancement
                    system("cls");

                    float a;    // Brightness
                    float b;    // Contrast

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
                case 6: //Brightness
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
                case 7: // Contrast
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
                case 8: // Rotate
                    system("cls");

                    char degree[6];
                    
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
                case 9: // Histogram values
                    system("cls");

                    FILE *fp_out2 = NULL;       // File Pointer for histogram
                    char filename_out2[20];     // Filename for histogram
                    float mean;                 // Mean value
                    float variance;             // Variance
                    int min;                    // Minimum value of hue
                    int min_r;                  // Minimum value of hue (Red)
                    int min_g;                  // Minimum value of hue (Green)
                    int min_b;                  // Minimum value of hue (Blue)
                    int max;                    // Maximum value of hue
                    int max_r;                  // Maximum value of hue (Red)
                    int max_g;                  // Maximum value of hue (Green
                    int max_b;                  // Maximum value of hue (Blue)
                    int min_pos;                // Minimum hue population (BW)
                    int min_pos_r;              // Minimum hue population (Red)
                    int min_pos_g;              // Minimum hue population (Green)
                    int min_pos_b;              // Minimum hue population (Blue)
                    int max_pos;                // Maximum hue population (BW)
                    int max_pos_r;              // Maximum hue population (Red)
                    int max_pos_g;              // Maximum hue population (Green)
                    int max_pos_b;              // Maximum hue population (Blue)

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
                case 10: // Histogram equalization [RGB]
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
                case 11: // Histogram equalization [HSV]
                    system("cls");

                    printf("\n\nImage editing...\n");
                    if (is_colored) {
                        histogram_equalization_hsv_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                    }
                    printf("\nEditing complete.\n\n");

                    release_mem = 1;
                    system("pause");
                    break;
                case 12: // Histogram equalization [YUV]
                    system("cls");

                    printf("\n\nImage editing...\n");
                    if (is_colored) {
                        histogram_equalization_yuv_color(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                    }
                    printf("\nEditing complete.\n\n");

                    release_mem = 1;
                    system("pause");
                    break;
                case 13: // Image convolution with 2 masks
                    system("cls");

                    int size;   // Size of masks
                    float **wx; // Mask array X-Axis
                    float **wy; // Mask array Y-Axis

                    printf("Enter size of mask: ");
                    scanf("%d", &size);

                    printf("\n\nMemory allocation...\n");
                    wx = (float**)malloc((size)*sizeof(float*));
                    for (int i = 0; i < size; i++) {
                        wx[i] = (float*)malloc((size)*sizeof(float));
                    }

                    wy = (float**)malloc((size)*sizeof(float*));
                    for (int i = 0; i < size; i++) {
                        wy[i] = (float*)malloc((size)*sizeof(float));
                    }

                    printf("\n\nImage editing...\n");
                    printf("\nEnter wx mask:\n\n");
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
                            printf("wx[%d][%d] = ", i, j);
                            scanf("%f", &wx[i][j]);
                        }
                        printf("\n");
                    }

                    printf("\nEnter wy mask:\n\n");
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
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

                    for (int i = 0; i < size; i++) {
                        free(wx[i]);
                        free(wy[i]);
                    }
                    free(wx);
                    free(wy);
                    wx = NULL;
                    wy = NULL;

                    system("pause");
                    break;
                case 14: // Color to grayscale
                    system("cls");

                    printf("\n\nImage editing...\n");
                    if (is_colored) {
                        color_to_grayscale(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                    } else {
                        printf("Only colored images!\n");
                    }
                    printf("\nEditing complete.\n\n");

                    release_mem = 1;
                    system("pause");
                    break;
                case 15: // Sepia tone
                    system("cls");

                    printf("\n\nImage editing...\n");
                    if (is_colored) {
                        sepia_tone(&image_in_r, &image_in_g, &image_in_b, &image_out_r, &image_out_g, &image_out_b);
                    } else {
                        printf("Only colored images!\n");
                    }
                    printf("\nEditing complete.\n\n");

                    release_mem = 1;
                    system("pause");
                    break;
                default:
                    system("cls");
                    printf("WRONG CHOICE! Enter a different number! (0-13)\n\n\n");
                    system("pause");
            }
        }
    }
}
