#pragma once

#include "core/background_color.hpp"
#include "core/material.hpp"
#include "core/param_set.hpp"
#include "core/primitive.hpp"
#include "core/scene.hpp"
#include "rt3.hpp"
#include "tinyxml2.h"
#include <functional>

class App {
private:
  using APIFunction = std::function<void(const ParamSet &, Scene &scene)>;

  static void parse(const RunningOptions &opts, Scene &scene);
  static void render(const Scene &scene);

  static inline const std::unordered_map<std::string, APIFunction>
      dispatch_map = {{"background", BackgroundColor::make_background},
                      {"object", Primitive::make_object},
                      {"material", Material::make_material}

  };

  static void process_tag(tinyxml2::XMLElement *element);

public:
  static void run(const RunningOptions &opts);
};
