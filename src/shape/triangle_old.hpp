#pragma once
#include "core/param_set.hpp"
#include "core/shape.hpp"
#include "math/vector_3.hpp"
namespace old_tri{

  class Triangle : public Shape {
  public:
    bool intersect_p(const Ray &r) const override;
    std::optional<Surfel> intersect(const Ray &r) const override;
    Triangle(const Point3 &a, const Point3 &b, const Point3 &c)
        : A{a}, B{b}, C{c} {
      norm = cross(C - A, B - A);
    }
    Triangle(const ParamSet &ps);
    Point3 get_center() const override;
  
    bool is_degenerate();
  
  private:
    Point3 A;
    Point3 B;
    Point3 C;
    Vector3 norm;
  };
}
