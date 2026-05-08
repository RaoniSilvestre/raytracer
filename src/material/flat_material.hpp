#include "core/material.hpp"

class FlatMaterial : public Material {
public:
  FlatMaterial(const ParamSet &ps);
  Color get_color() const;
  Color c;
};