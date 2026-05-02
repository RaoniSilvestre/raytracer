#pragma once

#include "core/background_color.hpp"
#include "core/camera.hpp"
#include "core/param_set.hpp"
#include "core/ray.hpp"
#include "core/scene.hpp"
#include <memory>
#include <optional>

class Integrator {
public:
  static std::shared_ptr<Integrator> make_integrator(const ParamSet &ps,
                                                     std::unique_ptr<Camera>);
  virtual void preprocess([[maybe_unused]] const Scene &s) {};
  virtual ~Integrator() = default;
  Integrator() = default;
  std::unique_ptr<Camera> camera;
  virtual std::optional<Color> li(const Ray &r, const Scene &scene) const = 0;
};
