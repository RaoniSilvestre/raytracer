#pragma once

#include "core/param_set.hpp"
#include "math/vector_3.hpp"

class LookAt {
public:
  Vector3 look_from;
  Point3 look_at;
  Vector3 up;

  LookAt(Vector3 _look_from, Point3 _look_at, Vector3 _up) {
    look_from = _look_from;
    look_at = _look_at;
    up = _up;
  }

  LookAt(const ParamSet &ps);
};
