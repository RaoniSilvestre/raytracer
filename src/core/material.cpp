
#include "core/material.hpp"
#include "core/scene.hpp"
#include "material/blinn_material.hpp"
#include "material/flat_material.hpp"
#include <memory>
#include <string>

void Material::make_material(const ParamSet &ps, Scene &s) {
  std::string type = ps.retrieve<std::string>("type");
  if (type == "blinn") {
    s.material = std::make_shared<BlinnMaterial>(ps);
  } else if (type == "flat") {
    s.material = std::make_shared<FlatMaterial>(ps);
  }
}

void Material::make_new_named_material(const ParamSet &ps, Scene &s) {
  std::string name = ps.retrieve<std::string>("name");
  std::string type = ps.retrieve<std::string>("type");
  std::shared_ptr<Material> m;
  if (type == "blinn" || type == "blinn_phong") {
    m = std::make_shared<BlinnMaterial>(ps);
  } else if (type == "flat") {
    m = std::make_shared<FlatMaterial>(ps);
  }
  s.named_materials.insert(std::make_pair(name, std::move(m)));
}

void Material::process_named_material(const ParamSet &ps, Scene &s) {
  std::string name = ps.retrieve<std::string>("name");
  s.material = s.named_materials[name];
}