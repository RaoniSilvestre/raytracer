#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ostream>

class Color {

private:
  static uint8_t map_to_255(double value) {
    return static_cast<uint8_t>(std::lround(std::clamp(value, 0., 1.) * 255.));
  }

public:
  double red, green, blue;
  Color() = default;
  Color(double red, double green, double blue)
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
    const double epsilon = 0.001f;

    auto is_near = [epsilon](double a, double b) {
      return std::abs(a - b) < epsilon;
    };

    return is_near(red, other.red) && is_near(green, other.green) &&
           is_near(blue, other.blue);
  }
  Color operator+(const Color &r) const {
    return {this->red + r.red, this->green + r.green, this->blue + r.blue};
  }
  Color operator*(const Color &r) const {
    return {this->red * r.red, this->green * r.green, this->blue * r.blue};
  }
  Color operator*(double r) const {
    return {this->red * r, this->green * r, this->blue * r};
  }
  // friend Color operator*(double lhs, const Color &rhs) {
  //   return {rhs.red * lhs, rhs.green * lhs, rhs.blue * lhs};
  // }
  static double interpolate(const double a, const double b, double t);
  static Color interpolate(const Color &a, const Color &b, const double t);
  static Color parseColorString(const char *color_str);
};
