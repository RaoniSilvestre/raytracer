#include "integrator/depth_integrator.hpp"
#include "core/scene.hpp"
#include <algorithm>
#include <limits>

std::optional<Color> DepthIntegrator::li(const Ray& ray, const Scene &scene) const{
  std::optional<Color> c = std::nullopt;
  double hit_t = std::numeric_limits<double>::infinity();
  for (const auto &obj : scene.objects) {
    auto s = obj->intersect(ray);
    if(s && s->t < hit_t){
      hit_t = s->t;
      double normalized_t = std::clamp((hit_t-zmin)/(zmax-zmin), 0., 1.);
      c = Color::interpolate(near, far, normalized_t);
    }
  }
  if(!c){
    return far;
  }
  return c;
}

void DepthIntegrator::preprocess(const Scene &scene){
    std::cout << ">>> Preprocessing image\n";
    double min_t_dist = 0;
    double max_t_dist = std::numeric_limits<double>::infinity();
  
    for (const auto &obj : scene.objects) {
        double dist = (obj->get_center() - camera->origin).length();
        min_t_dist = std::min(min_t_dist, dist);
        max_t_dist = std::max(max_t_dist, dist);
    }
  this->scene_z_min = min_t_dist;
  this->scene_z_max = max_t_dist; 
  std::cout << ">>> Preprocessing finished\n";
}