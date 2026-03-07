/**
 * Represents an RGBA color
 */

#ifndef COLOR
#define COLOR

class Color {
 public:
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
  
  Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
    : r(red), g(green), b(blue), a(alpha) {};
  Color(unsigned char red, unsigned char green, unsigned char blue)
    : Color(red, green, blue, 255) {};
  // default color is opaque black
  Color()
    : Color(0, 0, 0, 255) {};
  
};

#endif
