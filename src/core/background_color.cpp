#include "background_color.hpp"

BackgroundColor::BackgroundColor(Color bl, Color br, Color tl, Color tr)
    : bl(bl), br(br), tl(tl), tr(tr) {}

double interpolate(double a, double b, double t) { return a * (1.0f - t) + b * t; }

Color BackgroundColor::lerp(const Color &a, const Color &b, double t) const {
  double red = interpolate(a.red, b.red, t);
  double green = interpolate(a.green, b.green, t);
  double blue = interpolate(a.blue, b.blue, t);

  return Color{red, green, blue};
}

Color BackgroundColor::sampleUV(double u, double v) const {
  Color x_b = this->lerp(this->bl, this->br, u);
  Color x_t = this->lerp(this->tl, this->tr, u);

  return this->lerp(x_b, x_t, v);
}
