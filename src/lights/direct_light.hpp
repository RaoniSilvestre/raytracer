#pragma once
#include "core/light.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"

class DirectLight : public Light {
public:
  DirectLight(const ParamSet &ps);
  Color sample_li(const Surfel &s, Vector3 &dir,
                  const std::vector<std::unique_ptr<Primitive>> &obj,
                  const Ray &r /*, VisibilityTester v*/) override;

private:
  Vector3 direction;
};