#pragma once

#include "color.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"

class Light {
public:
  virtual ~Light() = default;
  virtual Color sample_li(const Surfel &s,
                          Vector3 &dir /*, VisibilityTester v*/) = 0;

private:
  Color intensity;
  Color scale;
};