#include <iostream>
#include <string>
#include <chrono>
#include "image_data.h"
#include "fragment_mandelbrot.h"

void get_input(std::string& input) {
  std::cout << "\nEnter one of the following keys to take an action:   \n"
      << "\ti - set max iterations\n"
      << "\to - set offset\n"
      << "\tz - set zoom\n"
      << "\ts - view current settings\n"
      << "\tr - reset to default values\n"
      << "\tg - generate image with current settings\n"
      << "\tq - quit\n"
      << ">>";
    std::cin >> input;
}

void change_iterations(FragmentMandelbrot& mb_frag) {
  std::cout << "Set max iterations (will have a large performance impact): ";
  int it;
  std::cin >> it;
  mb_frag.max_iterations = it;
  std::cout << "max_iterations set to " << it << std::endl;
}

void change_offset(FragmentMandelbrot& mb_frag) {
  std::cout << "X offset: ";
  double x_off;
  std::cin >> x_off;
  mb_frag.offset_x = x_off;
  std::cout << "Y offset: ";
  double y_off;
  std::cin >> y_off;
  mb_frag.offset_y = y_off;
  std::cout << "Offset set to " << x_off << ", " << y_off << std::endl;
}

void change_zoom(FragmentMandelbrot& mb_frag) {
  std::cout << "Set zoom level (1.0 default, higher numbers are 'zoomed-in': ";
  double zoom;
  std::cin >> zoom;
  mb_frag.zoom = zoom;
  std::cout << "Zoom set to " << zoom << std::endl;
}

void display_settings(FragmentMandelbrot& mb_frag) {
  std::cout << "Max iterations: " << mb_frag.max_iterations
	    << "\nX offset: " << mb_frag.offset_x
	    << "\nY offset: " << mb_frag.offset_y
	    << "\nZoom: " << mb_frag.zoom << std::endl;
}

void reset_settings(FragmentMandelbrot& mb_frag) {
  std::cout << "Resetting to defaults..." << std::endl;
  mb_frag.max_iterations = FragmentMandelbrot::DEFAULT_MAX_ITERATIONS;
  mb_frag.offset_x = FragmentMandelbrot::DEFAULT_OFFSET_X;
  mb_frag.offset_y = FragmentMandelbrot::DEFAULT_OFFSET_Y;
  mb_frag.zoom = FragmentMandelbrot::DEFAULT_ZOOM;
}

void generate_image(ImageData& image, FragmentMandelbrot& mb_frag) {
  std::cout << "Enter a name for the output file (.png will be appended): ";
  std::string name;
  std::cin >> name;
  name += ".png";
  // start timer
  auto start = std::chrono::high_resolution_clock::now();
  for (unsigned r=0; r<image.height; ++r) {
    for (unsigned c=0; c<image.width; ++c) {
      mb_frag.process(double(c) / image.width, double(r) / image.height, image.get_pixel(r, c));
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
      
  int res = image.encode_image(name);
  if (res == 0) {
    std::cout << "Image " << name << " created successfully in " << duration.count()/1000.0 << " seconds"
	      << std::endl;
  }
  else std::cout << "Error " << res << " in creating image" << std::endl;
}

int main() {
  std::cout << "Select resolution side length (will be square): ";
  int res;
  std::cin >> res;
  // create image data of specified size
  ImageData image(res, res);
  FragmentMandelbrot mb_frag;
  while (1) {
    std::string input;
    get_input(input);
    if (input == "i") {
      change_iterations(mb_frag);
    }
    else if (input == "o") {
      change_offset(mb_frag);
    }
    else if (input == "z") {
      change_zoom(mb_frag);
    }
    else if (input == "s") {
      display_settings(mb_frag);
    }
    else if (input == "r") {
      reset_settings(mb_frag);
    }
    else if (input == "g") {
      generate_image(image, mb_frag);
    }
    else if (input == "q") {
      break;
    }
    else {
      std::cout << "unrecognized input: " << input << std::endl;
    }
  }	 
}

