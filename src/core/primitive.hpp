#pragma once
#include "core/bounding_box.hpp"
#include "core/material.hpp"
#include "core/param_set.hpp"
#include "core/ray.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"
#include <optional>

class Surfel;

class Primitive {
public:
  virtual ~Primitive() = default;

  static void make_object(const ParamSet &ps, Scene &scene);
  virtual Point3 get_center() const = 0;
  virtual bool intersect_p(const Ray &r) const = 0;
  virtual std::optional<Surfel> intersect(const Ray &r) const = 0;
  virtual const Material *get_material() const = 0;
  virtual BoundingBox get_bounding_box() const {return {{0., 0.,0.},{0., 0.,0.}};};
};