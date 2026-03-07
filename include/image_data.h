/**
 * Provides an intermediary for adjusting color values for an individual pixel.
 */


#ifndef IMAGE_DATA
#define IMAGE_DATA

#include <vector>
#include <string>
#include "color.h"

class ImageData {
 public:
  const unsigned width;
  const unsigned height;
  // initializes to all white, all opaque
  ImageData(unsigned w, unsigned h)
    : width(w), height(h), data(w * h * 4, Color()) {};
  //~ImageData();
  // sets the pixel at the given x and y to the specified color
  int set_pixel(unsigned row, unsigned col, Color color);
  // fetches color data and constructs a Color object to return
  Color* get_pixel(unsigned row, unsigned col);
  unsigned encode_image(std::string image_name);
private:
  // something something encapsulation
  std::vector<Color> data;
};

#endif
