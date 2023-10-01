#include "gradient.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int L_octant(float theta)
{
    const float pi = 3.141592653;
    
    if (theta < 0)
        theta += pi;
       
    if (theta >= 0.0 && theta < pi/8.0)
        return 1;

    if (theta >= pi/8.0 && theta < 3.0*pi/8.0)
        return 2;

    if (theta >= 3.0*pi/8.0 && theta < 5.0*pi/8.0)
        return 3;

    if (theta >= 5.0*pi/8.0 && theta < 7.0*pi/8.0)
        return 4;

    if (theta >= 7.0*pi/8.0 && theta < 9.0*pi/8.0)
        return 1;

    if (theta >= 9.0*pi/8.0 && theta < 11.0*pi/8.0)
        return 2;

    if (theta >= 11.0*pi/8.0 && theta < 13.0*pi/8.0)
       return 3;

    if (theta >= 13.0*pi/8.0 && theta < 15.0*pi/8.0)
        return 4;

    // theta in [15/8 * pi, 2 * pi]
        return 1;
}

/*float *gradient_norm_abs(float *di_channel, float *dj_channel, int size){

}*/

float *gradient_norm_eucl(float *di_channel, float *dj_channel, int size){
    float *channel = (float*) malloc(sizeof(float) * (size));
    for(int i=0; i<size; i++)
    {
        channel[i] = sqrt(pow(di_channel[i], 2) + pow(dj_channel[i], 2));
    }

    return channel;
}
/*
float *gradient_norm_max(float *di_channel, float *dj_channel, int size){

}*/

float *gradient_local_max(float *di_channel, float *dj_channel, int width, int height){

    float *channel = (float*) malloc(sizeof(float) * (width * height));
    for(int i=1; i<height-1; i++){
        for(int j=1; j<width-1 ; j++){
            float theta = atan2f(-di_channel[i*width+j], dj_channel[i*width+j]);
            int quadrant = L_octant(theta);

            float p_norm = sqrt(pow(di_channel[i*width+j], 2) + pow(dj_channel[i*width+j], 2));
            float p1_norm, p2_norm;
            switch(quadrant){
                case 1:
                    p1_norm = sqrt(pow(di_channel[i*width+j-1], 2) + pow(dj_channel[i*width+j-1], 2));
                    p2_norm = sqrt(pow(di_channel[i*width+j+1], 2) + pow(dj_channel[i*width+j+1], 2));
                    break;
                case 2:
                    p1_norm = sqrt(pow(di_channel[((i+1)*width) +j-1], 2) + pow(dj_channel[((i+1)*width) +j-1], 2));
                    p2_norm = sqrt(pow(di_channel[((i-1)*width) +j+1], 2) + pow(dj_channel[((i-1)*width) +j+1], 2));
                    break;
                case 3:
                    p1_norm = sqrt(pow(di_channel[((i+1)*width) +j], 2) + pow(dj_channel[((i+1)*width) +j], 2));
                    p2_norm = sqrt(pow(di_channel[((i-1)*width) +j], 2) + pow(dj_channel[((i-1)*width) +j], 2));
                    break;
                case 4:
                    p1_norm = sqrt(pow(di_channel[((i-1)*width) +j-1], 2) + pow(dj_channel[((i-1)*width) +j-1], 2));
                    p2_norm = sqrt(pow(di_channel[((i+1)*width) +j+1], 2) + pow(dj_channel[((i+1)*width) +j+1], 2));
                    break;
                default:
                    p1_norm = 0.0;
                    p2_norm = 0.0;
                    break;
            }
            if(p_norm > p1_norm && p_norm > p2_norm){
                channel[i*width+j] = p_norm;
            }else{
                channel[i*width+j] = 0.0;
            }
        }
    }

    return channel;
}
