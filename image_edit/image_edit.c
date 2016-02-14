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


#define _CRT_SECURE_NO_WARNINGS	// Disabled deprication warnings for scanf, fopen

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algorithms.h"

#define	MAX(x, y)	(((x)>(y))?(x):(y))
#define	MIN(x, y)	(((x)<(y))?(x):(y))




/****************************** BW ******************************/

void free_memory_bw(unsigned char ***image_in, unsigned char ***image_out) {
    int i = 0;

    for (i = 0; i < lines; i++) {
        free((*image_in)[i]);
        free((*image_out)[i]);
        (*image_in)[i] = NULL;
        (*image_out)[i] = NULL;
    }
    free(*image_in);
    free(*image_out);
    *image_in = NULL;
    *image_out = NULL;
}

void read_file_bw(unsigned char ***image_in, unsigned char ***image_out, char filename_in[], FILE *fp_in) {
    int i = 0;

    printf("Enter filename to read: ");
    scanf("%s", filename_in);

    printf("Number of lines: ");
    scanf("%d", &lines);

    printf("Number of columns: ");
    scanf("%d", &columns);

    printf("\n\nMemory allocation...\n");
    *image_in = (unsigned char**)malloc((lines)*sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_in)[i] = (unsigned char*)malloc((columns)*sizeof(unsigned char));
    }

    *image_out = (unsigned char**)malloc((lines)*sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_out)[i] = (unsigned char*)malloc((columns)*sizeof(unsigned char));
    }

    fp_in = fopen(filename_in, "rb");
    printf("Reading file...\n\n");
    for (i = 0; i < lines; i++) {
        fread((*image_in)[i], sizeof(unsigned char), columns, fp_in);
    }
    fclose(fp_in);
}

void write_file_bw(unsigned char ***image_out, char filename_out[], FILE *fp_out) {
    int i = 0;

    printf("Enter filename to write: ");
    scanf("%s", filename_out);

    fp_out = fopen(filename_out, "wb");
    printf("\n\nWriting file...\n");
    for (i = 0; i < lines; i++) {
        fwrite((*image_out)[i], sizeof(unsigned char), columns, fp_out);
    }
    fclose(fp_out);
}

void write_file_histogram_bw(char filename_out2[], FILE *fp_out2, int hist[], float possibility[], float mean, float variance, int *min, int *max, int *min_pos, int *max_pos) {
    int i = 0;

    printf("Enter filename to write histogram: ");
    scanf("%s", filename_out2);

    fp_out2 = fopen(filename_out2, "wb");
    printf("\n\nWriting file...\n");
    for (i = 0; i < 256; i++) {
        fprintf(fp_out2, "hist[%d] = %d\n", i, hist[i]);
    }
    fprintf(fp_out2, "\n\n----\n\n");
    fprintf(fp_out2, "min position\t= %d\t|\thue population at min = %d\n", min_pos, min);
    fprintf(fp_out2, "max position\t= %d\t|\thue population at max = %d\n", max_pos, max);
    fprintf(fp_out2, "mean value\t= %f\n", mean);
    fprintf(fp_out2, "variance\t= %f\n", variance);
    fprintf(fp_out2, "\n----\n\n\n");
    for (i = 0; i < 256; i++) {
        fprintf(fp_out2, "possibility[%d] = %f\t=>\t%.2f%%\n", i, possibility[i], possibility[i] * 100); // Printing possibility and possibility in percentag;
    }
    fclose(fp_out2);
}

void image_shift_bw(unsigned char ***image_in, unsigned char ***image_out, int n) {
    int i = 0;
    int j = 0;
    double x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = (*image_in)[i][j] / pow(2, (8 - n)); //<< n // Left shift depending on how many bits we gave
            (*image_out)[i][j] = (unsigned char)x;
            /*if(image_out[i][j]>100)
            {
            image_out[i][j]=255;
            }
            else
            {
            image_out[i][j]=0;
            }*/
        }
    }
}

void image_threshold_bw(unsigned char ***image_in, unsigned char ***image_out, int threshold) {
    int i = 0;
    int j = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            if ((*image_in)[i][j] > threshold) // Check if image input (specific pixel) is higher or lower than the threshold we gave
            {
                (*image_out)[i][j] = 255;
            } else {
                (*image_out)[i][j] = 0;
            }
        }
    }
}

void image_negative_bw(unsigned char ***image_in, unsigned char ***image_out) {
    int i = 0;
    int j = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out)[i][j] = 255 - (*image_in)[i][j]; // Creating a negative image
        }
    }
}

void image_sqrt_bw(unsigned char ***image_in, unsigned char ***image_out) {
    int i = 0;
    int j = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out)[i][j] = (unsigned char)sqrt((*image_in)[i][j] * 255); // Square root calculation
        }
    }
}

void image_contrast_enhancement_bw(unsigned char ***image_in, unsigned char ***image_out, float a, float b) {
    int i = 0;
    int j = 0;
    float x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = ((*image_in)[i][j] + a)*b; // Contrast Enhancement
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out)[i][j] = (unsigned char)x;
        }
    }
}

