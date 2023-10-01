#include "threshold.h"
#include "stif.h"
#include "histogram.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char *threshold_std(unsigned char *channel, int size, unsigned char th)
{
	unsigned char *uchar = (unsigned char *)malloc(sizeof(unsigned char)*(size));
	for(int i=0; i<size; i++){
		uchar[i] = (channel[i] < th)? 0:255;
	}

	return uchar;
}

unsigned char *threshold_mean(unsigned char *channel, int size)
{
	float mean = stif_mean(channel, size);

	return threshold_std(channel, size, (unsigned char)mean);
}

unsigned char *threshold_median(unsigned char *channel, int size)
{
	int median = stif_median(channel, size);

	return threshold_std(channel, size, (unsigned char)median);
}

unsigned char *threshold_lmean(unsigned char *channel,
				      int width, int height, int half_width)
{
	unsigned char *uchar = (unsigned char *)malloc(sizeof(unsigned char)*(width*height));
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			float lmean = stif_lmean(channel, width, height, i, j, half_width);
			uchar[(i*width)+j] = (channel[(i*width)+j] < lmean)? 0:255;
		}
	}
	return uchar;
}

unsigned char *threshold_percent(unsigned char *channel, int size, float percent)
{
	float *hist = histogram_make(channel, size);
	histogram_normalize(hist);
	histogram_cumulate(hist);
	float p = ((percent)/100);

	int i=0;
	while(hist[i] <= p)
	{
		i++;
	}

	
	return threshold_std(channel, size, (unsigned char)i);
}


