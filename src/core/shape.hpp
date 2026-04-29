// core/shape.hpp
#pragma once

#include "core/param_set.hpp"
#include "core/ray.hpp"
#include "core/scene.hpp"

class Shape {
public:
  virtual ~Shape() = default;

  static void make_object(const ParamSet &ps, Scene &scene);

  virtual bool intersect(const Ray &r, Surfel *s) const = 0;
  
  virtual bool intersect_p(const Ray &r) const = 0;

protected:
  bool flip_normals;
};
