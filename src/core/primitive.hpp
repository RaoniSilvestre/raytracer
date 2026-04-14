#pragma once

#include "core/material.hpp"
#include "core/param_set.hpp"
#include "core/ray.hpp"

class Primitive {
public:
  virtual ~Primitive() = default;

  static void make_object(const ParamSet &ps, Scene &scene);

  virtual bool intersect_p(const Ray &r) const = 0;
  virtual const Material *get_material() const { return material.get(); }

protected:
  std::shared_ptr<Material> material;
};
