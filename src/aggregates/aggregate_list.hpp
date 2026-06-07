#pragma once

#include "core/primitive.hpp"
#include "primitive/aggregate_primitive.hpp"
#include <memory>
#include <vector>

class AggregateList : public AggregatePrimitive{
public:
  AggregateList(std::vector<std::unique_ptr<Primitive>> &&v){
    objects = std::move(v);
  }
  bool intersect_p(const Ray &r) const override;
  std::optional<Surfel> intersect(const Ray &r) const override;
  const Material *get_material() const override;
  std::vector<std::unique_ptr<Primitive>> objects;
};