#ifndef FRAGMENT_MANDELBROT
#define FRAGMENT_MANDELBROT

#include "fragment.h"
#include "color.h"

class FragmentMandelbrot : public Fragment {
 public:
  static constexpr int DEFAULT_MAX_ITERATIONS = 100;
  static constexpr double DEFAULT_OFFSET_X = -0.6;
  static constexpr double DEFAULT_OFFSET_Y = 0.0;
  static constexpr double DEFAULT_ZOOM = .4;
  int max_iterations = 100;
  double offset_x = 0.0;
  double offset_y = 0.0;
  double zoom = 1.0;
  FragmentMandelbrot(int it, double off_x, double off_y, double z)
    : max_iterations(it), offset_x(off_x), offset_y(off_y), zoom(z) {};
  FragmentMandelbrot()
    : max_iterations(DEFAULT_MAX_ITERATIONS), offset_x(DEFAULT_OFFSET_X), offset_y(DEFAULT_OFFSET_Y),
      zoom(DEFAULT_ZOOM) {};
  void process(double x, double y, Color* color) override;
};

#endif
