#include "color.hpp"

class BackgroundColor {
private:
  Color bl;
  Color br;
  Color tl;
  Color tr;

  /// Return the linearly interpolated color in [A;B], based on the parameter
  /// \f$0\leq t \leq 1.\f$
  Color lerp(const Color &A, const Color &B, float t) const;

public:
  /// Ctro receives a list of four colors, for each corner.
  BackgroundColor(Color bl, Color br, Color tl, Color tr);
  /// Dtro
  ~BackgroundColor() {};
  /// Sample and returns a color, based on the raster coordinate.
  Color sampleUV(float u, float v) const;
};
