#pragma once
#include "core/background_color.hpp"
#include "core/light.hpp"
#include "core/primitive.hpp"
#include <map>
#include <memory>
#include <vector>
class Light;
class Scene {
public:
  std::unique_ptr<BackgroundColor> background;
  std::vector<std::unique_ptr<Primitive>> objects;
  std::map<std::string, std::shared_ptr<Material>> named_materials;
  std::shared_ptr<Material> material;
  std::vector<std::unique_ptr<Light>> lights;
};
