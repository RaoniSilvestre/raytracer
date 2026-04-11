
#include "object/sphere.hpp"
#include "math/vector_3.hpp"
#include <cmath>

bool Sphere::intersect_p(const Ray &r) const {
  Vector3 o_c = r.origem - center;
  Vector3 d = r.direcao;
  Vector3 d_hat = unit_vector(d);
  double parallel_length = dot(o_c, d_hat);
  Vector3 o_c_perp = o_c - parallel_length*d_hat;
  double delta = radius*radius-(dot(o_c_perp, o_c_perp));
  
  // Delta negativo significa que não intersecta.
  if (delta < 0) {
    return false;
  }
  return true;

  auto dd = dot(d, d);
  auto o_cd = dot(o_c, d);
  double sqrt_delta = sqrt(delta);

  double t = (-o_cd - sqrt_delta) / dd;

  if (t < 0) {
    t = (-o_cd + sqrt_delta) / dd;
    if (t < 0) {
      return false;
    }
  }


  return true;
}
