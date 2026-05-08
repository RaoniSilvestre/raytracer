#pragma once

#include "color.hpp"
#include "core/param_set.hpp"
#include "core/scene.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"

class Light {
public:
  virtual ~Light() = default;
  virtual Color sample_li(const Surfel &s,
                          Vector3 &dir /*, VisibilityTester v*/) = 0;
  static void make_light(const ParamSet &ps, Scene &s);
  std::string type;

protected:
  Color intensity;
  Color scale;
};