#include "core/integrator.hpp"
#include <algorithm>
#include <memory>

class FlatIntegrator : public Integrator {
public:
  std::optional<Color> li(const Ray &ray, const Scene &scene,
                          int depth = 0) const override;
  FlatIntegrator(std::unique_ptr<Camera> c) { camera = std::move(c); };
};
