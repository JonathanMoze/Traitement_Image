#include "sed.h"
#include "colorimetric_data.h"
#include "xyz.h"

#include "MISSINGCODE.h"

/*
  Computing the normalization coefficient associated with a light source s
*/
float
xyz_get_k_from_s(float *s)
{
    float *S = sed_dup(s);
    sed_multiply_by(S, cie_y_bar);
    float k = 1/sed_sum(S);
    return k;
}


/* 
   Computing the CIE-XYZ coordinates of the DSE E. The normalisation
   coefficient K is calculated by reference to the DSE of a light
   source S (result of the function xyz_get_k_from_s). The result is
   stored as a three-number floating-point vector at the address given
   by the xyz parameter.
*/
void
xyz_from_sed(float *xyz, float *e, float k)
{
    float *X = sed_dup(e);
    float *Y = sed_dup(e);
    float *Z = sed_dup(e);
    sed_multiply_by(X, cie_x_bar);
    sed_multiply_by(Y, cie_y_bar);
    sed_multiply_by(Z, cie_z_bar);
    xyz[0] = k * sed_sum(X);
    xyz[1] = k * sed_sum(Y);
    xyz[2] = k * sed_sum(Z);
}


/*
  sRGB transform (REC-709 with D65)

  | r |   |  3.240479, -1.537150, -0.498535 |   | X |
  | g | = | -0.969256,  1.875992,  0.041556 | * | Y |
  | b |   |  0.055648, -0.204043,  1.057311 |   | Z |

*/

float
xyz_srgb_r(float cie_x, float cie_y, float cie_z)
{

  return cie_x*3.240479+cie_y*(-1.537150)+cie_z*(-0.498535);

}

float
xyz_srgb_g(float cie_x, float cie_y, float cie_z)
{

  return cie_x*(-0.969256)+cie_y*1.875992+cie_z*0.041556;

}

float
xyz_srgb_b(float cie_x, float cie_y, float cie_z)
{

  return cie_x*0.055648+cie_y*(-0.204043)+cie_z*1.057311;

}

