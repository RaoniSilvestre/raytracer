#include "primitive/geometric_primitive.hpp"
#include "core/shape.hpp"
#include "math/vector_3.hpp"
#include "shape/plane.hpp"
#include "shape/sphere.hpp"
#include "shape/triangle.hpp"
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

std::optional<Surfel> GeometricPrimitive::intersect(const Ray &r) const {
  auto s = this->geoshape->intersect(r);
  if (s) {
    s->set_primitive(this);
  }
  return s;
}

bool GeometricPrimitive::intersect_p(const Ray &r) const {
  return this->geoshape->intersect_p(r);
}

Material *GeometricPrimitive::get_material() const { return material.get(); }

std::vector<std::shared_ptr<Shape>> get_shapes(const ParamSet &ps) {
  std::string object_type = ps.retrieve<std::string>("type");

  if (object_type == "sphere") {
    return {std::make_shared<Sphere>(ps)};
  } else if (object_type == "trianglemesh") {
    bool flip_normals = false;
    return create_triangle_mesh_shape(flip_normals, ps);
  } else if (object_type == "plane") {
    return {std::make_shared<Plane>(ps)};
  }

  throw std::runtime_error("Objeto não parseável");
}

void GeometricPrimitive::make_object(const ParamSet &ps, Scene &scene) {
  std::vector<std::shared_ptr<Shape>> shapes = get_shapes(ps);

  for (const auto &shape : shapes) {
    auto geometric_primitive =
          std::make_unique<GeometricPrimitive>(scene.material, shape);
    scene.objects.push_back(std::move(geometric_primitive));
  }
}

Point3 GeometricPrimitive::get_center() const { return geoshape->get_center(); }
