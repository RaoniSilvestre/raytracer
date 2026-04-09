
#include "object/sphere.hpp"
#include "math/vector_3.hpp"
#include <cmath>
#include <ios>
#include <iostream>

bool Sphere::intersect_p(const Ray &r) const {
  std::ios_base::sync_with_stdio(false);
  auto o_c = r.origem - center;
  auto d = r.direcao;
  float a = dot(d, d); // d . d
  float h = dot(o_c, d);//o-c dot d
  float c = dot(o_c, o_c); //o-c dot o-c
  float delta = (h * h - (a * c-radius*radius));

  // Delta negativo significa que não intersecta.
  if (delta < 0) {
    return false;
  }
  return true;
  float sqrt_delta = sqrt(delta);

  float t = (-h - sqrt_delta) / a;

  if (t <= 0) {
    t = (-h + sqrt_delta) / a;
    if (t <= 0) {
      return false;
    }
  }


  return true;
}
