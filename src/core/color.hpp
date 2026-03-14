#include <algorithm>
#include <cmath>

class Color {

private:
  static int map_to_255(float value) {
    float clamped = std::clamp(value, 0.0f, 255.0f);
    return static_cast<int>(std::lround(clamped));
  }

public:
  float red, green, blue;

  Color(float red, float green, float blue)
      : red(red), green(green), blue(blue) {}

  int red_int() const { return map_to_255(red); }
  int green_int() const { return map_to_255(green); }
  int blue_int() const { return map_to_255(blue); }

  bool operator==(const Color &other) const {
    const float epsilon = 0.001f;

    auto is_near = [epsilon](float a, float b) {
      return std::abs(a - b) < epsilon;
    };

    return is_near(red, other.red) && is_near(green, other.green) &&
           is_near(blue, other.blue);
  }
};
