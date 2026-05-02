#include "integrator/normal_map_integrator.hpp"
#include "math/vector_3.hpp"

Color convert_vec_into_color(Vector3 &v) {
  return {v.x() * 255., v.y() * 255., v.z() * 255.};
}

Vector3 convert_vec_into_positive(Vector3 &v) {
  return Vector3({v.x() + 1, v.y() + 1, v.z() + 1}) * 0.5;
}

std::optional<Color> NormalMapIntegrator::li(const Ray &ray,
                                             const Scene &scene) const {
  std::optional<Color> c = std::nullopt;
  double hit_t = std::numeric_limits<double>::infinity();
  for (const auto &obj : scene.objects) {
    auto s = obj->intersect(ray);
    if (s && s->t < hit_t) {
      hit_t = s->t;
      Vector3 norm = unit_vector(s->norm);
      norm = convert_vec_into_positive(norm);
      c = convert_vec_into_color(norm);
    }
  }

  return c;
}
