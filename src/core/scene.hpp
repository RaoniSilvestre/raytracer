#pragma once

#include "core/background_color.hpp"
#include "core/primitive.hpp"
#include <memory>
#include <vector>
#include <map>

class Scene {
public:
  std::unique_ptr<BackgroundColor> background;
  std::vector<std::unique_ptr<Primitive>> objects;
  std::map<std::string, std::shared_ptr<Material>> named_materials;
  std::shared_ptr<Material> material;
};
