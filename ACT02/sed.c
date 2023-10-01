#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sed.h"
#include "colorimetric_data.h"

#include "MISSINGCODE.h"

float *
sed_alloc(void)
{
    float *sed = calloc(SED_SIZE, sizeof(float));
    assert(sed != NULL);

    return sed;
}
    
void
sed_copy(float *dst, float *src)
{
    memcpy(dst, src, SED_SIZE * sizeof(float));
}

float *
sed_dup(float *sed)
{
    float *result = sed_alloc();

    sed_copy(result, sed);
    return result;
}

float
sed_sum(float *sed)
{
    float area = 0.0;
    int i;

    for (i = 0; i < SED_SIZE; i++)
	area += sed[i];

    return area * SED_LAMBDA_STEP;
}

void
sed_multiply_by(float *e, float *f)
{
    for (int i = 0; i < SED_SIZE; i++)
	e[i] = e[i] * f[i];
}

float *
sed_blackbody(int temperature)
{
    assert(temperature >= 0.0);
    float *result = sed_alloc();


    double c1 = 3.74150E29;
    double c2 = 1.4388E7;

    double multi = c2/(560.0*temperature);
    double expo = exp(multi);
    double aT = (pow(560.0, 5)*(expo-1))/c1;


    for(int i=0; i<SED_SIZE; i++){
        double lambda = SED_LAMBDA_MIN+i*SED_LAMBDA_STEP;
        result[i] = aT*(c1/(pow(lambda, 5)*(exp(c2/(lambda*temperature))-1)));
    }
    


    return result;
}

