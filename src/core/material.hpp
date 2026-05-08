#pragma once
#include "core/background_color.hpp"
#include "core/color.hpp"
#include "core/param_set.hpp"
#include <string>

class Material {
public:
  virtual ~Material() = default;
  virtual Color get_color() const = 0;
  std::string type;
  static void make_material(const ParamSet &ps, Scene &s);
  static void make_new_named_material(const ParamSet &ps, Scene &s);
  static void process_named_material(const ParamSet &ps, Scene &s);
};