void image_brightness_bw(unsigned char ***image_in, unsigned char ***image_out, float a) {
    int i = 0;
    int j = 0;
    float x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = (*image_in)[i][j] + a; // Brightness
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out)[i][j] = (unsigned char)x;
        }
    }
}

void image_contrast_bw(unsigned char ***image_in, unsigned char ***image_out, float b) {
    int i = 0;
    int j = 0;
    float x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = (*image_in)[i][j] * b; // Contrast
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out)[i][j] = (unsigned char)x;
        }
    }
}

void histogram_bw(unsigned char ***image_in, int hist[]) {
    int i = 0;
    int j = 0;
    int l = 0;

    for (i = 0; i < 256; i++) {
        hist[i] = 0;
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            l = (*image_in)[i][j];
            hist[l]++; // Printing histogram
        }
    }
}

void histogram_min_bw(int hist[], int *min, int *min_pos) {
    int i = 0;
    *min = 0;
    *min_pos = 300;

    for (i = 0; i < 256; i++) {
        if ((hist[i] != 0) && (i < (*min_pos))) {
            *min = hist[i];	// MIN hue in the image
            *min_pos = i;		// or min=hist[i];
        }
    }
}

void histogram_max_bw(int hist[], int *max, int *max_pos) {
    int i = 0;
    *max = 0; // allios max=hist[0]; an den kseroume ti domi tou pinaka
    *max_pos = -1;

    for (i = 0; i < 256; i++) {
        if ((hist[i] != 0) && (i >(*max_pos))) {
            *max = hist[i];	// MAX hue in the image
            *max_pos = i;		// or max=hist[i]
        }
    }
}

/*********** B way for min-max ***********/

/*
int histogram_min(unsigned char **image_in)
{
	int i,j,min;
	min=300;
	
	for(i=0;i<lines;i++)
	{
		for(j=0;j<columns;j++)
		{
			if(image_in[i][j]<min)
			{
				min=image_in[i][j]; // MIN hue in the image
			}
		}
	}
	return min;
}


int histogram_max(unsigned char **image_in)
{
	int i,j,max;
	max=0;
	
	for(i=0;i<lines;i++)
	{
		for(j=0;j<columns;j++)
		{
			if(image_in[i][j]>max)
			{
				max=image_in[i][j]; // MAX hue in the image
			}
		}
	}
	return max;
}

*/

float histogram_mean_bw(int hist[]) {
    int i = 0;
    float mean = 0.0;
    float hist_sum = 0.0;

    for (i = 0; i < 256; i++) {
        // hist[i] : number of pixel that has a specific hue
        // i : hue
        hist_sum = hist_sum + (i*hist[i]);
    }
    mean = hist_sum / (float)(lines*columns); // Mean value
    return mean;
}

float histogram_variance_bw(int hist[], float mean) {
    int i = 0;
    float variance = 0.0;
    float var_sum = 0.0;

    for (i = 0; i < 256; i++) {
        // hist[i] : number of pixel that has a specific hue
        // i : hue
        var_sum = (var_sum + ((i - mean)*(i - mean)*hist[i])) / (float)(lines*columns);
    }
    variance = (float)sqrt(var_sum);
    //variance=var_sum/((float)lines*columns); // Variance
    return variance;
}

void histogram_possibility_bw(int hist[], float possibility[]) {
    int i = 0;

    for (i = 0; i < 256; i++) {
        possibility[i] = hist[i] / ((float)lines*columns); // Possibilities of each hue to appear
    }
}

void histogram_equalization_bw(unsigned char ***image_in, unsigned char ***image_out, float possibility[]) {
    int i = 0;
    int j = 0;
    int k = 0;
    float hist_eq[256];

    hist_eq[0] = possibility[0];
    for (i = 1; i < 256; i++) {
        hist_eq[i] = hist_eq[i - 1] + possibility[i];
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            k = (*image_in)[i][j];
            (*image_out)[i][j] = (unsigned char)round(hist_eq[k] * 255.0); // Histogram equalization
        }
    }
}

void image_sum_bw(unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out) {
    int i = 0;
    int j = 0;
    int a = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            a = (*image_in1)[i][j] + (*image_in2)[i][j]; // Image summarization
            if (a > 255) {
                a = 255;
            }
            (*image_out)[i][j] = (unsigned char)a;
        }
    }
}

void image_sub_bw(unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out) {
    int i = 0;
    int j = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out)[i][j] = (*image_in1)[i][j] - (*image_in2)[i][j]; // Image subtraction
        }
    }
}

void image_convolution_bw(unsigned char ***image_in, unsigned char ***image_out, float **w, int size) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    double t = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out)[i][j] = 0;
        }
    }

    for (i = 1; i < lines - 1; i++) {
        for (j = 1; j < columns - 1; j++) {
            t = 0.0;
            for (k = 0; k < size; k++) {
                for (l = 0; l < size; l++) {
                    t = t + (*image_in)[i + k - 1][j + l - 1] * w[k][l]; // Image Convolution with one mask
                }
            }

            if (t > 255) {
                t = 255.0;
            } else if (t < 0) {
                t = 0.0;
            }
            (*image_out)[i][j] = (unsigned char)t;
        }
    }
}

