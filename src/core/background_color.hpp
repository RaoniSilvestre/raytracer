#pragma once

#include "color.hpp"

class BackgroundColor {
private:
  Color bl, br, tl, tr;

  Color lerp(const Color &A, const Color &B, float t) const;

public:
  BackgroundColor(Color bl, Color br, Color tl, Color tr);
  ~BackgroundColor() = default;
  Color sampleUV(float u, float v) const;
};
