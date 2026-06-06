// core/shape.hpp
#pragma once

#include "core/ray.hpp"
#include "core/scene.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"
#include <optional>

struct BoundingBox{
  Point3 lower_limit;
  Point3 upper_limit;
};

class Shape {
protected:
  BoundingBox bounds;
public:
  virtual ~Shape() = default;

  virtual bool intersect_p(const Ray &r) const {
    return intersect(r).has_value();
  }
  virtual std::optional<Surfel> intersect(const Ray &r) const = 0;
  virtual Point3 get_center() const = 0;
  virtual BoundingBox get_bounding_box() const = 0;
};
