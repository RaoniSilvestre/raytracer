#include "lights/ambient_light.hpp"
#include "core/color.hpp"
#include "core/param_set.hpp"
#include "core/primitive.hpp"
#include "core/ray.hpp"
#include "core/surfel.hpp"
#include "lights/direct_light.hpp"
#include "math/vector_3.hpp"
#include <cmath>
#include <limits>
#include <memory>

AmbientLight::AmbientLight(const ParamSet &ps) {
  this->scale = ps.retrieve<Color>("scale");
  this->intensity = this->scale * (ps.retrieve<Color>("intensity"));
  this->lt = light_type::AMBIENT;
}
Color AmbientLight::sample_li(
    const Surfel &s, [[maybe_unused]] Vector3 &out,
    [[maybe_unused]] const std::vector<std::unique_ptr<Primitive>> &obj,
    [[maybe_unused]] const Ray &r) {

  Color L = intensity * s.primitive->get_material()->get_ambient();
  return L;
}