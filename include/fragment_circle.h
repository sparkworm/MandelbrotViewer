#ifndef FRAGMENT_CIRCLE
#define FRAGMENT_CIRCLE

#include "fragment.h"

class FragmentCircle : public Fragment {
 public:
  void process(double x, double y, Color* color) override;
};

#endif
