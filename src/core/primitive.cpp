

#include "core/primitive.hpp"
#include "core/param_set.hpp"
#include "core/scene.hpp"
#include "object/sphere.hpp"
#include <memory>

// Quando tiver outros objetos, fazer parse de cada um aqui
void Primitive::make_object(const ParamSet &ps, Scene &scene) {
  scene.objects.push_back(std::make_unique<Sphere>(ps, scene.material));
}
