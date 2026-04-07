#include "core/look_at.hpp"
#include "math/vector_3.hpp"

LookAt::LookAt(const ParamSet &ps) {
  Vector3 _look_at = ps.retrieve<Vector3>("look_at");
  Point3 _look_from = ps.retrieve<Point3>("look_from");
  Vector3 _up = ps.retrieve<Vector3>("up");

  look_at = _look_at;
  look_from = _look_from;
  up = _up;
}
