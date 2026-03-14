#include <cstdint>

class Color {
public:
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  Color(uint8_t red, uint8_t green, uint8_t blue)
      : red(red), green(green), blue(blue) {}
};
