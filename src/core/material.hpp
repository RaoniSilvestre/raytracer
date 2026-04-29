#pragma once
#include "core/background_color.hpp"
#include "core/param_set.hpp"
#include <string>

class Material {
public:
  std::string type;
  Color color;

  Material(const ParamSet &ps)
      : type(ps.retrieve<std::string>("type")),
        color(ps.retrieve<Color>("color")) {}

  static void make_material(const ParamSet &ps, Scene &s);
  static void make_new_named_material(const ParamSet &ps, Scene &s);
  static void process_named_material(const ParamSet &ps, Scene &s);
};
