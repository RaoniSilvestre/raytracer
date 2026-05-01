#include "integrator/depth_integrator.hpp"
#include "core/scene.hpp"
#include <algorithm>

std::optional<Color> DepthIntegrator::li(const Ray& ray, const Scene &scene) const{
  std::optional<Color> c = std::nullopt;
  double hit_t = std::numeric_limits<double>::infinity();
  for (const auto &obj : scene.objects) {
    auto s = obj->intersect(ray);
    if(s && s->t < hit_t){
      hit_t = s->t;
      double normalized_t = (std::clamp(hit_t, zmin, zmax)-zmin)/(zmax-zmin);
      c = Color::interpolate(near, far, normalized_t);
      std::cout << c.value() << "\n";
    }
  }
  if(!c){
    return far;
  }
  return c;
}

void DepthIntegrator::preprocess(Scene &scene){
    double min_t_dist;
    double max_t_dist;
    for (const auto &obj : scene.objects){
        double dist = (obj->get_center() - camera->origin).length();
        min_t_dist = std::min(min_t_dist, dist);
        max_t_dist = std::max(max_t_dist, dist); 
    }
    z_depth = max_t_dist;
}