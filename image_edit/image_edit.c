#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image_edit.h"


void release_memory(unsigned char ***image_in, unsigned char ***image_out)
{
	int i = 0;

	for (i = 0; i < lines; i++)
	{
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


void release_memory_sum_sub(unsigned char ***image_in, unsigned char ***image_in1, unsigned char ***image_in2, unsigned char ***image_out)
{
	int i = 0;

	if (*image_in == NULL || *image_out == NULL)
	{
		printf("Memory already released! (image_in, image_out)");
		for (i = 0; i < lines; i++)
		{
			free((*image_in1)[i]);
			free((*image_in2)[i]);
		}
		free(*image_in1);
		free(*image_in2);
		*image_in1 = NULL;
		*image_in2 = NULL;
	}
	else
	{
		for (i = 0; i < lines; i++)
		{
			free((*image_in)[i]);
			free((*image_in1)[i]);
			free((*image_in2)[i]);
			free((*image_out)[i]);
		}
		free(*image_in);
		free(*image_in1);
		free(*image_in2);
		free(*image_out);
		*image_in = NULL;
		*image_in1 = NULL;
		*image_in2 = NULL;
		*image_out = NULL;
	}
}


void read_file(unsigned char ***image_in, unsigned char ***image_out, char filename_in[], FILE *fp_in)
{
	int i = 0;

	printf("Enter filename to read: ");
	scanf("%s", filename_in);

	printf("Number of lines: ");
	scanf("%d", &lines);

	printf("Number of columns: ");
	scanf("%d", &columns);

	printf("\n\nMemory allocation...\n");
	*image_in = (unsigned char**)malloc((lines)*sizeof(unsigned char*));
	for (i = 0; i < lines; i++)
	{
		(*image_in)[i] = (unsigned char*)malloc((columns)*sizeof(unsigned char));
	}

	*image_out = (unsigned char**)malloc((lines)*sizeof(unsigned char*));
	for (i = 0; i < lines; i++)
	{
		(*image_out)[i] = (unsigned char*)malloc((columns)*sizeof(unsigned char));
	}

	fp_in = fopen(filename_in, "rb");
	printf("Reading file...\n");
	for (i = 0; i < lines; i++)
	{
		fread((*image_in)[i], sizeof(unsigned char), columns, fp_in);
	}
	fclose(fp_in);
}


void read_file_sum_sub(unsigned char ***image_in1, unsigned char ***image_in2, char filename_in[], FILE *fp_in)
{
	int i = 0;

	printf("\n\nMemory allocation...\n");
	*image_in1 = (unsigned char**)malloc((lines)*sizeof(unsigned char*));
	for (i = 0; i < lines; i++)
	{
		(*image_in1)[i] = (unsigned char*)malloc((columns)*sizeof(unsigned char));
	}

	*image_in2 = (unsigned char**)malloc((lines)*sizeof(unsigned char*));
	for (i = 0; i < lines; i++)
	{
		(*image_in2)[i] = (unsigned char*)malloc((columns)*sizeof(unsigned char));
	}

	fp_in = fopen(filename_in, "rb");
	printf("Reading file...\n");
	for (i = 0; i < lines; i++)
	{
		fread((*image_in1)[i], sizeof(unsigned char), columns, fp_in);
	}
	fclose(fp_in);

	fp_in = fopen(filename_in, "rb");
	for (i = 0; i < lines; i++)
	{
		fread((*image_in2)[i], sizeof(unsigned char), columns, fp_in);
	}
	fclose(fp_in);
}


void write_file(unsigned char ***image_in, unsigned char ***image_out, char filename_out[], FILE *fp_out)
{
	int i = 0;

	printf("Enter filename to write: ");
	scanf("%s", filename_out);	

	fp_out = fopen(filename_out, "wb");
	printf("\n\nWriting file...\n");
	for (i = 0; i < lines; i++)
	{
		fwrite((*image_out)[i], sizeof(unsigned char), columns, fp_out);
	}
	fclose(fp_out);
}


void write_file_histogram(char filename_out2[], FILE *fp_out2, int hist[], float possibility[], float mean, float variance, int *min, int *max, int *min_pos, int *max_pos)
{
	int i = 0;

	printf("Enter filename to write histogram: ");
	scanf("%s", filename_out2);

	fp_out2 = fopen(filename_out2, "wb");
	printf("\n\nWriting file...\n");
	for (i = 0; i < 256; i++)
	{
		fprintf(fp_out2, "hist[%d] = %d\n", i, hist[i]);
	}
	fprintf(fp_out2, "\n\n----\n\n");
	fprintf(fp_out2, "min position\t= %d\t|\thue population at min = %d\n", min_pos, min);
	fprintf(fp_out2, "max position\t= %d\t|\thue population at max = %d\n", max_pos, max);
	fprintf(fp_out2, "mean value\t= %f\n", mean);
	fprintf(fp_out2, "variance\t= %f\n", variance);
	fprintf(fp_out2, "\n----\n\n\n");
	for (i = 0; i < 256; i++)
	{
		fprintf(fp_out2, "possibility[%d] = %f\t=>\t%.2f%%\n", i, possibility[i], possibility[i] * 100); // Printing possibility and possibility in percentag;
	}
	fclose(fp_out2);
}


void image_shift(unsigned char **image_in, unsigned char **image_out, int n)
{
	int i = 0;
	int j = 0;
	double x = 0.0;
	
	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			x = image_in[i][j] / pow(2, (8 - n)); //<< n // Left shift depending on how many bits we gave
			image_out[i][j] = (unsigned char)x;
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


void image_threshold(unsigned char **image_in, unsigned char **image_out, int threshold)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			if (image_in[i][j] > threshold) // Check if image input (specific pixel) is higher or lower than the threshold we gave
			{
				image_out[i][j] = 255;
			}
			else
			{
				image_out[i][j] = 0;
			}
		}
	}
}


