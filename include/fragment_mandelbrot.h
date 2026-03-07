#ifndef FRAGMENT_MANDELBROT
#define FRAGMENT_MANDELBROT

#include "fragment.h"
#include "color.h"

class FragmentMandelbrot : public Fragment {
 public:
  int max_iterations = 100;
  double offset_x = 0.0;
  double offset_y = 0.0;
  double zoom = 1.0;
  void process(double x, double y, Color* color) override;
};

#endif
