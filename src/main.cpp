#include "core/app.hpp"
#include "core/background_color.hpp"
#include <iostream>
#include <ostream>

int main() {
  Color black = {0, 0, 0};
  Color white = {255, 255, 255};
  Color red = {255, 0, 0};
  Color blue = {0, 0, 255};

  BackgroundColor bg{black, red, white, blue};

  int width = 400;
  int height = 200;

  std::cout << "P3\n" << width << " " << height << "\n255\n";

  for (int j = height - 1; j >= 0; --j) {
    float v = static_cast<float>(j) / static_cast<float>(height - 1);
    for (int i = 0; i < width; ++i) {
      float u = static_cast<float>(i) / static_cast<float>(width - 1);

      Color color = bg.sampleUV(u, v);

      std::cout << color.red_int() << " " << color.green_int() << " "
                << color.blue_int() << "\n";
    }
  }

  return 0;
}
