#include "core/light.hpp"
#include "core/param_set.hpp"
#include "core/scene.hpp"
#include "lights/point_light.hpp"
#include "math/vector_3.hpp"
#include <memory>
#include <stdexcept>
#include <string>

void Light::make_light(const ParamSet &ps, Scene &s) {
  std::string type = ps.retrieve<std::string>("type");
  if (type == "point") {
    auto ptr = std::make_unique<PointLight>(ps);
    s.lights.push_back(std::move(ptr));
  } else {
    std::cout << "ignoring temporary unsuported light type\n";
  }
}
