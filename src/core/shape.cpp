#include "core/shape.hpp"
#include "shape/sphere.hpp"
#include <memory>

void Shape::make_object(const ParamSet &ps, Scene &scene) {
  scene.objects.push_back(std::make_unique<Sphere>(ps, scene.material));
}