void image_convolution_2d_bw(unsigned char ***image_in, unsigned char ***image_out, float **wx, float **wy, int size) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    double t = 0.0;
    double tx = 0.0;
    double ty = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out)[i][j] = 0;
        }
    }

    for (i = 1; i < lines - 1; i++) {
        for (j = 1; j < columns - 1; j++) {
            tx = 0.0;
            for (k = 0; k < size; k++) {
                for (l = 0; l < size; l++) {
                    tx = tx + (*image_in)[i + k - 1][j + l - 1] * wx[k][l]; // Image Convolution with one mask at X-Axis
                }
            }

            ty = 0.0;
            for (k = 0; k < size; k++) {
                for (l = 0; l < size; l++) {
                    ty = ty + (*image_in)[i + k - 1][j + l - 1] * wy[k][l]; // Image Convolution with one mask at Y-Axis
                }
            }

            t = sqrt(tx*tx + ty*ty);

            if (t > 255) {
                t = 255.0;
            } else if (t < 0) {
                t = 0.0;
            }

            (*image_out)[i][j] = (unsigned char)t;
        }
    }
}

void image_rotation_clockwise_bw (unsigned char ***image_in, unsigned char ***image_out) {
    int i = 0;
    int j = 0;
    int k = 0;

    k = lines - 1;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out)[j][k] = (*image_in)[i][j]; 	// 90 degrees clockwise
        }
        k--;
    }
}

void image_rotation_counterclockwise_bw (unsigned char ***image_in, unsigned char ***image_out) {
    int i = 0;
    int j = 0;
    int k = 0;

    k = lines - 1;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out)[i][j] = (*image_in)[j][k]; 	// 90 degrees counter-clockwise
        }
        k--;
    }
}




/****************************** COLOR ******************************/

void free_memory_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;

    for (i = 0; i < lines; i++) {
        free((*image_in_r)[i]);
        free((*image_in_g)[i]);
        free((*image_in_b)[i]);
        free((*image_out_r)[i]);
        free((*image_out_g)[i]);
        free((*image_out_b)[i]);
        (*image_in_r)[i] = NULL;
        (*image_in_g)[i] = NULL;
        (*image_in_b)[i] = NULL;
        (*image_out_r)[i] = NULL;
        (*image_out_g)[i] = NULL;
        (*image_out_b)[i] = NULL;
    }
    free(*image_in_r);
    free(*image_in_g);
    free(*image_in_b);
    free(*image_out_r);
    free(*image_out_g);
    free(*image_out_b);
    *image_in_r = NULL;
    *image_in_g = NULL;
    *image_in_b = NULL;
    *image_out_r = NULL;
    *image_out_g = NULL;
    *image_out_b = NULL;
}

void read_file_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    char filename_in[], FILE *fp_in
    ) {
    int i = 0;

    printf("Enter filename to read: ");
    scanf("%s", filename_in);

    printf("Number of lines: ");
    scanf("%d", &lines);

    printf("Number of columns: ");
    scanf("%d", &columns);

    printf("\n\nMemory allocation...\n");
    *image_in_r = (unsigned char**)malloc((lines)* sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_in_r)[i] = (unsigned char*)malloc((columns)* sizeof(unsigned char));
    }
    *image_in_g = (unsigned char**)malloc((lines)* sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_in_g)[i] = (unsigned char*)malloc((columns)* sizeof(unsigned char));
    }
    *image_in_b = (unsigned char**)malloc((lines)* sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_in_b)[i] = (unsigned char*)malloc((columns)* sizeof(unsigned char));
    }

    *image_out_r = (unsigned char**)malloc((lines)* sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_out_r)[i] = (unsigned char*)malloc((columns)* sizeof(unsigned char));
    }
    *image_out_g = (unsigned char**)malloc((lines)* sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_out_g)[i] = (unsigned char*)malloc((columns)* sizeof(unsigned char));
    }
    *image_out_b = (unsigned char**)malloc((lines)* sizeof(unsigned char*));
    for (i = 0; i < lines; i++) {
        (*image_out_b)[i] = (unsigned char*)malloc((columns)* sizeof(unsigned char));
    }

    printf("Reading file...\n\n");
    if (((fp_in = fopen(filename_in, "rb")) == NULL)) {
        printf("Not a valid input file\n");
    } else {
        for (i = 0; i < lines; i++) {
            fread((*image_in_r)[i], sizeof(unsigned char), columns, fp_in);
        }
        for (i = 0; i < lines; i++) {
            fread((*image_in_g)[i], sizeof(unsigned char), columns, fp_in);
        }
        for (i = 0; i < lines; i++) {
            fread((*image_in_b)[i], sizeof(unsigned char), columns, fp_in);
        }

        fclose(fp_in);
    }
}

void write_file_color(
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    char filename_out[], FILE *fp_out
    ) {
    int i = 0;

    printf("Enter filename to write: ");
    scanf("%s", filename_out);

    printf("\n\nWriting file...\n");
    if (((fp_out = fopen(filename_out, "wb")) == NULL)) {
        printf("Not a valid input file\n");
    } else {
        for (i = 0; i < lines; i++) {
            fwrite((*image_out_r)[i], sizeof(unsigned char), columns, fp_out);
        }
        for (i = 0; i < lines; i++) {
            fwrite((*image_out_g)[i], sizeof(unsigned char), columns, fp_out);
        }
        for (i = 0; i < lines; i++) {
            fwrite((*image_out_b)[i], sizeof(unsigned char), columns, fp_out);
        }

        fclose(fp_out);
    }
}

