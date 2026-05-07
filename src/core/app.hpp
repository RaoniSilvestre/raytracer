#pragma once

#include "core/background_color.hpp"
#include "core/integrator.hpp"
#include "core/light.hpp"
#include "core/material.hpp"
#include "core/param_set.hpp"
#include "core/primitive.hpp"
#include "core/scene.hpp"
#include "primitive/geometric_primitive.hpp"
#include "rt3.hpp"
#include "tinyxml2.h"
#include <functional>
#include <memory>

struct ParseReturn {
  std::shared_ptr<Integrator> integrator;
};
class App {
private:
  using APIFunction = std::function<void(const ParamSet &, Scene &scene)>;

  static ParseReturn parse(const RunningOptions &opts, Scene &scene);
  static void render(const Scene &scene,
                     const std::shared_ptr<Integrator> integrator);

  static inline const std::unordered_map<std::string, APIFunction>
      dispatch_map = {
          {"background", BackgroundColor::make_background},
          {"object", GeometricPrimitive::make_object},
          {"material", Material::make_material},
          {"make_named_material", Material::make_new_named_material},
          {"named_material", Material::process_named_material},
          {"light_source", Light::make_light}

  };

  static void process_tag(tinyxml2::XMLElement *element);

public:
  static void run(const RunningOptions &opts);
};
