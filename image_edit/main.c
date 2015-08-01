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



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image_edit.h"


int main()
{
	FILE *fp_in = NULL;					// File Pointer for image_in
	FILE *fp_out = NULL;				// File Pointer for image_out
	FILE *fp_out2 = NULL;				// File Pointer for histogram
	unsigned char **image_in = NULL;	// Image input array
	unsigned char **image_in1 = NULL;	// Image input 1 for summarize - subtract
	unsigned char **image_in2 = NULL;	// Image input 2 for summarize - subtract
	unsigned char **image_out = NULL;	// Image output array
	char release_mem = 0;				// Check if entered choice 1
	char release_mem_sum_sub = 0;		// Check if entered choice 13, 14
	char filename_in[20];				// Filename for input image
	char filename_out[20];				// Filename for output image
	char filename_out2[20];				// Filename for histogram
	float possibility[256];				// Possibilities each hue
	float mean = 0.0;					// Mean value
	float variance = 0.0;				// Variance 
	float a = 0.0;						// Brightness
	float b = 0.0;						// Contrast
	//float **w = NULL;					// Mask array
	float **wx = NULL;					// Mask array X-Axis
	float **wy = NULL;					// Mask array Y-Axis
	int hist[256];						// Histogram array
	int i = 0;							// Line counter
	int j = 0;							// Column counter
	int n = 0;							// Number of bits to shift
	int threshold = 0;					// Image threshold
	int choice = 0;						// What edit want to do
	int min = 0;						// Minimum value of hue
	int max = 0;						// Maximum value of hue
	int min_pos = 0;					// Minimum hue population
	int max_pos = 0;					// Maximum hue population
	int size = 0;						// Size of mask array, either one mask or X-Axis, Y-Axis mask


	while (1)
	{
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
		printf("10. Histogram stats\n");
		printf("11. Histogram equalization [RGB]\n");
		printf("12. Image summarization\n");
		printf("13. Image subtraction\n");
		printf("14. Image convolution with 2 masks\n\n\n");

		printf("Enter a number (0-14): ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 0: // Exit
			system("cls");
			printf("Exiting the program...\n\n\n\n");

			if (release_mem)
			{
				release_memory(&image_in, &image_out);
			}
			
			if (release_mem_sum_sub)
			{
				release_memory_sum_sub(&image_in, &image_in1, &image_in2, &image_out);
			}

			exit(EXIT_SUCCESS);
			break;
		case 1: // Read from file
			system("cls");
			read_file(&image_in, &image_out, filename_in, fp_in);
			release_mem = 1;
			break;
		case 2: // Write to file
			system("cls");
			write_file(&image_in, &image_out, filename_out, fp_out);
			release_mem = 1;
			break;
		case 3: // Shift
			system("cls");

			printf("Enter number of bits (0-7): ");
			scanf("%d", &n);

			printf("\n\nImage editing...\n");
			image_shift(&image_in, &image_out, n);
			printf("\nEditing complete.\n\n");

			release_mem = 1;
			system("pause");
			break;
		case 4: // Threshold
			system("cls");

			printf("Enter threshold: ");
			scanf("%d", &threshold);

			printf("\n\nImage editing...\n");
			image_threshold(&image_in, &image_out, threshold);
			printf("\nEditing complete.\n\n");

			release_mem = 1;
			system("pause");
			break;
		case 5: // Negative
			system("cls");

			printf("\n\nImage editing...\n");
			image_negative(&image_in, &image_out);
			printf("\nEditing complete.\n\n");

			release_mem = 1;
			system("pause");
			break;
		case 6: // Sqrt
			system("cls");

			printf("\n\nImage editing...\n");
			image_sqrt(&image_in, &image_out);
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
			image_contrast_enhancement(&image_in, &image_out, a, b);
			printf("\nEditing complete.\n\n");

			release_mem = 1;
			system("pause");
			break;
		case 8: //Brightness
			system("cls");

			printf("Brightness: ");
			scanf("%f", &a);

			printf("\n\nImage editing...\n");
			image_brightness(&image_in, &image_out, a);
			printf("\nEditing complete.\n\n");

			release_mem = 1;
			system("pause");
			break;
		case 9: // Contrast
			system("cls");

			printf("Contrast: ");
			scanf("%f", &b);

			printf("\n\nImage editing...\n");
			image_contrast(&image_in, &image_out, b);
			printf("\nEditing complete.\n\n");

			release_mem = 1;
			system("pause");
			break;
		case 10: // Histogram values
			system("cls");

			printf("\n\nImage editing...\n");
			histogram(&image_in, hist);
			histogram_min(hist, &min, &min_pos);
			histogram_max(hist, &max, &max_pos);
			histogram_possibility(hist, possibility);
			mean = histogram_mean(hist);
			variance = histogram_variance(hist, mean);
			printf("\nEditing complete.\n\n");

			write_file_histogram(filename_out2, fp_out2, hist, possibility, mean, variance, &min, &max, &min_pos, &max_pos);

			release_mem = 1;
			system("pause");
			break;
		case 11: // Histogram equalization [RGB]
			system("cls");

			printf("\n\nImage editing...\n");
			histogram(&image_in, hist);
			histogram_possibility(hist, possibility);
			histogram_equalization_rgb(&image_in, &image_out, possibility);
			printf("\nEditing complete.\n\n");

			release_mem = 1;
			system("pause");
			break;
		case 12: // Image summarization
			system("cls");

			read_file_sum_sub(&image_in1, &image_in2, filename_in, fp_in);

			printf("\n\nImage editing...\n");
			image_sum(&image_in1, &image_in2, &image_out);
			printf("\nEditing complete.\n\n");

			release_mem_sum_sub = 1;
			system("pause");
			break;
		case 13: // Image subtraction
			system("cls");

			read_file_sum_sub(&image_in1, &image_in2, filename_in, fp_in);

			printf("\n\nImage editing...\n");
			image_sub(&image_in1, &image_in2, &image_out);
			printf("\nEditing complete.\n\n");

			release_mem_sum_sub = 1;
			system("pause");
			break;
		case 14: // Image convolution with 2 masks
			system("cls");

			printf("Enter size of mask: ");
			scanf("%d", &size);

			printf("\n\nMemory allocation...\n");
			wx = (float**)malloc((size)*sizeof(float*));
			for (i = 0; i < size; i++)
			{
				wx[i] = (float*)malloc((size)*sizeof(float));
			}

			wy = (float**)malloc((size)*sizeof(float*));
			for (i = 0; i < size; i++)
			{
				wy[i] = (float*)malloc((size)*sizeof(float));
			}

			printf("\n\nImage editing...\n");
			printf("\nEnter wx mask:\n\n");
			for (i = 0; i < size; i++)
			{
				for (j = 0; j < size; j++)
				{
					printf("wx[%d][%d] = ", i, j);
					scanf("%f", &wx[i][j]);
				}
				printf("\n");
			}

			printf("\nEnter wy mask:\n\n");
			for (i = 0; i < size; i++)
			{
				for (j = 0; j < size; j++)
				{
					printf("wy[%d][%d] = ", i, j);
					scanf("%f", &wy[i][j]);
				}
				printf("\n");
			}

			image_convolution_2d(&image_in, &image_out, wx, wy, size);
			printf("\nEditing complete.\n\n");

			for (i = 0; i < size; i++)
			{
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


