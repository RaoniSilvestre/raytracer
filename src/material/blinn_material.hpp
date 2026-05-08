#pragma once
#include "core/color.hpp"
#include "core/material.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"

class BlinnMaterial : public Material {
public:
  BlinnMaterial(const ParamSet &ps);
  Color get_color() const;
  // type="blinn" name="gold"ambient="0.4 0.4 0.4" diffuse ="1 0.65 0.0"
  // specular ="0.8 0.6 0.2"  glossiness ="256"
  Vector3 ambient;
  Vector3 diffuse;
  Vector3 specular;
  double glossiness;
};