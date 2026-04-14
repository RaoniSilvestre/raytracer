
#include "core/material.hpp"
#include "core/scene.hpp"
#include <memory>

void Material::make_material(const ParamSet &ps, Scene &s) {
  s.material = std::make_shared<Material>(ps);
}
