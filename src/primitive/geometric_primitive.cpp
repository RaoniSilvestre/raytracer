#include "primitive/geometric_primitive.hpp"
#include "core/shape.hpp"
#include "math/vector_3.hpp"
#include "shape/plane.hpp"
#include "shape/sphere.hpp"
#include "shape/triangle.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>

std::optional<Surfel> GeometricPrimitive::intersect(const Ray &r) const {
  return this->geoshape->intersect(r);
}

bool GeometricPrimitive::intersect_p(const Ray &r) const {
  return this->geoshape->intersect_p(r);
}

const Material *GeometricPrimitive::get_material() { return material.get(); }

std::shared_ptr<Shape> get_shape(const ParamSet &ps) {
  std::string object_type = ps.retrieve<std::string>("type");
  if (object_type == "sphere") {
    return std::make_shared<Sphere>(ps);
  } else if (object_type == "triangle") {
    auto shared_tri = std::make_shared<Triangle>(ps);
    if (shared_tri->is_degenerate()) {
      std::cout << "degenerate triangle\n";
      throw std::runtime_error("Triangulo degenerado");
    }

    return shared_tri;
  } else if (object_type == "plane") {
    return std::make_shared<Plane>(ps);
  }

  throw std::runtime_error("Objeto não parseável");
}

void GeometricPrimitive::make_object(const ParamSet &ps, Scene &scene) {
  std::shared_ptr<Shape> shape = get_shape(ps);

  auto geometric_primitive =
      std::make_unique<GeometricPrimitive>(scene.material, shape);

  scene.objects.push_back(std::move(geometric_primitive));
}

Point3 GeometricPrimitive::get_center() const { return geoshape->get_center(); }
