#pragma once
#include "core/light.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"

class AmbientLight : public Light {
public:
  AmbientLight(const ParamSet &ps);
  Color sample_li(const Surfel &s, Vector3 &dir,
                  const std::shared_ptr<Primitive> aggregator,
                  const Ray &r /*, VisibilityTester v*/) override;
};