void image_shift_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    int n
    ) {
    int i = 0;
    int j = 0;
    double x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = (*image_in_r)[i][j] / pow(2, (8 - n)); //<< n // Left shift depending on how many bits we gave
            (*image_out_r)[i][j] = (unsigned char)x;

            x = (*image_in_g)[i][j] / pow(2, (8 - n)); //<< n // Left shift depending on how many bits we gave
            (*image_out_g)[i][j] = (unsigned char)x;

            x = (*image_in_b)[i][j] / pow(2, (8 - n)); //<< n // Left shift depending on how many bits we gave
            (*image_out_b)[i][j] = (unsigned char)x;
        }
    }
}

void image_threshold_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    int threshold
    ) {
    int i = 0;
    int j = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            // Check if image input (specific pixel) is higher or lower than the threshold we gave
            if ((*image_in_r)[i][j] > threshold || (*image_in_g)[i][j] > threshold || (*image_in_b)[i][j] > threshold) {
                (*image_out_r)[i][j] = 255;
                (*image_out_g)[i][j] = 255;
                (*image_out_b)[i][j] = 255;
            } else {
                (*image_out_r)[i][j] = 0;
                (*image_out_g)[i][j] = 0;
                (*image_out_b)[i][j] = 0;
            }
        }
    }
}

void image_negative_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out_r)[i][j] = 255 - (*image_in_r)[i][j]; // Creating a negative image
            (*image_out_g)[i][j] = 255 - (*image_in_g)[i][j]; // Creating a negative image
            (*image_out_b)[i][j] = 255 - (*image_in_b)[i][j]; // Creating a negative image
        }
    }
}

void image_sqrt_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out_r)[i][j] = (unsigned char)sqrt((*image_in_r)[i][j] * 255); // Square root calculation
            (*image_out_g)[i][j] = (unsigned char)sqrt((*image_in_g)[i][j] * 255); // Square root calculation
            (*image_out_b)[i][j] = (unsigned char)sqrt((*image_in_b)[i][j] * 255); // Square root calculation
        }
    }
}

void image_contrast_enhancement_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float a, float b
    ) {
    int i = 0;
    int j = 0;
    float x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = ((*image_in_r)[i][j] + a)*b; // Contrast Enhancement
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_r)[i][j] = (unsigned char)x;

            x = ((*image_in_g)[i][j] + a)*b; // Contrast Enhancement
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_g)[i][j] = (unsigned char)x;

            x = ((*image_in_b)[i][j] + a)*b; // Contrast Enhancement
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_b)[i][j] = (unsigned char)x;
        }
    }
}

void image_brightness_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float a
    ) {
    int i = 0;
    int j = 0;
    float x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = (*image_in_r)[i][j] + a; // Brightness
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_r)[i][j] = (unsigned char)x;

            x = (*image_in_g)[i][j] + a; // Brightness
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_g)[i][j] = (unsigned char)x;

            x = (*image_in_b)[i][j] + a; // Brightness
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_b)[i][j] = (unsigned char)x;
        }
    }
}

void image_contrast_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float b
    ) {
    int i = 0;
    int j = 0;
    float x = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            x = (*image_in_r)[i][j] * b; // Contrast
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_r)[i][j] = (unsigned char)x;

            x = (*image_in_g)[i][j] * b; // Contrast
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_g)[i][j] = (unsigned char)x;

            x = (*image_in_b)[i][j] * b; // Contrast
            if (x > 255) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            (*image_out_b)[i][j] = (unsigned char)x;
        }
    }
}

void histogram_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    int hist_r[], int hist_g[], int hist_b[]
    ) {
    int i = 0;
    int j = 0;
    int l = 0;

    for (i = 0; i < 256; i++) {
        hist_r[i] = 0;
        hist_g[i] = 0;
        hist_b[i] = 0;
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            l = (*image_in_r)[i][j];
            hist_r[l]++; // Printing histogram
            l = (*image_in_g)[i][j];
            hist_g[l]++; // Printing histogram
            l = (*image_in_b)[i][j];
            hist_b[l]++; // Printing histogram
        }
    }
}

void histogram_min_color(
    int hist_r[], int hist_g[], int hist_b[],
    int *min_r, int *min_g, int *min_b,
    int *min_pos_r, int *min_pos_g, int *min_pos_b
    ) {
    int i = 0;
    *min_r = 0;
    *min_g = 0;
    *min_b = 0;
    *min_pos_r = 300;
    *min_pos_g = 300;
    *min_pos_b = 300;

    for (i = 0; i < 256; i++) {
        if ((hist_r[i] != 0) && (i < (*min_pos_r))) {
            *min_r = hist_r[i];	// MIN hue in the image
            *min_pos_r = i;		// or min=hist[i];
        }

        if ((hist_g[i] != 0) && (i < (*min_pos_g))) {
            *min_g = hist_g[i];	// MIN hue in the image
            *min_pos_g = i;		// or min=hist[i];
        }

        if ((hist_b[i] != 0) && (i < (*min_pos_b))) {
            *min_b = hist_b[i];	// MIN hue in the image
            *min_pos_b = i;		// or min=hist[i];
        }
    }
}

