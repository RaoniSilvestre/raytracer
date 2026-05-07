
#include "core/material.hpp"
#include "core/scene.hpp"
#include <memory>
#include <string>

void Material::make_material(const ParamSet &ps, Scene &s) {
  std::string type = ps.retrieve<std::string>("type");
  if(type == "blinn"){
    
  }
  s.material = std::make_shared<Material>(ps);
}

void Material::make_new_named_material(const ParamSet &ps, Scene &s) {
  std::string name = ps.retrieve<std::string>("name");
  s.named_materials.insert(
      std::make_pair(name, std::make_shared<Material>(ps)));
}

void Material::process_named_material(const ParamSet &ps, Scene &s) {
  std::string name = ps.retrieve<std::string>("name");
  s.material = s.named_materials[name];
}