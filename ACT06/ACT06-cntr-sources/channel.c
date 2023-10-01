#include "channel.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

float *channel_to_float(unsigned char *channel, int size)
{
    float *compl = (float*) malloc(sizeof(float) * (size));
    for(int i=0; i<size; i++){
        compl[i] = (float)((int)channel[i]);        
    }
    return compl;
}

unsigned char *channel_to_uchar(float *fchannel, int size, enum channel_disp_mode mode)
{
    unsigned char *uchar = (unsigned char *)malloc(sizeof(unsigned char)*(size));
    for(int i=0; i<size; i++){
        double val = fchannel[i];
        if(mode == Cdm_normalize){
            val = (val/2)+127;
        } else if(mode == Cdm_absval){
            val = val < 0 ? -val : val;//fabs(val);

        }
        val = (val > 255) ? 255 : val; 
        uchar[i] = (unsigned char)val;
    }

    return uchar;

}