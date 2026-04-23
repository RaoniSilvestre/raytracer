
#include "shape/sphere.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"
#include <cmath>

bool Sphere::intersect_p(const Ray &r) const {
  Vector3 o_c = r.origem - center;
  Vector3 d = r.direcao;

  auto a = dot(d, d);
  auto half_b = dot(o_c, d);
  auto c = dot(o_c, o_c) - radius * radius;

  double discriminant = half_b * half_b - a * c;

  if (discriminant < 0) {
    return false;
  }

  double sqrtd = sqrt(discriminant);
  double t = (-half_b - sqrtd) / a;

  if (t < 0) {
    t = (-half_b + sqrtd) / a;
    if (t < 0) {
      return false;
    }
  }

  return true;
}

Sphere::Sphere(const ParamSet &ps) {
  auto r = ps.retrieve<double>("radius");
  auto c = ps.retrieve<Point3>("center");

  radius = r;
  center = c;
}
