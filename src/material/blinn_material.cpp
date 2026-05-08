#include "material/blinn_material.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"
#include <string>

BlinnMaterial::BlinnMaterial(const ParamSet &ps) {
  this->ambient = ps.retrieve<Vector3>("ambient");
  this->diffuse = ps.retrieve<Vector3>("diffuse");
  this->specular = ps.retrieve<Vector3>("specular");
  this->glossiness = ps.retrieve<double>("glossiness");
  this->type = ps.retrieve<std::string>("type");
}
Color BlinnMaterial::get_color() const {
  return {diffuse.x(), diffuse.y(), diffuse.z()};
}