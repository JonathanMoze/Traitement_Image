#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <imago2.h>

char *channel_compose(char* rchan, char* gchan, char* bchan, size_t size)
{
    char* rgb = malloc(size*3*sizeof(char));
    for(int x=0; x<size; x++){
        int pixNb = x*sizeof(char);
        char valR = rchan[pixNb];
        char valG = gchan[pixNb];
        char valB = bchan[pixNb];

        pixNb*=3;
        rgb[pixNb] = valR;
        rgb[pixNb+1] = valG;
        rgb[pixNb+2] = valB;

    }


    return rgb;
}



int main( int argc, char *argv[])
{
    assert(argc == 5);

    char* inputR = argv[1];
    char* inputG = argv[2];
    char* inputB = argv[3];
    char* output = argv[4];

    int width, height;
    unsigned char* imageR = img_load_pixels(inputR, &width, &height, IMG_FMT_GREY8);
    unsigned char* imageG = img_load_pixels(inputG, &width, &height, IMG_FMT_GREY8);
    unsigned char* imageB = img_load_pixels(inputB, &width, &height, IMG_FMT_GREY8);

    unsigned char* rgb = channel_compose(imageR, imageG, imageB, width*height);

    img_save_pixels(output, rgb, width, height, IMG_FMT_RGB24);

    free(rgb);
    
    return 0;
}