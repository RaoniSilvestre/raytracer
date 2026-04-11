#include "core/app.hpp"
#include "core/primitive.hpp"
#include "math/vector_3.hpp"

class Sphere : public Primitive {
public:
  bool intersect_p(const Ray &r) const override;

  Sphere(double r, Point3 c) {
    radius = r;
    center = c;
  };

private:
  double radius;
  Point3 center;
};
