// file for general purpose functions
#include <cmath>
#include "image_data.h"
#include "color.h"

#ifndef UTILS
#define UTILS

// full_image's dimensions must be an integer multiple of target's
void downscale_image(ImageData& full_image, ImageData& target);

Color rgba_from_hsva(double h, double s, double v, double a);

#endif
