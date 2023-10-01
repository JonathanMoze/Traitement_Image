#include <stdio.h>
#include <assert.h>
#include <imago2.h>

int main( int argc, char *argv[])
{
    assert(argc == 3);

    char* input = argv[1];
    char* output = argv[2];

    int width, height;
    unsigned char* image = img_load_pixels(input, &width, &height, IMG_FMT_RGB24);
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            unsigned char* pix = image + (y*width+x)*(3*sizeof(char));
            char red = pix[0];
            char green = pix[1];
            char blue = pix[2];

            pix[0] = blue;
            pix[1] = red;
            pix[2] = green;

        }
    }

    img_save_pixels(output, image, width, height, IMG_FMT_RGB24);
    

    return 0;
}