void image_negative(unsigned char **image_in, unsigned char **image_out)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			image_out[i][j] = 255 - image_in[i][j]; // Creating a negative image
		}
	}
}


void image_sqrt(unsigned char **image_in, unsigned char **image_out)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			image_out[i][j] = (unsigned char)sqrt(image_in[i][j] * 255); // Square root calculation
		}
	}
}


void image_contrast_enhancement(unsigned char **image_in, unsigned char **image_out, float a, float b)
{
	int i = 0;
	int j = 0;
	float x = 0.0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			x = (image_in[i][j] + a)*b; // Contrast Enhancement
			if (x > 255)
			{
				x = 255;
			}
			else if (x < 0)
			{
				x = 0;
			}
			image_out[i][j] = (unsigned char)x;
		}
	}
}


void image_brightness(unsigned char **image_in, unsigned char **image_out, float a)
{
	int i = 0;
	int j = 0;
	float x = 0.0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			x = image_in[i][j] + a; // Brightness
			if (x > 255)
			{
				x = 255;
			}
			else if (x < 0)
			{
				x = 0;
			}
			image_out[i][j] = (unsigned char)x;
		}
	}
}


void image_contrast(unsigned char **image_in, unsigned char **image_out, float b)
{
	int i = 0;
	int j = 0;
	float x = 0.0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			x = image_in[i][j] * b; // Contrast
			if (x > 255)
			{
				x = 255;
			}
			else if (x < 0)
			{
				x = 0;
			}
			image_out[i][j] = (unsigned char)x;
		}
	}
}


void histogram(unsigned char **image_in, int hist[])
{
	int i = 0;
	int j = 0;
	int l = 0;

	for (i = 0; i < 256; i++)
	{
		hist[i] = 0;
	}

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			l = image_in[i][j];
			hist[l]++; // Printing histogram
		}
	}
}


void histogram_min(int hist[], int *min, int *min_pos)
{
	int i = 0;
	*min = 0;
	*min_pos = 300;

	for (i = 0; i < 256; i++)
	{
		if ((hist[i] != 0) && (i < (*min_pos)))
		{
			*min = hist[i];	// MIN hue in the image
			*min_pos = i;		// or min=hist[i];
		}
	}
}


