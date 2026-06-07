#include "integrator/blinn_integrator.hpp"
#include "core/color.hpp"
#include "core/material.hpp"
#include "math/vector_3.hpp"
#include <iostream>
#include <limits>
#include <optional>

std::optional<Color> BlinnIntegrator::li(const Ray &ray, const Scene &scene,
                                         int depth) const {
  std::optional<Color> c = std::nullopt;
  double hit_t = std::numeric_limits<double>::infinity();
  Vector3 reflecting;
  Point3 hit_point;
  Color reflect_coef;
  auto s = scene.objects_aggregate->intersect(ray);
  if (s && s->t < hit_t) {
    c = {0., 0., 0.};
    hit_t = s->t;
    hit_point = s->point;
    reflecting = ray.direcao - 2.*(dot(ray.direcao, s->norm))*s->norm;
    reflect_coef = s->primitive->get_material()->get_mirror();
    for (auto &l : scene.lights) {
      c = c.value() + l->sample_li(s.value(), reflecting, scene.objects_aggregate, ray);
    }
  }
  if (c && depth < max_depth) {
    auto reflect_result =
    li(Ray(hit_point + reflecting * 0.1, reflecting), scene, depth + 1);
    if (reflect_result) {
      c = c.value() + (reflect_result.value()) * reflect_coef;
    }
  }
  return c;
}
