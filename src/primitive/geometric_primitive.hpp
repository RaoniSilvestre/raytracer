#pragma once
#include "core/bounding_box.hpp"
#include "core/primitive.hpp"
#include "core/shape.hpp"
#include "math/vector_3.hpp"
#include <memory>
#include <optional>

class GeometricPrimitive : public Primitive {
public:
  GeometricPrimitive(std::shared_ptr<Material> m, std::shared_ptr<Shape> s)
      : material{m}, geoshape{s} {}
  static void make_object(const ParamSet &ps, Scene &scene);
  bool intersect_p(const Ray &r) const override;
  std::optional<Surfel> intersect(const Ray &r) const override;
  Material *get_material() const override;
  Point3 get_center() const override;
  BoundingBox get_bounding_box() const override{
    return geoshape->get_bounding_box();
  }
private:
  std::shared_ptr<Material> material;
  std::shared_ptr<Shape> geoshape;
};
