#include "material/blinn_material.hpp"
#include "core/color.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"
#include <string>

BlinnMaterial::BlinnMaterial(const ParamSet &ps) {
  this->ambient = ps.retrieve<Color>("ambient");
  this->diffuse = ps.retrieve<Color>("diffuse");
  this->specular = ps.retrieve<Color>("specular");
  this->mirror = ps.retrieve<Color>("mirror");

  this->glossiness = ps.retrieve<double>("glossiness");
  this->type = ps.retrieve<std::string>("type");

}
Color BlinnMaterial::get_color() const {
  return {diffuse.red, diffuse.green, diffuse.blue};
}
Color BlinnMaterial::get_diffuse() const {
  return {diffuse.red, diffuse.green, diffuse.blue};
}
Color BlinnMaterial::get_ambient() const {
  return {ambient.red, ambient.green, ambient.blue};
}
double BlinnMaterial::get_glossiness() const { return glossiness; }

Color BlinnMaterial::get_specular() const {
  return {specular.red, specular.green, specular.blue};
}
Color BlinnMaterial::get_mirror() const {
  return {mirror.red, mirror.green, mirror.blue};
}