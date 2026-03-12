#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include "utils.h"
#include "image_data.h"
#include "fragment_mandelbrot.h"

std::string generate_name(FragmentMandelbrot& mb_frag, int supersampling) {
  std::stringstream ss;
  ss << "x:" << mb_frag.offset_x << "_y:" << mb_frag.offset_y << "_z:" << mb_frag.zoom << "_i:"
			      << mb_frag.max_iterations << "_ss:" << supersampling;
  return ss.str();
}

void get_input(std::string& input) {
  std::cout << "\nEnter one of the following keys to take an action:   \n"
	    << "\ti - set max iterations\n"
	    << "\to - set offset\n"
	    << "\tz - set zoom\n"
	    << "\ts - set supersampling\n"
	    << "\tv - view current settings\n"
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

void change_supersampling(int& supersampling) {
  std::cout << "Set super sampling (integer one default, large performance impact): ";
  std::cin >> supersampling;
}

void display_settings(FragmentMandelbrot& mb_frag, int supersampling) {
  std::cout << "Max iterations: " << mb_frag.max_iterations
	    << "\nX offset: " << mb_frag.offset_x
	    << "\nY offset: " << mb_frag.offset_y
	    << "\nZoom: " << mb_frag.zoom
	    << "\nSupersampling: " << supersampling << std::endl;
}

void reset_settings(FragmentMandelbrot& mb_frag, int& supersampling) {
  std::cout << "Resetting to defaults..." << std::endl;
  mb_frag.max_iterations = FragmentMandelbrot::DEFAULT_MAX_ITERATIONS;
  mb_frag.offset_x = FragmentMandelbrot::DEFAULT_OFFSET_X;
  mb_frag.offset_y = FragmentMandelbrot::DEFAULT_OFFSET_Y;
  mb_frag.zoom = FragmentMandelbrot::DEFAULT_ZOOM;
  supersampling = 1;
}

void generate_image(ImageData& image, FragmentMandelbrot& mb_frag, int supersampling) {
  // auto generated names will cause the file to be overwritten, but with an identical image
  std::cout << "Enter a name for the output file, or leave blank for auto-gen (.png will be appended): ";
  std::string name;
  std::getline(std::cin, name);
  if (name == "") {
    name = generate_name(mb_frag, supersampling);
  }
  name += ".png";
  // start timer
  auto start = std::chrono::high_resolution_clock::now();
  if (supersampling == 1) {
    for (unsigned r=0; r<image.height; ++r) {
      for (unsigned c=0; c<image.width; ++c) {
	mb_frag.process(double(c) / image.width, double(r) / image.height, image.get_pixel(r, c));
      }
    }
  }
  else {
    ImageData large_image(image.width * supersampling, image.height * supersampling);
    for (unsigned r=0; r<large_image.height; ++r) {
      for (unsigned c=0; c<large_image.width; ++c) {
	mb_frag.process(double(c) / large_image.width, double(r) / large_image.height,
			large_image.get_pixel(r, c));
      }
    }
    // downscale
    downscale_image(large_image, image);
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
  // the number of pixels in either direction that will form a single pixel on the output image
  int supersampling = 1;
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
      change_supersampling(supersampling);
    }
    else if (input == "v") {
      display_settings(mb_frag, supersampling);
    }
    else if (input == "r") {
      reset_settings(mb_frag, supersampling);
    }
    else if (input == "g") {
      generate_image(image, mb_frag, supersampling);
    }
    else if (input == "q") {
      break;
    }
    else {
      std::cout << "unrecognized input: " << input << std::endl;
    }
  }	 
}

