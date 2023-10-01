#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include <imago2.h>

#include "mmip.h"
#include "strelm.h"

#include "MISSING_CODE.h"
//#include "SOLUTION.h"

static unsigned char*
L_diff(unsigned char *i1, unsigned char *i2, int size)
{
    unsigned char *result = malloc(size*sizeof(unsigned char));

    L_DIFF_MISSINGCODE

    return result;
}
				   

unsigned char *
mmip_disk_erosion(unsigned char *channel, int width, int height, int radius)
{
    unsigned char *result = malloc(width*height*sizeof(unsigned char));
    
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            result[i*width+j] = strelm_disk_getmin(channel, width, height, i, j, radius);
        }
    }

    return result;
}


unsigned char *
mmip_disk_dilation(unsigned char *channel, int width, int height, int radius)
{
    unsigned char *result = malloc(width*height*sizeof(unsigned char));

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            result[i*width+j] = strelm_disk_getmax(channel, width, height, i, j, radius);
        }
    }

    return result;
}

unsigned char *
mmip_disk_opening(unsigned char *channel, int width, int height, int radius)
{
    unsigned char *result = mmip_disk_erosion(channel, width, height, radius);

    return mmip_disk_dilation(result, width, height, radius);

}


unsigned char *
mmip_disk_closing(unsigned char *channel, int width, int height, int radius)
{
    unsigned char *result = mmip_disk_dilation(channel, width, height, radius);

    return mmip_disk_erosion(result, width, height, radius);
}

unsigned char *
mmip_disk_bgrad(unsigned char *channel, int width, int height, int radius)
{
    unsigned char *dilatation = mmip_disk_dilation(channel, width, height, radius);
    unsigned char *erosion = mmip_disk_erosion(channel, width, height, radius);

    unsigned char *result = malloc(width*height*sizeof(unsigned char));

    for(int i=0; i<(width*height); i++){
        result[i] = dilatation[i]-erosion[i];
        if(result[i] < 0){
            result[i] = 0;
        }
    }

    return result;
    
}


unsigned char *
mmip_disk_igrad(unsigned char *channel, int width, int height, int radius)
{
    unsigned char *result = mmip_disk_erosion(channel, width, height, radius);
    
    for(int i=0; i<(width*height); i++){
        result[i] = channel[i]-result[i];
        if(result[i] < 0){
            result[i] = 0;
        }
    }

    return result;

}


unsigned char *
mmip_disk_ograd(unsigned char *channel, int width, int height, int radius)
{
    unsigned char *result = mmip_disk_dilation(channel, width, height, radius);

    

    for(int i=0; i<(width*height); i++){
        
        unsigned char tmp = result[i] - channel[i];
        result[i] = tmp;
        if(result[i] < 0){
            result[i] = 0;
        }
    }
    
    return result;

}


        

    
