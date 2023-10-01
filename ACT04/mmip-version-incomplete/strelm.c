#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include <imago2.h>

#include "strelm.h"

#include "MISSING_CODE.h"
//#include "SOLUTION.h"

/* Bounding box */
static int i_min;
static int i_max;
static int j_min;
static int j_max;

static void
L_set_bbox_square(int width, int height, int ip, int jp, int radius)
{
    assert(radius >= 0);

    i_min = ip - radius;
    if(i_min < 0)
        i_min = 0;
    j_min = jp - radius;
    if(j_min < 0)
        j_min = 0;
    i_max = ip + radius;
    if(i_max >= height)
        i_max = (height-1);
    j_max = jp + radius;
    if(j_max >= width)
        j_max = (width-1);
}

static void
L_set_bbox_rectangle(int width, int height, int ip, int jp, int radius, int mode)
{
    assert(radius >= 0);

    if(mode ==0){// VER
        i_min = ip - radius;
        if(i_min < 0)
            i_min = 0;
        i_max = ip + radius;
        if(i_max >= height)
            i_max = (height-1);
        j_min = jp;
        j_max = jp;

    }else{// HOR
        j_min = jp - radius;
        if(j_min < 0)
            j_min = 0;
        j_max = jp + radius;
        if(j_max >= width)
            j_max = (width-1);
        i_min = ip;
        i_max = ip;
    }
}

static bool
L_is_inside_disk(int ip, int jp, int radius, int i, int j)
{
   double dist = pow((i-ip), 2) + pow((j-jp), 2);
   return (dist <= pow(radius, 2));
}

static bool
L_is_inside_rect(int ip, int jp, int radius, int mode, int i, int j)
{
    if(mode == 0){// VER
        return (j == jp) &&  i<=(ip+radius) && i>=(ip-radius);
    }else{
        return (i == ip) &&  j<=(jp+radius) && j>=(jp-radius);
    }
}

unsigned char
strelm_disk_getmin(unsigned char *channel, int width, int height, int ip, int jp, int radius)
{
    L_set_bbox_square(width, height, ip, jp, radius);

    unsigned char min = 255;
    for(int j=j_min; j<=j_max; j++){
        for(int i=i_min; i<=i_max; i++){
            if(L_is_inside_disk(ip, jp, radius, i, j) && channel[i*width+j] <= min){
                min = channel[i*width+j];
            }
        }
    }

    return min;
}

unsigned char
strelm_disk_getmax(unsigned char *channel, int width, int height, int ip, int jp, int radius)
{
    L_set_bbox_square(width, height, ip, jp, radius);
    unsigned char max = 0;
    for(int i=i_min; i<=i_max; i++){
        for(int j=j_min; j<=j_max; j++){
            if(L_is_inside_disk(ip, jp, radius, i, j) && channel[i*width+j] >= max){
                max = channel[i*width+j];
            }
        }
    }

    return max;
}

unsigned char
strelm_rect_getmin(unsigned char *channel, int width, int height, int ip, int jp, int radius, int mode)
{
    L_set_bbox_rectangle(width, height, ip, jp, radius, mode);

    unsigned char min = 255;
    for(int j=j_min; j<=j_max; j++){
        for(int i=i_min; i<=i_max; i++){
            if(L_is_inside_rect(ip, jp, radius, mode, i, j) && channel[i*width+j] <= min){
                min = channel[i*width+j];
            }
        }
    }

    return min;
}

unsigned char
strelm_rect_getmax(unsigned char *channel, int width, int height, int ip, int jp, int radius, int mode)
{
    L_set_bbox_rectangle(width, height, ip, jp, radius, mode);
    unsigned char max = 0;
    for(int i=i_min; i<=i_max; i++){
        for(int j=j_min; j<=j_max; j++){
            if(L_is_inside_rect(ip, jp, radius, mode, i, j) && channel[i*width+j] >= max){
                max = channel[i*width+j];
            }
        }
    }

    return max;
}

    