void histogram_max_color(
    int hist_r[], int hist_g[], int hist_b[],
    int *max_r, int *max_g, int *max_b,
    int *max_pos_r, int *max_pos_g, int *max_pos_b
    ) {
    int i = 0;
    *max_r = 0; // allios max=hist[0]; an den kseroume ti domi tou pinaka
    *max_g = 0; // allios max=hist[0]; an den kseroume ti domi tou pinaka
    *max_b = 0; // allios max=hist[0]; an den kseroume ti domi tou pinaka
    *max_pos_r = -1;
    *max_pos_g = -1;
    *max_pos_b = -1;

    for (i = 0; i < 256; i++) {
        if ((hist_r[i] != 0) && (i >(*max_pos_r))) {
            *max_r = hist_r[i];	// MAX hue in the image
            *max_pos_r = i;		// or max=hist[i]
        }

        if ((hist_g[i] != 0) && (i > (*max_pos_g))) {
            *max_g = hist_g[i];	// MAX hue in the image
            *max_pos_g = i;		// or max=hist[i]
        }

        if ((hist_b[i] != 0) && (i > (*max_pos_b))) {
            *max_b = hist_b[i];	// MAX hue in the image
            *max_pos_b = i;		// or max=hist[i]
        }
    }
}

float histogram_mean_color(
    int hist_r[], int hist_g[], int hist_b[]
    ) {
    int i = 0;
    float mean = 0.0;
    float hist_sum_r = 0.0;
    float hist_sum_g = 0.0;
    float hist_sum_b = 0.0;

    for (i = 0; i < 256; i++) {
        // hist[i] : number of pixel that has a specific hue
        // i : hue
        hist_sum_r = hist_sum_r + (i*hist_r[i]);
        hist_sum_g = hist_sum_g + (i*hist_g[i]);
        hist_sum_b = hist_sum_b + (i*hist_b[i]);
    }
    mean = (hist_sum_r + hist_sum_g + hist_sum_b) / (float)(lines*columns); // Mean value
    return mean;
}

float histogram_variance_color(
    int hist_r[], int hist_g[], int hist_b[], float mean
    ) {
    int i = 0;
    float variance = 0.0;
    float var_sum_r = 0.0;
    float var_sum_g = 0.0;
    float var_sum_b = 0.0;

    for (i = 0; i < 256; i++) {
        // hist[i] : number of pixel that has a specific hue
        // i : hue
        var_sum_r = (var_sum_r + ((i - mean)*(i - mean)*hist_r[i])) / (float)(lines*columns);
        var_sum_g = (var_sum_g + ((i - mean)*(i - mean)*hist_g[i])) / (float)(lines*columns);
        var_sum_b = (var_sum_b + ((i - mean)*(i - mean)*hist_b[i])) / (float)(lines*columns);
    }
    variance = (float)sqrt(var_sum_r + var_sum_g + var_sum_b);
    //variance=var_sum/((float)lines*columns); // Variance
    return variance;
}

void histogram_possibility_color(
    int hist_r[], int hist_g[], int hist_b[],
    float possibility_r[], float possibility_g[], float possibility_b[]
    ) {
    int i = 0;

    for (i = 0; i < 256; i++) {
        possibility_r[i] = hist_r[i] / (float)(lines*columns); // Possibilities of each hue to appear
        possibility_g[i] = hist_g[i] / (float)(lines*columns); // Possibilities of each hue to appear
        possibility_b[i] = hist_b[i] / (float)(lines*columns); // Possibilities of each hue to appear
    }
}

void histogram_equalization_rgb_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float possibility_r[], float possibility_g[], float possibility_b[]
    ) {
    int i = 0;
    int j = 0;
    int k = 0;
    float hist_eq_r[256];
    float hist_eq_g[256];
    float hist_eq_b[256];

    hist_eq_r[0] = possibility_r[0];
    hist_eq_g[0] = possibility_g[0];
    hist_eq_b[0] = possibility_b[0];
    for (i = 1; i < 256; i++) {
        hist_eq_r[i] = hist_eq_r[i - 1] + possibility_r[i];
        hist_eq_g[i] = hist_eq_g[i - 1] + possibility_g[i];
        hist_eq_b[i] = hist_eq_b[i - 1] + possibility_b[i];
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            k = (*image_in_r)[i][j];
            (*image_out_r)[i][j] = (unsigned char)round(hist_eq_r[k] * 255.0); // Histogram equalization
            k = (*image_in_g)[i][j];
            (*image_out_g)[i][j] = (unsigned char)round(hist_eq_g[k] * 255.0); // Histogram equalization
            k = (*image_in_b)[i][j];
            (*image_out_b)[i][j] = (unsigned char)round(hist_eq_b[k] * 255.0); // Histogram equalization
        }
    }
}

