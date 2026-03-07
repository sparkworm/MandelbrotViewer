#include "image_data.h"
#include "lodepng.h"

int ImageData::set_pixel(unsigned row, unsigned col, Color color) {
  // ensure pixel is within picture
  if (row >= height || col >= width) return -1;
  data[row * width + col] = color;
  return 0;
}

Color* ImageData::get_pixel(unsigned row, unsigned col) {
  // invalid coordinates, return a black pixel
  if (row >= height || col >= width) return nullptr;
  return &data[row * width + col];
}

unsigned ImageData::encode_image(std::string image_name) {
  return lodepng::encode(image_name, reinterpret_cast<unsigned char*>(data.data()), width, height);
}
