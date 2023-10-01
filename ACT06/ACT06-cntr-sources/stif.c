#include "stif.h"
#include "histogram.h"
#include <math.h>
#include <stdio.h>


float stif_mean(unsigned char *channel, int size)
{
	float*f = histogram_make(channel, size);
	histogram_normalize(f);

	float mean = 0;
	for(int i=0; i<HISTOGRAM_NLEV; i++){
		mean += i*f[i];
	}
	return mean;
}

float stif_lmean(unsigned char *channel, int width, int height,
			int i, int j, int half_width)
{
	float*f = histogram_make_local(channel, width, height, i, j, half_width);
	histogram_normalize(f);
	

	float mean = 0.0;
	for(int index=0; index<HISTOGRAM_NLEV; index++){
		mean += index*f[index];
	}
	return mean;
}

float stif_variance(unsigned char *channel, int size)
{
	float mean = stif_mean(channel, size);
	float*f = histogram_make(channel, size);
	histogram_normalize(f);

	float variance=0.0;
	for(int i=0; i<HISTOGRAM_NLEV; i++){
		variance += f[i]* pow((i-mean), 2);
	}

	return variance;

}

float stif_lvariance(unsigned char *channel, int width, int height,
			    int i, int j, int half_width)
{
	float mean = stif_lmean(channel, width, height, i, j, half_width);
	float*f = histogram_make_local(channel, width, height, i, j, half_width);
	histogram_normalize(f);

	float variance=0.0;
	for(int index=0; index<HISTOGRAM_NLEV; index++){
		variance += f[index]* pow((index-mean), 2);
	}

	return variance;

}

float stif_entropy(unsigned char *channel, int size)
{
	float*f = histogram_make(channel, size);
	histogram_normalize(f);

	float entropy = 0.0;
	for(int i=0; i<HISTOGRAM_NLEV; i++){
		if(f[i] > 1e-6){
			entropy += f[i] * log2(f[i]);
		}
		
	}
	return -entropy;


}

float stif_lentropy(unsigned char *channel, int width, int height,
			   int i, int j, int half_width)
{
	float*f = histogram_make_local(channel, width, height, i, j, half_width);
	histogram_normalize(f);

	float entropy = 0.0;
	for(int index=0; index<HISTOGRAM_NLEV; index++){
		if(f[index] > 1e-6){
			entropy += f[index] * log2(f[index]);
		}
		
	}
	return -entropy;
}

int stif_median(unsigned char *channel, int size)
{
	float*f = histogram_make(channel, size);

	int sum = 0;
    for(int i=0; i<HISTOGRAM_NLEV; i++){
        sum+=  (int)f[i];
    }
	sum /= 2.0;

	int i=0;
	float sum_j = 0;
	do{
		sum_j=0;
		for(int j=0; j<=i; j++){
			sum_j += f[j];
		}
		i++;
	}while(sum_j<sum);
	return i-1;

}

int stif_lmedian(unsigned char *channel, int width, int height,
			int i, int j, int half_width)
{
	float*f = histogram_make_local(channel, width, height, i, j, half_width);

	int sum = 0;
    for(int i=0; i<HISTOGRAM_NLEV; i++){
        sum+=  (int)f[i];
    }
	sum /= 2.0;

	int index=0;
	float sum_j = 0;
	do{
		sum_j=0;
		for(int j=0; j<=index; j++){
			sum_j += f[j];
		}
		index++;
	}while(sum_j<sum);
	return index-1;
}