void histogram_equalization_hsv_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;
    int k = 0;
    int hist_v[256];
    double **R;
    double **G;
    double **B;
    double **H;
    double **S;
    double **V;
    double s_hist_eq_v[256];
    double sum_of_hist_v[256];
    double max = 0.0;
    double min = 0.0;
    double chroma = 0.0;
    double tmp = 0.0;
    double c = 0.0;
    double m = 0.0;
    double x = 0.0;
    long n = 0;

    R = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        R[i] = (double*)malloc((columns)* sizeof(double));
    }

    G = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        G[i] = (double*)malloc((columns)* sizeof(double));
    }

    B = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        B[i] = (double*)malloc((columns)* sizeof(double));
    }

    H = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        H[i] = (double*)malloc((columns)* sizeof(double));
    }

    S = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        S[i] = (double*)malloc((columns)* sizeof(double));
    }

    V = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        V[i] = (double*)malloc((columns)* sizeof(double));
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            // unsigned char to double
            R[i][j] = (double)(*image_in_r)[i][j]; // R
            G[i][j] = (double)(*image_in_g)[i][j]; // G
            B[i][j] = (double)(*image_in_b)[i][j]; // B
            R[i][j] = R[i][j] / 255.0; // [0..1]
            G[i][j] = G[i][j] / 255.0; // [0..1]
            B[i][j] = B[i][j] / 255.0; // [0..1]

            // RGB to HSV conversion
            min = MIN(R[i][j], MIN(G[i][j], B[i][j]));
            max = MAX(R[i][j], MAX(G[i][j], B[i][j]));
            chroma = max - min;
            H[i][j] = 0;
            S[i][j] = 0;
            if (chroma != 0.0) {
                if (fabs(R[i][j] - max) < 0.00001) {
                    H[i][j] = ((G[i][j] - B[i][j]) / chroma);
                    H[i][j] = fmod(H[i][j], 6.0);	//H[i][j]=H[i][j]%6.0;
                } else if (fabs(G[i][j] - max) < 0.00001) {
                    H[i][j] = ((B[i][j] - R[i][j]) / chroma) + 2;
                } else {
                    H[i][j] = ((R[i][j] - G[i][j]) / chroma) + 4;	//fB[i][j]==max
                }

                H[i][j] = H[i][j] * 60.0;
                if (H[i][j] < 0.0) {
                    H[i][j] = H[i][j] + 360;
                }
                S[i][j] = chroma / max;
            }
            V[i][j] = max;

            // Checks
            V[i][j] = V[i][j] * 255;

            if (V[i][j] > 255) V[i][j] = 255;
            if (V[i][j] < 0) V[i][j] = 0;
        }
    }

    for (i = 0; i < 256; i++) {
        hist_v[i] = 0;
        s_hist_eq_v[i] = 0.0;
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            k = (int)V[i][j];
            hist_v[k]++;
        }
    }

    n = lines * columns;

    for (i = 0; i < 256; i++)  // pdf of image
    {
        s_hist_eq_v[i] = (double)hist_v[i] / (double)n;
    }

    sum_of_hist_v[0] = s_hist_eq_v[0];
    for (i = 1; i < 256; i++)        // cdf of image
    {
        sum_of_hist_v[i] = sum_of_hist_v[i - 1] + s_hist_eq_v[i];
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            k = (int)V[i][j];
            V[i][j] = (unsigned char)round(sum_of_hist_v[k] * 255.0);
            V[i][j] = V[i][j] / 255;

            // HSV to RGB conversion
            c = V[i][j] * S[i][j];
            x = c * (1.0 - fabs(fmod(H[i][j] / 60.0, 2) - 1.0));
            m = V[i][j] - c;

            if (H[i][j] >= 0.0 && H[i][j] < 60.0) {
                R[i][j] = c;
                G[i][j] = x;
                B[i][j] = 0;
            } else if (H[i][j] >= 60.0 && H[i][j] < 120.0) {
                R[i][j] = x;
                G[i][j] = c;
                B[i][j] = 0;
            } else if (H[i][j] >= 120.0 && H[i][j] < 180.0) {
                R[i][j] = 0;
                G[i][j] = c;
                B[i][j] = x;
            } else if (H[i][j] >= 180.0 && H[i][j] < 240.0) {
                R[i][j] = 0;
                G[i][j] = x;
                B[i][j] = c;
            } else if (H[i][j] >= 240.0 && H[i][j] < 300.0) {
                R[i][j] = x;
                G[i][j] = 0;
                B[i][j] = c;
            } else if (H[i][j] >= 300.0 && H[i][j] < 360.0) {
                R[i][j] = c;
                G[i][j] = 0;
                B[i][j] = x;
            }

            R[i][j] = R[i][j] + m;
            G[i][j] = G[i][j] + m;
            B[i][j] = B[i][j] + m;

            // Checks
            R[i][j] = R[i][j] * 255;
            G[i][j] = G[i][j] * 255;
            B[i][j] = B[i][j] * 255;

            if (R[i][j] > 255) R[i][j] = 255;
            if (R[i][j] < 0) R[i][j] = 0;
            if (G[i][j] > 255) G[i][j] = 255;
            if (G[i][j] < 0) G[i][j] = 0;
            if (B[i][j] > 255) B[i][j] = 255;
            if (B[i][j] < 0) B[i][j] = 0;

            // Save changes
            (*image_out_r)[i][j] = (unsigned char)(R[i][j]);
            (*image_out_g)[i][j] = (unsigned char)(G[i][j]);
            (*image_out_b)[i][j] = (unsigned char)(B[i][j]);
        }
    }
}

