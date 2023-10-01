#include <stdlib.h>
#include <stdio.h>
#include "histogram.h"
#include "bbox.h"

float *histogram_make(unsigned char *channel, int size)
{
    float *histogram = malloc(HISTOGRAM_NLEV*sizeof(float));
    for(int i=0; i<HISTOGRAM_NLEV; i++){
        histogram[i] = 0;
    }
    for(int i=0; i<size; i++){
        histogram[channel[i]]++;
    }

    return histogram;
}

float *histogram_make_local(unsigned char *channel, int width, int height,
				   int i, int j, int half_width)
{
    float *histogram = malloc(HISTOGRAM_NLEV*sizeof(float));
    struct bbox box = bbox_init(width, height, i, j, half_width);

    for(int i=0; i<HISTOGRAM_NLEV; i++){
        histogram[i] = 0;
    }


    for(int index_i=box.imin; index_i<=box.imax; index_i++){
        for(int index_j=box.jmin; index_j<=box.jmax; index_j++){
            histogram[channel[index_i*width+index_j]]++;
        }
    }

    float sum = 0.0;
    for(int index=0; index<HISTOGRAM_NLEV; index++){
        sum += histogram[index];
	}


    return histogram;
}

float *histogram_dup(float *hist)
{
    return NULL;
}

void histogram_cumulate(float *hist)
{
    float sum=0.0;
    for(int i=0; i<HISTOGRAM_NLEV; i++){
        sum+=hist[i];
        hist[i]=sum;
    }
}

void histogram_normalize(float *hist)
{
    float sum = 0.0;
    for(int i=0; i<HISTOGRAM_NLEV; i++){
        sum+=hist[i];
    }
    for(int i=0; i<HISTOGRAM_NLEV; i++){
        hist[i] = hist[i]/(sum);
    }
}



