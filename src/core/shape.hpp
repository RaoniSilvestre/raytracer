// core/shape.hpp
#pragma once

#include "core/param_set.hpp"
#include "core/ray.hpp"
#include "core/scene.hpp"
#include "core/surfel.hpp"
#include <optional>

class Shape {
public:
  virtual ~Shape() = default;

  virtual std::optional<Surfel> intersect(const Ray &r) const = 0;
  
  virtual bool intersect_p(const Ray &r) const = 0;

protected:
  bool flip_normals;
};