void histogram_equalization_yuv_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;
    int k = 0;
    int hist_y[256];
    double **R;
    double **G;
    double **B;
    double **Y;
    double **U;
    double **V;
    double s_hist_eq_y[256];
    double sum_of_hist_y[256];
    double max = 0.0;
    double min = 0.0;
    double chroma = 0.0;
    double tmp = 0.0;
    double c = 0.0;
    double m = 0.0;
    double x = 0.0;
    long n = 0;

    R = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        R[i] = (double*)malloc((columns)* sizeof(double));
    }

    G = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        G[i] = (double*)malloc((columns)* sizeof(double));
    }

    B = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        B[i] = (double*)malloc((columns)* sizeof(double));
    }

    Y = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        Y[i] = (double*)malloc((columns)* sizeof(double));
    }

    U = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        U[i] = (double*)malloc((columns)* sizeof(double));
    }

    V = (double**)malloc((lines)* sizeof(double*));
    for (i = 0; i < lines; i++) {
        V[i] = (double*)malloc((columns)* sizeof(double));
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            // unsigned char to double
            R[i][j] = (double)(*image_in_r)[i][j]; // R
            G[i][j] = (double)(*image_in_g)[i][j]; // G
            B[i][j] = (double)(*image_in_b)[i][j]; // B
            R[i][j] = R[i][j] / 255.0; // [0..1]
            G[i][j] = G[i][j] / 255.0; // [0..1]
            B[i][j] = B[i][j] / 255.0; // [0..1]

            // RGB to YUV conversion
            Y[i][j] = (0.299*R[i][j]) + (0.587*G[i][j]) + (0.114*B[i][j]); // Y
            U[i][j] = (-0.14713*R[i][j]) - (0.28886*G[i][j]) + (0.436*B[i][j]); // U
            V[i][j] = (0.615*R[i][j]) - (0.51499*G[i][j]) - (0.10001*B[i][j]); // V

            // Checks
            Y[i][j] = Y[i][j] * 255;
            if (Y[i][j] > 255) Y[i][j] = 255;
            if (Y[i][j] < 0) Y[i][j] = 0;
        }
    }

    for (i = 0; i < 256; i++) {
        hist_y[i] = 0;
        s_hist_eq_y[i] = 0.0;
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            k = (int)Y[i][j];
            hist_y[k]++;
        }
    }

    n = lines * columns;

    for (i = 0; i < 256; i++)  // pdf of image
    {
        s_hist_eq_y[i] = (double)hist_y[i] / (double)n;
    }

    sum_of_hist_y[0] = s_hist_eq_y[0];
    for (i = 1; i < 256; i++)        // cdf of image
    {
        sum_of_hist_y[i] = sum_of_hist_y[i - 1] + s_hist_eq_y[i];
    }

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            k = (int)Y[i][j];
            Y[i][j] = (unsigned char)round(sum_of_hist_y[k] * 255.0);
            Y[i][j] = Y[i][j] / 255;

            // YUV to RGB conversion
            R[i][j] = Y[i][j] + (0 * U[i][j]) + (1.13983*V[i][j]);
            G[i][j] = Y[i][j] + (-0.39465*U[i][j]) + (-0.58060*V[i][j]);
            B[i][j] = Y[i][j] + (2.03211*U[i][j]) + (0 * V[i][j]);

            // Checks
            R[i][j] = R[i][j] * 255;
            G[i][j] = G[i][j] * 255;
            B[i][j] = B[i][j] * 255;

            if (R[i][j]>255) R[i][j] = 255;
            if (R[i][j] < 0) R[i][j] = 0;
            if (G[i][j] > 255) G[i][j] = 255;
            if (G[i][j] < 0) G[i][j] = 0;
            if (B[i][j] > 255) B[i][j] = 255;
            if (B[i][j] < 0) B[i][j] = 0;

            // Save changes
            (*image_out_r)[i][j] = (unsigned char)(R[i][j]);
            (*image_out_g)[i][j] = (unsigned char)(G[i][j]);
            (*image_out_b)[i][j] = (unsigned char)(B[i][j]);
        }
    }
}

void image_convolution_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float **w, int size
    ) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    double tR = 0.0;
    double tG = 0.0;
    double tB = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out_r)[i][j] = 0;
            (*image_out_g)[i][j] = 0;
            (*image_out_b)[i][j] = 0;
        }
    }

    for (i = 1; i < lines - 1; i++) {
        for (j = 1; j < columns - 1; j++) {
            tR = 0.0;
            tG = 0.0;
            tB = 0.0;
            for (k = 0; k < size; k++) {
                for (l = 0; l < size; l++) {
                    tR = tR + (*image_in_r)[i + k - 1][j + l - 1] * w[k][l]; // Image Convolution with one mask
                    tG = tG + (*image_in_g)[i + k - 1][j + l - 1] * w[k][l]; // Image Convolution with one mask
                    tB = tB + (*image_in_b)[i + k - 1][j + l - 1] * w[k][l]; // Image Convolution with one mask
                }
            }

            if (tR > 255 || tG > 255 || tB > 255) {
                tR = 255.0;
                tG = 255.0;
                tB = 255.0;
            } else if (tR < 0 || tG < 0.0 || tB < 0.0) {
                tR = 0.0;
                tG = 0.0;
                tB = 0.0;
            }

            (*image_out_r)[i][j] = (unsigned char)tR;
            (*image_out_g)[i][j] = (unsigned char)tG;
            (*image_out_b)[i][j] = (unsigned char)tB;
        }
    }
}

