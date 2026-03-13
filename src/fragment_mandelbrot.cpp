#include "fragment_mandelbrot.h"

#include "utils.h"

void FragmentMandelbrot::process(double pixel_x, double pixel_y, Color* color) {
  //double x0 = (pixel_x + offset_x) / zoom * 2.47 - 2.0;
  //double y0 = (pixel_y - offset_y) / zoom * 2.24 - 1.12;
  double x0 = (pixel_x - 0.0) / zoom + offset_x;
  double y0 = (pixel_y - 0.5) / zoom + offset_y;

  double x = 0.0;
  double y = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  double w = 0.0;
  
  int i = 0;
  // optimised escape time algorithm
  while (x*x + y*y <= 4.0 && i < max_iterations) {
    x = x2 - y2 + x0;
    y = w - x2 - y2 + y0;
    x2 = x * x;
    y2 = y * y;
    w = (x + y) * (x + y);
    i++;
  }
  // either within fractal, or insufficient iterations to prove outside fractal: treat as inside
  if (i==max_iterations) {
    *color = Color(0,0,0,255);
  }
  // outside of fractal: use time until termination to ascribe a hue
  else *color = rgba_from_hsva((double)i/max_iterations, 1.0, 1.0, 1.0);
}
