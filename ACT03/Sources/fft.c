#include <stdlib.h>
#include <math.h>
#include "fft.h"


static fftw_complex *conv_uchar_to_complex(unsigned char *channel, int width, int height)
{
    fftw_complex *compl = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width*height));
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            double tmp = (double)((int)channel[i*width+j]);
            tmp = pow((-1), i+j)*tmp*(1.0/(width*height));
            compl[i*width+j] = (fftw_complex)tmp;
            
        }
    }
    
    return compl;
}
static unsigned char *conv_complex_to_uchar(fftw_complex *c_channel, int width, int height)
{
    unsigned char *uchar = (unsigned char *)malloc(sizeof(unsigned char)*(width*height));
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            double tmp = creal(c_channel[i*width+j]);
            tmp = pow(-1, (i+j))*tmp;
            tmp = tmp < 0 ? 0 : tmp;
            tmp = tmp > 255 ? 255 : tmp;
            uchar[i*width+j] = (unsigned char)tmp;
        }
    }

    return uchar;
}

fftw_complex *fft_forward(unsigned char *chan, int width, int height)
{
    fftw_complex *in = conv_uchar_to_complex(chan, width, height);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width*height));
    fftw_plan plan =  fftw_plan_dft_2d(height, width, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    return out;
}

unsigned char *fft_backward(fftw_complex *fr_chan, int width, int height)
{
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width*height));
    fftw_plan plan =  fftw_plan_dft_2d(height, width, fr_chan, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    return conv_complex_to_uchar(out, width, height);
}


double *fft_extract_as(fftw_complex *fr_chan, int width, int height)
{
    double *tabOut = (double *)malloc(sizeof(double)*(width*height));
    for(int i=0; i<(width*height); i++)
    {
        //tabOut[i] = sqrt(pow(creal(fr_chan[i]), 2) + pow(cimag(fr_chan[i]), 2));
        tabOut[i] = cabs(fr_chan[i]);
    }

    return tabOut;
}

double *fft_extract_ps(fftw_complex *fr_chan, int width, int height)
{
    double *tabOut = (double *)malloc(sizeof(double)*(width*height));
    for(int i=0; i<(width*height); i++)
    {
        //tabOut[i] = atan2(cimag(fr_chan[i]), creal(fr_chan[i]));
        tabOut[i] = carg(fr_chan[i]);
    }

    return tabOut;
}

fftw_complex *fft_compose_aps(double *as, double *ps, int width, int height)
{
    fftw_complex *compl = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width*height));
    for(int i=0; i<(width*height); i++){
        compl[i] = (as[i]*cos(ps[i])) + (I*as[i])*sin(ps[i]);
    }

    return compl;
}