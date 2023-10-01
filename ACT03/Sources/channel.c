#include <stdlib.h>
#include <math.h>
#include "fft.h"

unsigned char *channel_compose(char* rchan, char* gchan, char* bchan, size_t size)
{
    unsigned char* rgb = malloc(size*3*sizeof(unsigned char));
    for(int x=0; x<size; x++){
        int pixNb = x*sizeof(char);
        unsigned char valR = rchan[pixNb];
        unsigned char valG = gchan[pixNb];
        unsigned char valB = bchan[pixNb];

        pixNb*=3;
        rgb[pixNb] = valR;
        rgb[pixNb+1] = valG;
        rgb[pixNb+2] = valB;

    }


    return rgb;
}

char *channel_extract(char* pixels, int size, int channel_number)
{
    char* monochrome = malloc(size*sizeof(char));
    int index=0;
    for(int x=0; x<size; x++){
        unsigned char* pix = pixels + x*(3*sizeof(char));
        char val = pix[channel_number];
        

        monochrome[index] = val;
        index++;

    }


    return monochrome;
}

