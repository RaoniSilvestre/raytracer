#pragma once

#include "core/color.hpp"
#include "core/param_set.hpp"

class Scene;

class BackgroundColor {
private:
  Color bl, br, tl, tr;

  Color lerp(const Color &A, const Color &B, double t) const;

public:
  BackgroundColor(Color bl, Color br, Color tl, Color tr);
  ~BackgroundColor() = default;
  Color sampleUV(double u, double v) const;
  static void make_background(const ParamSet &ps, Scene &scene);
};
