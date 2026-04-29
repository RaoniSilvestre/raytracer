// shape/sphere.hpp
#pragma once

#include "core/param_set.hpp"
#include "core/shape.hpp"
#include "math/vector_3.hpp"

class Sphere : public Shape {
public:
  bool intersect_p(const Ray &r) const override;

  bool intersect(const Ray &r, Surfel *s) const override;
  
  Sphere(double r, Point3 c) {
    radius = r;
    center = c;
  };

  Sphere(const ParamSet &ps);

private:
  double radius;
  Point3 center;
};
