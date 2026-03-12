#include "utils.h"

void downscale_image(ImageData& full_image, ImageData& target) {
  unsigned x_scale = full_image.width / target.width;
  unsigned y_scale = full_image.height / target.height;
  // number of pixels of full_image used to calculate a single pixel in target
  unsigned p_ratio = x_scale * y_scale;
  // check for invalid dimensions
  if (x_scale * target.width != full_image.width || y_scale * target.height != full_image.height) {
    return;
  }
  for (unsigned tr=0; tr<target.height; ++tr) {
    for (unsigned tc=0; tc<target.width; ++tc) {
      unsigned r_sum = 0;
      unsigned g_sum = 0;
      unsigned b_sum = 0;
      unsigned a_sum = 0;
      for (unsigned fr=tr*y_scale; fr<tr*y_scale+y_scale; ++fr) {
	for (unsigned fc=tc*x_scale; fc<tc*x_scale+x_scale; ++fc) {
	  Color c = *full_image.get_pixel(fr, fc);
	  r_sum += c.r;
	  g_sum += c.g;
	  b_sum += c.b;
	  a_sum += c.a;
	}
      }
      Color new_color = Color((unsigned char)(r_sum/p_ratio), (unsigned char)(g_sum/p_ratio),
			      (unsigned char)(b_sum/p_ratio), (unsigned char)(a_sum/p_ratio));
      target.set_pixel(tr, tc, new_color);
    }
  }
}


// code adapted from MrBubu,
// based on https://stackoverflow.com/questions/51203917/math-behind-hsv-to-rgb-conversion-of-colors
// performs calculations with color channels on a scale of 0.0 to 1.0, then converts to unsigned char at end
Color rgba_from_hsva(double h, double s, double v, double a) {
  float r;
  float g;
  float b;

  float i = floor(h*6.0);
  float f = h*6.0 -i;
  float p = v*(1.0-s);
  float q = v*(1.0-f*s);
  float t = v* (1.0-(1.0-f)*s);

  int cond = int(i)%6;

  if (cond == 0){
    r = v; g = t; b = p;
  }
  else if (cond == 1){
    r = q; g = v; b = p;
  }
  else if (cond == 2){
    r = p; g = v; b = t;
  }
  else if (cond == 3){
    r = p; g = q; b = v;
  }
  else if (cond == 4){
    r = t; g = p; b = v;
  }
  else if (cond == 5){
    r = v; g = p; b = q;
  }
  else {
    // THIS SHOULD NEVER HAPPEN
    r = 0.0; g = 0.0; b = 0.0;
  }
  return Color(r*255,g*255,b*255,a*255);
}
