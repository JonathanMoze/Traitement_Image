#include "pderiv.h"
#include "convol1d.h"
#include "deriche.h"
#include <stdlib.h>

float *pderiv_d2_dj(float *channel, int width, int height){

    float kernel[3] = { 0.0, -1.0, 1.0 };

	float *ch = convol1d_apply_3(channel, height, width, kernel);
	
	return ch;
}

float *pderiv_d2_di(float *channel, int width, int height){

    float kernel[3] = { 0.0, -1.0, 1.0 };

	float *ch_1 = convol1d_swap_ij(channel, width, height);
	float *ch_2 = convol1d_apply_3(ch_1, height, width, kernel);
	float* f_result = convol1d_swap_ij(ch_2, height, width);
	free(ch_1);
	free(ch_2);
	return f_result;
}


float *pderiv_d3_dj(float *channel, int width, int height){
    float kernel[3] = { -1.0, 0, 1.0 };

	float *ch = convol1d_apply_3(channel, height, width, kernel);
	
	return ch;
}

float *pderiv_d3_di(float *channel, int width, int height){
    float kernel[3] = { -1.0, 0, 1.0 };
    float *ch_1 = convol1d_swap_ij(channel, width, height);
	float *ch_2 = convol1d_apply_3(ch_1, height, width, kernel);
	float* f_result = convol1d_swap_ij(ch_2, height, width);
	free(ch_1);
	free(ch_2);
	return f_result;
}


float *pderiv_prewitt_dj(float *channel, int width, int height){
    float kernelLissage[3] = { 1, 1, 1 };
    float kernel[3] = { -1.0, 0, 1.0 };
    float *ch_1 = convol1d_swap_ij(channel, width, height);
	float *ch_2 = convol1d_apply_3(ch_1, height, width, kernelLissage);
	float* ch_3 = convol1d_swap_ij(ch_2, height, width);
    float* f_result = convol1d_apply_3(ch_3, width, height, kernel);
	free(ch_1);
	free(ch_2);
    free(ch_3);
    return f_result;
}

float *pderiv_prewitt_di(float *channel, int width, int height){
    float kernelLissage[3] = { 1, 1, 1 };
    float kernel[3] = { -1.0, 0, 1.0 };
    float *ch_1 = convol1d_apply_3(channel, width, height, kernelLissage);
	float *ch_2 = convol1d_swap_ij(ch_1, width, height);
	float* ch_3 = convol1d_apply_3(ch_2, height, width, kernel);
    float* f_result = convol1d_swap_ij(ch_3, height, width);
	free(ch_1);
	free(ch_2);
    free(ch_3);
    return f_result;
}


float *pderiv_sobel_dj(float *channel, int width, int height){
    float kernelLissage[3] = { 1, 2, 1 };
    float kernel[3] = { -1.0, 0, 1.0 };
    float *ch_1 = convol1d_swap_ij(channel, width, height);
	float *ch_2 = convol1d_apply_3(ch_1, height, width, kernelLissage);
	float* ch_3 = convol1d_swap_ij(ch_2, height, width);
    float* f_result = convol1d_apply_3(ch_3, width, height, kernel);
	free(ch_1);
	free(ch_2);
    free(ch_3);
    return f_result;
}

float *pderiv_sobel_di(float *channel, int width, int height){
    float kernelLissage[3] = { 1, 2, 1 };
    float kernel[3] = { -1.0, 0, 1.0 };
    float *ch_1 = convol1d_apply_3(channel, width, height, kernelLissage);
	float *ch_2 = convol1d_swap_ij(ch_1, width, height);
	float* ch_3 = convol1d_apply_3(ch_2, height, width, kernel);
    float* f_result = convol1d_swap_ij(ch_3, height, width);
	free(ch_1);
	free(ch_2);
    free(ch_3);
    return f_result;
}


float *pderiv_deriche_di(float *channel, int width, int height, float alpha){
	float *ch_1 = deriche_apply_s(channel, width, height, alpha);
	float *ch_2 = convol1d_swap_ij(ch_1, width, height);
	float* ch_3 = deriche_apply_d(ch_2, width, height, alpha);
    float* f_result = convol1d_swap_ij(ch_3, height, width);
	free(ch_1);
	free(ch_2);
    free(ch_3);
    return f_result;
}


float *pderiv_deriche_dj(float *channel, int width, int height, float alpha){
	float *ch_1 = convol1d_swap_ij(channel, width, height);
	float *ch_2 = deriche_apply_s(ch_1, height, width, alpha);
	float* ch_3 = convol1d_swap_ij(ch_2, height, width);
    float* f_result = deriche_apply_d(ch_3, width, height, alpha);
	free(ch_1);
	free(ch_2);
    free(ch_3);
    return f_result;
}
