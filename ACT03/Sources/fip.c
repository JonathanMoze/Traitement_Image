#include "fip.h"


void fip_save_image_spectrum(double *spectrum, int width, int height, char *name, bool phase)
{
    double smax = spectrum[0];
    for(int i=1; i<(width*height); i++){
        smax = (spectrum[i] > smax)? spectrum[i]:smax;
    }

    unsigned char *uchar = (unsigned char *)malloc(sizeof(unsigned char)*(width*height));

    for(int i=0; i<(width*height); i++){
        double norm = (spectrum[i]/smax);
        if(phase){
            norm = (norm+1.0)/2;
        }
        double tmp = (pow(norm, 0.15)*255);
        
        uchar[i] = (unsigned char)tmp;        
    }


    img_save_pixels(name, uchar, width, height, IMG_FMT_GREY8);    

}

void fip_as_cut(double *spectrum, int width, int height, int min, int max, int mode)
{
    int centerX = width/2;
    int centerY = height/2;

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){

            double val = sqrt(pow(j-centerX,2)+pow(i-centerY,2));
            if(mode == 0){
                if(val < min || val > max){
                    spectrum[i*width+j] = 0;
                }
            } else {
                if(val >= min && val <= max){
                    spectrum[i*width+j] = 0;
                }
            }  
        }
    }
}

void fip_as_notch(double *spectrum, int width, int height, int u, int v, int r, float k)
{

}