void histogram_max(int hist[], int *max, int *max_pos)
{
	int i = 0;
	*max = 0; // allios max=hist[0]; an den kseroume ti domi tou pinaka
	*max_pos = -1;

	for (i = 0; i < 256; i++)
	{
		if ((hist[i] != 0) && (i > (*max_pos)))
		{
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


void histogram_possibility(int hist[], float possibility[])
{
	int i = 0;

	for (i = 0; i < 256; i++)
	{
		possibility[i] = hist[i] / ((float)lines*columns); // Possibilities of each hue to appear
	}
}


void histogram_equalization_rgb(unsigned char **image_in, unsigned char **image_out, float possibility[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	float hist_eq[256];

	hist_eq[0] = possibility[0];
	for (i = 1; i < 256; i++)
	{
		hist_eq[i] = hist_eq[i - 1] + possibility[i];
	}

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			k = image_in[i][j];
			image_out[i][j] = (unsigned char)round(hist_eq[k] * 255.0); // Histogram equalization
		}
	}
}


float histogram_mean(int hist[])
{
	int i = 0;
	float mean = 0;
	float hist_sum = 0;

	for (i = 0; i < 256; i++)
	{
		// hist[i] : number of pixel that has a specific hue
		// i : hue
		hist_sum = hist_sum + (i*hist[i]);
	}
	mean = hist_sum / ((float)lines*columns); // Mean value
	return mean;
}


float histogram_variance(int hist[], float mean)
{
	int i = 0;
	float variance = 0.0;
	float var_sum = 0.0;

	for (i = 0; i < 256; i++)
	{
		// hist[i] : number of pixel that has a specific hue
		// i : hue
		var_sum = var_sum + ((i - mean)*(i - mean)*hist[i] / ((float)lines*columns));
	}
	variance = (float)sqrt(var_sum);
	//variance=var_sum/((float)lines*columns); // Variance
	return variance;
}


void image_sum(unsigned char **image_in1, unsigned char **image_in2, unsigned char **image_out)
{
	int i = 0;
	int j = 0;
	int a = 0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			a = image_in1[i][j] + image_in2[i][j]; // Image summarization
			if (a > 255)
			{
				a = 255;
			}
			image_out[i][j] = (unsigned char)a;
		}
	}
}


void image_sub(unsigned char **image_in1, unsigned char **image_in2, unsigned char **image_out)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			image_out[i][j] = image_in1[i][j] - image_in2[i][j]; // Image subtraction
		}
	}
}


void image_convolution(unsigned char **image_in, unsigned char **image_out, float **w, int size)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	double t = 0.0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			image_out[i][j] = 0;
		}
	}

	for (i = 1; i < lines - 1; i++)
	{
		for (j = 1; j < columns - 1; j++)
		{
			t = 0.0;
			for (k = 0; k < size; k++)
			{
				for (l = 0; l < size; l++)
				{
					t = t + image_in[i + k - 1][j + l - 1] * w[k][l]; // Image Convolution with one mask
				}
			}

			if (t > 255)
			{
				t = 255.0;
			}
			else if (t < 0)
			{
				t = 0.0;
			}
			image_out[i][j] = (unsigned char)t;
		}
	}
}


void image_convolution_2d(unsigned char **image_in, unsigned char **image_out, float **wx, float **wy, int size)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	double t = 0.0;
	double tx = 0.0;
	double ty = 0.0;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < columns; j++)
		{
			image_out[i][j] = 0;
		}
	}

	for (i = 1; i < lines - 1; i++)
	{
		for (j = 1; j < columns - 1; j++)
		{
			tx = 0.0;
			for (k = 0; k < size; k++)
			{
				for (l = 0; l < size; l++)
				{
					tx = tx + image_in[i + k - 1][j + l - 1] * wx[k][l]; // Image Convolution with one mask at X-Axis
				}
			}

			ty = 0.0;
			for (k = 0; k < size; k++)
			{
				for (l = 0; l < size; l++)
				{
					ty = ty + image_in[i + k - 1][j + l - 1] * wy[k][l]; // Image Convolution with one mask at Y-Axis
				}
			}

			t = sqrt(tx*tx + ty*ty);

			if (t > 255)
			{
				t = 255.0;
			}
			else if (t < 0)
			{
				t = 0.0;
			}

			image_out[i][j] = (unsigned char)t;
		}
	}
}
