#include "hysteresis.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

static bool isPixelAround(unsigned char *result, int width, int height, int i, int j)
{
    for(int index_i = i-1; index_i <= i+1; index_i++){
        for(int index_j = j-1; index_j<= j+1; index_j++){
            if(index_i >= 0 && index_i < height && index_j >= 0 && index_j < width && index_i != i && index_j != j && result[index_i*width+index_j] != -1)
                return true;
        }
    }

    return false;
}

unsigned char *hysteresis_thr(unsigned char *channel, int width, int height, int th_low, int th_high)
{
    unsigned char *result = (unsigned char*) malloc(sizeof(unsigned char) * (width * height));
    bool *tag = (bool*) malloc(sizeof(bool) * (width * height));

    for(int i=1; i<height-1; i++){
        for(int j=1; j<width-1 ; j++){
            int pixVal = lround(channel[i*width+j]);
            if(pixVal >= th_high){
                result[i*width+j] = channel[i*width+j];
                tag[i*width+j] = true;
            }else{
                tag[i*width+j] = false;
            }
        }
    }

    bool modif = false;
    do{
        modif=false;
        for(int i=1; i<height-1; i++){
            for(int j=1; j<width-1 ; j++){
                int pixVal = lround(channel[i*width+j]);
                if (tag[i*width+j] == false)
                {
                   if(isPixelAround(result, width, height, i, j) && pixVal <= th_high && pixVal >= th_low){
                    result[i*width+j] = 255;
                    tag[i*width+j] = true;
                    modif = true;
                   }
                }
            }
        }
    } while(modif == true);

    for(int i=0; i<(width*height); i++){
        if(tag[i] == false)
            result[i] = 0;
    }

    free(tag);

    return result;

}

