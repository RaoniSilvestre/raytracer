#pragma once

#include "camera.hpp"
#include "core/background_color.hpp"
#include "core/param_set.hpp"
#include "film.hpp"
#include "rt3.hpp"
#include "tinyxml2.h"
#include <functional>
#include <memory>

class App {
private:
  static std::unique_ptr<BackgroundColor> background;
  static std::unique_ptr<Film> film;
  static std::unique_ptr<Camera> camera;

  using APIFunction = std::function<void(const ParamSet &)>;

  static void initialize();
  static void make_film(const ParamSet &);
  static void make_camera(const ParamSet &);
  static void make_background(const ParamSet &);
  static void parse(const RunningOptions &opts);
  static void render();

  static inline const std::unordered_map<std::string, APIFunction>
      dispatch_map = {{"film", App::make_film},
                      {"background", App::make_background},
                      {"camera", App::make_camera}};

  static void process_tag(tinyxml2::XMLElement *element);

public:
  static void run(const RunningOptions &opts);
};
