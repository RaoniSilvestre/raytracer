#pragma once
#include "core/color.hpp"
#include "core/material.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"

class BlinnMaterial : public Material {
public:
  BlinnMaterial(const ParamSet &ps);
  Color mirror;
  Color ambient;
  Color diffuse;
  Color specular;
  double glossiness;
  Color get_color() const override;
  Color get_ambient() const override;
  Color get_diffuse() const override;
  Color get_specular() const override;
  double get_glossiness() const override;
  Color get_mirror() const override;
};