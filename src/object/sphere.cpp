
#include "object/sphere.hpp"
#include "math/vector_3.hpp"
#include <cmath>

bool Sphere::intersect_p(const Ray &r) const {
  auto o_c = r.origem - center;
  auto d = r.direcao;

  float a = dot(d, d); // d . d
  float h = dot(o_c, d);
  float c = dot(o_c, o_c) - radius * radius;

  float delta = h * h - a * c;

  // Delta negativo significa que não intersecta.
  if (delta < 0) {
    return false;
  }

  float sqrt_delta = sqrt(delta);

  float t = (-h - sqrt_delta) / a;

  if (t < r.start || t > r.end) {
    t = (-h + sqrt_delta) / a;
    if (t < r.start || t > r.end) {
      return false;
    }
  }

  return true;

  return true;
}
