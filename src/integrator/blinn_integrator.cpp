#include "integrator/blinn_integrator.hpp"
#include "math/vector_3.hpp"
#include <optional>

std::optional<Color> BlinnIntegrator::li(const Ray &ray, const Scene &scene,
                                         [[maybe_unused]] int depth) const {
  std::optional<Color> c = std::nullopt;
  Vector3 unused_placeholder;
  double hit_t = std::numeric_limits<double>::infinity();
  for (const auto &obj : scene.objects) {
    auto s = obj->intersect(ray);
    if (s && s->t < hit_t) {
      if (!c) {
        c = {0., 0., 0.};
      }
      hit_t = s->t;
      for (auto &l : scene.lights) {
        c = c.value() +
            l->sample_li(s.value(), unused_placeholder, scene.objects, ray);
      }
    } else {
    }
  }
  return c;
}
