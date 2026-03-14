#include "background_color.hpp"
#include <cmath>
#include <cstdint>

uint8_t interpolate(uint8_t a, uint8_t b, float t) {
  float a_ = static_cast<float>(a) * (1 - t);
  float b_ = static_cast<float>(b) * t;
  float val = a_ - b_;
  return static_cast<uint8_t>(std::round(val));
}

Color BackgroundColor::lerp(const Color &a, const Color &b, float t) const {
  uint8_t red = interpolate(a.red, b.red, t);
  uint8_t green = interpolate(a.green, b.green, t);
  uint8_t blue = interpolate(a.blue, b.blue, t);

  return Color{red, green, blue};
}

Color BackgroundColor::sampleUV(float u, float v) const {
  Color x_b = this->lerp(this->bl, this->br, u);
  Color x_t = this->lerp(this->tl, this->tr, u);

  return this->lerp(x_b, x_t, v);
}
