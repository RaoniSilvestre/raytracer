#pragma once

#include "core/camera.hpp"
#include "core/integrator.hpp"
#include <memory>

class BlinnIntegrator : public Integrator {
public:
  std::optional<Color> li(const Ray &ray, const Scene &scene,
                          int depth = 0) const override;
  BlinnIntegrator(std::unique_ptr<Camera> c, const int d) : max_depth{d} {
    camera = std::move(c);
  }

private:
  [[maybe_unused]] int max_depth;
};
