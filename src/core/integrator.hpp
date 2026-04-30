#pragma once

#include "core/background_color.hpp"
#include "core/camera.hpp"
#include "core/param_set.hpp"
#include "core/scene.hpp"
#include "core/ray.hpp"
#include <algorithm>
#include <memory>
#include <optional>

class Integrator{
public:
    static std::shared_ptr<Integrator> make_integrator(const ParamSet &ps, std::unique_ptr<Camera>);
    
    virtual ~Integrator() = default;
    Integrator() = default;
    std::unique_ptr<Camera> camera;
    virtual std::optional<Color> li(const Ray& r, const Scene &scene) const = 0;
};