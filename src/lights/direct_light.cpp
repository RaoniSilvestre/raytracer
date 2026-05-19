#include "lights/direct_light.hpp"
#include "core/color.hpp"
#include "core/param_set.hpp"
#include "core/primitive.hpp"
#include "core/ray.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"
#include <cmath>
#include <limits>
#include <memory>

DirectLight::DirectLight(const ParamSet &ps) {
  auto from = ps.retrieve<Point3>("from");
  auto to = ps.retrieve<Point3>("to");
  this->direction = unit_vector(to - from);

  this->scale = ps.retrieve<Color>("scale");
  this->intensity = this->scale * (ps.retrieve<Color>("intensity"));
  this->lt = light_type::DIRECTIONAL;
}
Color DirectLight::sample_li(const Surfel &s, [[maybe_unused]] Vector3 &out,
                             const std::vector<std::unique_ptr<Primitive>> &obj,
                             const Ray &r) {
  const double epsilon = 0.000001;

  Vector3 unit_normal = unit_vector(s.norm);
  Ray light_ray(s.point + -(this->direction) * epsilon, -(this->direction));
  double hit_t = std::numeric_limits<double>::infinity();
  for (auto &o : obj) {
    if (o.get() == s.primitive) {
      // std::cout << "same object\n";
      continue;
    }
    auto surface = o->intersect(light_ray);
    if (surface && surface->t < hit_t) {
      // hit_t = surface->t;
      return {0., 0., 0.}; // black
    }
  }
  double n_l_cos = std::max(0., dot(-(this->direction), unit_normal));
  Color kd = s.primitive->get_material()->get_diffuse();
  Vector3 unit_in_direction = unit_vector(-r.direcao);
  Vector3 h = (unit_in_direction + -(this->direction)) /
              (unit_in_direction + -(this->direction)).length();
  Color ks = s.primitive->get_material()->get_specular();
  double n_h_cos = std::max(0., dot(unit_normal, h));
  double glossiness = s.primitive->get_material()->get_glossiness();
  Color L = kd * intensity * n_l_cos;
  if (glossiness > 0) {
    L = L + ks * intensity * pow(n_h_cos, glossiness);
  }
  return L;
}