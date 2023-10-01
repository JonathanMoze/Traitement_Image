#include "convol1d.h"
#include <stdlib.h>


float *convol1d_swap_ij(float *channel, int width, int height)
{
    float *compl = (float*) malloc(sizeof(float) * (width * height));
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            compl[i*width + j] = channel[(j)*width + (i)];
        }
    }
    return compl;
}



float *convol1d_apply_3(float *channel, int width, int height, float kernel[3])
{
    float *compl = (float*) malloc(sizeof(float) * (width * height));
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(j==0 || j==(width-1)){
                compl[i*width+j] = channel[i*width+j];
            }else{
                compl[i*width+j] = ((kernel[2] * channel[i*width+j-1]) + (kernel[1] * channel[i*width+j]) + (kernel[0] * channel[i*width+j+1]));
            }    
        }
    }
    return compl;
}
