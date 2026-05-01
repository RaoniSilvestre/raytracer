#include "primitive/geometric_primitive.hpp"
#include "math/vector_3.hpp"
#include "shape/sphere.hpp"
#include <iostream>
#include <optional>

std::optional<Surfel> GeometricPrimitive::intersect(const Ray &r) const{
    return this->geoshape->intersect(r);
}

bool GeometricPrimitive::intersect_p(const Ray &r) const{
    return this->geoshape->intersect_p(r);
}

const Material *GeometricPrimitive::get_material(){
    return material.get();
}

void GeometricPrimitive::make_object(const ParamSet &ps, Scene &scene) {
  std::string object_type = ps.retrieve<std::string>("type");
  if(object_type == "sphere"){
    std::unique_ptr g = std::make_unique<GeometricPrimitive>(scene.material, std::make_shared<Sphere>(ps));
    scene.objects.push_back(std::move(g));
  }
}

Point3 GeometricPrimitive::get_center() const{
  return geoshape->center;
}
