#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ostream>

class Color {

private:
  static uint8_t map_to_255(float value) {
    float clamped = std::clamp(value, 0.0f, 255.0f);
    return static_cast<uint8_t>(std::lround(clamped));
  }

public:
  float red, green, blue;

  Color(float red, float green, float blue)
      : red(red), green(green), blue(blue) {}

  uint8_t red_int() const { return map_to_255(red); }
  uint8_t green_int() const { return map_to_255(green); }
  uint8_t blue_int() const { return map_to_255(blue); }
  friend std::ostream &operator<<(std::ostream &os, Color c) {
    os << static_cast<int>(c.red_int()) << " "
       << static_cast<int>(c.green_int()) << " "
       << static_cast<int>(c.blue_int()) << " ";
    return os;
  }
  bool operator==(const Color &other) const {
    const float epsilon = 0.001f;

    auto is_near = [epsilon](float a, float b) {
      return std::abs(a - b) < epsilon;
    };

    return is_near(red, other.red) && is_near(green, other.green) &&
           is_near(blue, other.blue);
  }

  static Color parseColorString(const char *color_str);
};
