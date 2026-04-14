#include "core/material.hpp"
#include "core/param_set.hpp"
#include "core/primitive.hpp"
#include "math/vector_3.hpp"
#include <memory>

class Sphere : public Primitive {
public:
  bool intersect_p(const Ray &r) const override;

  Sphere(double r, Point3 c) {
    radius = r;
    center = c;
  };

  Sphere(const ParamSet &ps, std::shared_ptr<Material> m);

private:
  double radius;
  Point3 center;
};
