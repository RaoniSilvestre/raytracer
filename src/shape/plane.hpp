#include "core/shape.hpp"
#include "math/vector_3.hpp"

class Plane : public Shape {
public:
  std::optional<Surfel> intersect(const Ray &r) const override;
  Point3 get_center() const override;

  Plane(Point3 p, Vector3 n) {
    point = p;
    normal = unit_vector(n);
  };

  Plane(const ParamSet &ps);

private:
  Point3 point;
  Vector3 normal;
};
