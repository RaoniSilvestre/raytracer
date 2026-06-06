#pragma once

#include "color.hpp"
#include "core/param_set.hpp"
#include "core/scene.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"
#include <vector>

class Light {

public:
  virtual ~Light() = default;
  virtual Color sample_li(const Surfel &s, Vector3 &dir,
                          const std::vector<std::unique_ptr<Primitive>> &obj,
                          const Ray &r /*, VisibilityTester v*/) = 0;
  static void make_light(const ParamSet &ps, Scene &s);

protected:
  enum class light_type {
    POINT,
    AMBIENT,
    DIRECTIONAL,
    SPOT,
  };
  light_type lt;
  Color intensity;
  Color scale;
};