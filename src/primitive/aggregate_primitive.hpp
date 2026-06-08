#pragma once

#include "core/param_set.hpp"
#include "core/primitive.hpp"
#include "core/scene.hpp"
#include <algorithm>
#include <memory>
#include <stdexcept>

class AggregatePrimitive : public Primitive{
public:
  Point3 get_center() const {throw std::runtime_error("cannot call get center of an aggregate");}
  virtual bool intersect_p(const Ray &r) const = 0;
  virtual std::optional<Surfel> intersect(const Ray &r) const = 0;
  virtual const Material *get_material() const = 0;
  static void make_aggregate(const ParamSet& ps, Scene &s);
  virtual const std::vector<std::unique_ptr<Primitive>>& get_objects_list() const = 0; 
};