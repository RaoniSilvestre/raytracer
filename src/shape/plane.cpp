

#include "shape/plane.hpp"
#include "core/surfel.hpp"
#include <limits>
#include <optional>

std::optional<Surfel> Plane::intersect(const Ray &r) const {
  constexpr double EPSILON = 1e-8;

  double denom = dot(normal, r.direcao);

  if (std::abs(denom) < EPSILON) {
    return std::nullopt;
  }

  Vector3 p0l0 = point - r.origem;
  double t = dot(p0l0, normal) / denom;

  if (t > EPSILON) {
    Vector3 outg = r.direcao - 2.0 * dot(r.direcao, normal) * normal;

    Point3 hit_point = r(t);

    return Surfel(hit_point, normal, outg, t);
  }

  return std::nullopt;
}

Plane::Plane(const ParamSet &ps) {
  point = ps.retrieve<Point3>("point");
  normal = ps.retrieve<Vector3>("normal");
  constexpr double inf = std::numeric_limits<double>::infinity();
  bounds.lower_limit = {-inf, -inf, -inf};
  bounds.upper_limit = {inf, inf, inf};
}

Point3 Plane::get_center() const { return this->point; }
