#pragma once
#include "core/light.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"

class PointLight : public Light {
public:
  PointLight(const ParamSet &ps);
  Color sample_li(const Surfel &s, Vector3 &dir /*, VisibilityTester v*/);

private:
  Point3 from;
  Vector3 to;
};