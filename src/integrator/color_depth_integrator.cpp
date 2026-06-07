
#include "integrator/color_depth_integrator.hpp"
#include "aggregates/aggregate_list.hpp"
#include "core/scene.hpp"
#include <algorithm>
#include <limits>

std::optional<Color>
ColorDepthIntegrator::li(const Ray &ray, const Scene &scene,
                         [[maybe_unused]] int depth) const {
  std::optional<Color> c = std::nullopt;
  double hit_t = std::numeric_limits<double>::infinity();
  auto s = scene.objects_aggregate->intersect(ray);
  if (s && s->t < hit_t) {
    hit_t = s->t;
    double normalized_t = std::clamp((hit_t - zmin) / (zmax - zmin), 0., 1.);
    c = Color::interpolate(s->primitive->get_material()->get_color(),
                            Color::interpolate(near, far, normalized_t),
                            normalized_t);
  }
  if (!c) {
    return far;
  }
  return c;
}

void ColorDepthIntegrator::preprocess(const Scene &scene) {
  std::cout << ">>> Preprocessing image\n";
  double min_t_dist = 0;
  double max_t_dist = std::numeric_limits<double>::infinity();
  AggregateList* agglist = dynamic_cast<AggregateList*>(scene.objects_aggregate.get());
  for (const auto &obj : agglist->objects) {
    double dist = (obj->get_center() - camera->origin).length();
    min_t_dist = std::min(min_t_dist, dist);
    max_t_dist = std::max(max_t_dist, dist);
  }
  this->scene_z_min = min_t_dist;
  this->scene_z_max = max_t_dist;
  std::cout << ">>> Preprocessing finished\n";
}
