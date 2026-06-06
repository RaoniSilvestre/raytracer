#include "core/light.hpp"
#include "core/param_set.hpp"
#include "core/scene.hpp"
#include "lights/ambient_light.hpp"
#include "lights/direct_light.hpp"
#include "lights/spot_light.hpp"
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
  } else if (type == "directional") {
    auto ptr = std::make_unique<DirectLight>(ps);
    s.lights.push_back(std::move(ptr));
  } else if (type == "ambient") {
    auto ptr = std::make_unique<AmbientLight>(ps);
    s.lights.push_back(std::move(ptr));
  } else if(type == "spot"){
    auto ptr = std::make_unique<SpotLight>(ps);
    s.lights.push_back(std::move(ptr));
  }
  else {
    std::cout << "ignoring temporary unsuported light type\n";
  }
}
