#ifndef FRAGMENT
#define FRAGMENT

#include "color.h"

class Fragment {
 public:
  virtual void process(double x, double y, Color* color) = 0;
};

#endif
