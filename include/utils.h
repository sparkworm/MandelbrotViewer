// file for general purpose functions
#include <cmath>
#include "color.h"


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
