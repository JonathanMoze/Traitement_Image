#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <imago2.h>

#include "histogram.h"
#include "stif.h"

static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s IMAGE\n"
	    "    Compute and display statistical features\n"
	    , s);
    exit(EXIT_FAILURE);
}

static struct img_pixmap *
img_pixmap_read(char *file_name)
{
    struct img_pixmap *img = img_create();

    if (img_load(img, file_name) == -1)
    {
	fprintf(stderr, "Cannot load \"%s\" image\n", file_name);
	exit(EXIT_FAILURE);
    }
    if (img_is_float(img) || img_has_alpha(img) || !img_is_greyscale(img))
    {
	fprintf(stderr, "Sorry, only grey levels 8 bits images\n");
	exit(EXIT_FAILURE);
    }

    return img;
}


int 
main(int argc, char *argv[])
{
    if (argc != 5)
	    usage(argv[0]);
    
    int i,j,half_width;
    i = atoi(argv[1]);
    j = atoi(argv[2]);
    half_width = atoi(argv[3]);
    struct img_pixmap *img = img_pixmap_read(argv[4]);

    unsigned char *channel = (unsigned char *) img->pixels;
    int width = img->width;
    int height = img->height;

    float mu = stif_lmean(channel, width, height, i, j, half_width);
    int med = stif_lmedian(channel, width, height, i, j, half_width);
    float sdv = sqrt(stif_lvariance(channel, width, height, i, j, half_width));
    float entr = stif_lentropy(channel, width, height, i, j, half_width);
		     

    printf("mean    : %5.1f (%5.3f)\n"
	   "median  : %5d (%5.3f)\n"
	   "std dev : %5.1f (%5.3f)\n"
	   "entropy : %5.1f\n",
	   mu, mu/(HISTOGRAM_NLEV - 1),
	   med, (float) med/(HISTOGRAM_NLEV - 1),
	   sdv, sdv/(HISTOGRAM_NLEV - 1),
	   entr);

    img_free(img);
    
    exit(EXIT_SUCCESS);
}
