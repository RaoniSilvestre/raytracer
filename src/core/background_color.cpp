#include "background_color.hpp"
#include "core/scene.hpp"

BackgroundColor::BackgroundColor(Color bl, Color br, Color tl, Color tr)
    : bl(bl), br(br), tl(tl), tr(tr) {}


Color BackgroundColor::lerp(const Color &a, const Color &b, double t) const {
  double red = Color::interpolate(a.red, b.red, t);
  double green = Color::interpolate(a.green, b.green, t);
  double blue = Color::interpolate(a.blue, b.blue, t);

  return Color{red, green, blue};
}

Color BackgroundColor::sampleUV(double u, double v) const {
  Color x_b = this->lerp(this->bl, this->br, u);
  Color x_t = this->lerp(this->tl, this->tr, u);

  return this->lerp(x_b, x_t, v);
}

void BackgroundColor::make_background(const ParamSet &ps, Scene &scene) {
  if (ps.has("color")) {
    Color c = ps.retrieve<Color>("color");
    scene.background = std::make_unique<BackgroundColor>(c, c, c, c);
    std::cout << ">>> Background Solid Color initialized." << std::endl;
  } else {
    Color bl = ps.retrieve<Color>("bl");
    Color tl = ps.retrieve<Color>("tl");
    Color tr = ps.retrieve<Color>("tr");
    Color br = ps.retrieve<Color>("br");

    scene.background = std::make_unique<BackgroundColor>(bl, br, tl, tr);
    std::cout << ">>> Background 4-Colors Interpolated initialized."
              << std::endl;
  }
}
