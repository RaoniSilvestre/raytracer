#pragma once
#include "core/light.hpp"
#include "core/param_set.hpp"
#include "core/primitive.hpp"
#include "math/vector_3.hpp"
#include <memory>

class DirectLight : public Light {
public:
  DirectLight(const ParamSet &ps);
  Color sample_li(const Surfel &s, Vector3 &dir,
                  const std::shared_ptr<Primitive> aggregator,
                  const Ray &r /*, VisibilityTester v*/) override;

private:
  Vector3 direction;
};