#include "core/integrator.hpp"


class FlatIntegrator : public Integrator{
public:
    std::optional<Color> li(const Ray& ray, const Scene &scene) const override;
};
