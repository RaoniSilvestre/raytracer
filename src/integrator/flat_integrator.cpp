#include "integrator/flat_integrator.hpp"
#include "core/background_color.hpp"
#include "core/surfel.hpp"
#include <limits>
#include <optional>

std::optional<Color> FlatIntegrator::li(const Ray &ray, const Scene &scene,
                                        [[maybe_unused]] int depth) const {
  std::optional<Color> c = std::nullopt;
  double hit_t = std::numeric_limits<double>::infinity();
  auto s = scene.objects_aggregate->intersect(ray);
  if (s && s->t < hit_t) {
    hit_t = s->t;
    c = s->primitive->get_material()->get_color();
  }

  return c;
}