void image_convolution_2d_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b,
    float **wx, float **wy, int size
    ) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    double tR = 0.0;
    double tG = 0.0;
    double tB = 0.0;
    double txR = 0.0;
    double txG = 0.0;
    double txB = 0.0;
    double tyR = 0.0;
    double tyG = 0.0;
    double tyB = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            (*image_out_r)[i][j] = 0;
            (*image_out_g)[i][j] = 0;
            (*image_out_b)[i][j] = 0;
        }
    }

    for (i = 1; i < lines - 1; i++) {
        for (j = 1; j < columns - 1; j++) {
            txR = 0.0;
            txG = 0.0;
            txB = 0.0;
            tyR = 0.0;
            tyG = 0.0;
            tyB = 0.0;
            for (k = 0; k < size; k++) {
                for (l = 0; l < size; l++) {
                    txR = txR + (*image_in_r)[i + k - 1][j + l - 1] * wx[k][l]; // Image Convolution with one mask at X-Axis
                    txG = txG + (*image_in_g)[i + k - 1][j + l - 1] * wx[k][l]; // Image Convolution with one mask at X-Axis
                    txB = txB + (*image_in_b)[i + k - 1][j + l - 1] * wx[k][l]; // Image Convolution with one mask at X-Axis
                    tyR = tyR + (*image_in_r)[i + k - 1][j + l - 1] * wy[k][l]; // Image Convolution with one mask at Y-Axis
                    tyG = tyG + (*image_in_g)[i + k - 1][j + l - 1] * wy[k][l]; // Image Convolution with one mask at Y-Axis
                    tyB = tyB + (*image_in_b)[i + k - 1][j + l - 1] * wy[k][l]; // Image Convolution with one mask at Y-Axis
                }
            }

            tR = sqrt(txR*txG + tyR*tyR);
            tG = sqrt(txR*txG + tyG*tyG);
            tB = sqrt(txR*txB + tyB*tyB);

            if (tR > 255.0 || tG > 255.0 || tB > 255.0) {
                tR = 255.0;
                tG = 255.0;
                tB = 255.0;
            } else if (tR < 0.0 || tG < 0.0 || tB < 0.0) {
                tR = 0.0;
                tG = 0.0;
                tB = 0.0;
            }

            (*image_out_r)[i][j] = (unsigned char)tR;
            (*image_out_g)[i][j] = (unsigned char)tG;
            (*image_out_b)[i][j] = (unsigned char)tB;
        }
    }
}

void image_rotation_clockwise_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;
    int k = 0;

    k = lines - 1;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            // 90 degrees clockwise
            (*image_out_r)[j][k] = (*image_in_r)[i][j];
            (*image_out_g)[j][k] = (*image_in_g)[i][j];
            (*image_out_b)[j][k] = (*image_in_b)[i][j];
        }
        k--;
    }
}

void image_rotation_counterclockwise_color(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;
    int k = 0;

    k = lines - 1;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            // 90 degrees counter-clockwise
            (*image_out_r)[i][j] = (*image_in_r)[j][k];
            (*image_out_g)[i][j] = (*image_in_g)[j][k];
            (*image_out_b)[i][j] = (*image_in_b)[j][k];
        }
        k--;
    }
}

void color_to_grayscale(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;
    double y = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            y = (*image_in_b)[i][j] * 0.114 + (*image_in_g)[i][j] * 0.587 + (*image_in_r)[i][j] * 0.299;
            (*image_out_r)[i][j] = (unsigned char)y;
            (*image_out_g)[i][j] = (unsigned char)y;
            (*image_out_b)[i][j] = (unsigned char)y;
        }
    }
}

void sepia_tone(
    unsigned char ***image_in_r, unsigned char ***image_in_g, unsigned char ***image_in_b,
    unsigned char ***image_out_r, unsigned char ***image_out_g, unsigned char ***image_out_b
    ) {
    int i = 0;
    int j = 0;
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            r = (*image_in_b)[i][j] * 0.189 + (*image_in_g)[i][j] * 0.769 + (*image_in_r)[i][j] * 0.393;
            g = (*image_in_b)[i][j] * 0.168 + (*image_in_g)[i][j] * 0.686 + (*image_in_r)[i][j] * 0.349;
            b = (*image_in_b)[i][j] * 0.131 + (*image_in_g)[i][j] * 0.534 + (*image_in_r)[i][j] * 0.272;
            (*image_out_r)[i][j] = r > 255 ? (unsigned char)255 : (unsigned char)r;
            (*image_out_g)[i][j] = g > 255 ? (unsigned char)255 : (unsigned char)g;
            (*image_out_b)[i][j] = b > 255 ? (unsigned char)255 : (unsigned char)b;
        }
    }
}
