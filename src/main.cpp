#include <iostream>
#include "image_data.h"
#include "fragment_circle.h"
#include "fragment_mandelbrot.h"
// only for test function
#include <cmath>

// can be called for every pixel with a pointer to the color of that pixel.
void fragment(double x, double y, Color* color) {
  // test logic for creating a circle
  double center_x = 0.5;
  double center_y = 0.5;
  double delt_x = center_x - x;
  double delt_y = center_y - y;
  if (sqrt(delt_x*delt_x + delt_y*delt_y) < 0.25) {
    color->r = 255;
  }
  else color->r = 0;
}

int main() {
  std::cout << "creating simple rectangle" << std::endl;
  ImageData rectangle(256, 256);
  std::cout << rectangle.encode_image("test_rect.png") << std::endl;

  std::cout << "creating a circle with fragment method" << std::endl;
  ImageData circle(256, 256);
  for (unsigned r=0; r<circle.height; ++r) {
    for (unsigned c=0; c<circle.width; ++c) {
      fragment(double(c) / circle.width, double(r) / circle.height, circle.get_pixel(r, c));
    }
  }
  std::cout << circle.encode_image("test_circle.png") << std::endl;

  std::cout << "creating a circle with abstract fragment method" << std::endl;
  ImageData circle2(256, 256);
  FragmentCircle circ_frag;
  for (unsigned r=0; r<circle.height; ++r) {
    for (unsigned c=0; c<circle.width; ++c) {
      circ_frag.process(double(c) / circle2.width, double(r) / circle2.height, circle2.get_pixel(r, c));
    }
  }
  std::cout << circle2.encode_image("test_circle2.png") << std::endl;

  std::cout << "test mandelbrot" << std::endl;
  ImageData mb(512, 512);
  FragmentMandelbrot mb_frag;
  for (unsigned r=0; r<mb.height; ++r) {
    for (unsigned c=0; c<mb.width; ++c) {
      mb_frag.process(double(c) / mb.width, double(r) / mb.height, mb.get_pixel(r, c));
    }
  }
  std::cout << mb.encode_image("test_mandelbrot.png") << std::endl;
}

