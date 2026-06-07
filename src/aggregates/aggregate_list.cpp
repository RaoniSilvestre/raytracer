#include "aggregates/aggregate_list.hpp"
#include <optional>
#include <stdexcept>


bool AggregateList::intersect_p(const Ray &r) const {
  auto s = intersect(r);
  return s.has_value();
}
std::optional<Surfel> AggregateList::intersect(const Ray &r) const {
  double hit_t = std::numeric_limits<double>::infinity();
  std::optional<Surfel> sfinal;
  for (const auto &obj : this->objects) {
    auto s = obj->intersect(r);
    if (s && s->t < hit_t) {
      hit_t = s->t;
      sfinal = s;
    }
  }
  return sfinal;
}

const Material *AggregateList::get_material() const {
  throw(std::runtime_error("Cannot call get_material from an aggregate list"));
}

