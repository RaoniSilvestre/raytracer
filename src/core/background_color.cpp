#include "background_color.hpp"

BackgroundColor::BackgroundColor(Color bl, Color br, Color tl, Color tr)
    : bl(bl), br(br), tl(tl), tr(tr) {}

float interpolate(float a, float b, float t) { return a * (1.0f - t) + b * t; }

Color BackgroundColor::lerp(const Color &a, const Color &b, float t) const {
  float red = interpolate(a.red, b.red, t);
  float green = interpolate(a.green, b.green, t);
  float blue = interpolate(a.blue, b.blue, t);

  return Color{red, green, blue};
}

Color BackgroundColor::sampleUV(float u, float v) const {
  Color x_b = this->lerp(this->bl, this->br, u);
  Color x_t = this->lerp(this->tl, this->tr, u);

  return this->lerp(x_b, x_t, v);
}
