#pragma once

#include "core/background_color.hpp"
#include "core/camera.hpp"
#include "core/primitive.hpp"
#include <memory>
#include <vector>

class Scene {
public:
  std::unique_ptr<BackgroundColor> background;
  std::unique_ptr<Camera> camera;
  std::vector<std::unique_ptr<Primitive>> objects;
  std::shared_ptr<Material> material;
};
