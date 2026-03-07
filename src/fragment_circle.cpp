#include <cmath>
#include "fragment_circle.h"


void FragmentCircle::process(double x, double y, Color* color) {
  // hardcoded because this is just for testing
  double delt_x = x - 0.5;
  double delt_y = y - 0.5;
  if (sqrt(delt_x * delt_x + delt_y * delt_y) < 0.25) {
    color->b = 255;
  }
  else color->b = 0;
}
