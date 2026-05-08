#include "lights/point_light.hpp"
#include "core/color.hpp"
#include "core/param_set.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"

PointLight::PointLight(const ParamSet &ps) {
  this->from = ps.retrieve<Point3>("from");
  this->to = ps.retrieve<Vector3>("to");
  this->intensity = ps.retrieve<Color>("intensity");
  this->scale = ps.retrieve<Color>("scale");
}
Color PointLight::sample_li(const Surfel &s, Vector3 &v) {
  return {0., 0., 0.};
}