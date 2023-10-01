#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <imago2.h>
#include <math.h>

double f(double x, double A){
    return A*x+((2*(1-A)*pow(x,2))/(1+pow(x,2)));
}

int main( int argc, char *argv[])
{
    assert(argc == 8);

    

    int width = atoi(argv[1]);
    double A = atof(argv[2]);
    double B = atof(argv[3]);
    double X0 = atof(argv[4]);
    double Y0 = atof(argv[5]);
    int N = atoi(argv[6]);
    char* output = argv[7];

    struct img_pixmap *img = img_create();
    char* pix;
    int test = img_set_pixels(img, width, width, IMG_FMT_RGBA32, pix);
    assert(test != -1);

    double x = X0;
    double y = Y0;
    double xMax = abs(x);
    double yMax = abs(y);

    for(int n=0; n < N; n++){
        double x_tmp = B*y + f(x,A);
        double fcalc = f(x_tmp,A);
        printf("%d", fcalc);
        
        

    }

    return 0;
}