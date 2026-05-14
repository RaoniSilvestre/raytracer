#pragma once

#include "core/background_color.hpp"
#include "core/camera.hpp"
#include "core/integrator.hpp"
#include <memory>
class NormalMapIntegrator : public Integrator {
public:
  std::optional<Color> li(const Ray &ray, const Scene &scene,
                          int depth = 0) const override;
  NormalMapIntegrator(std::unique_ptr<Camera> c) { camera = std::move(c); }
};
