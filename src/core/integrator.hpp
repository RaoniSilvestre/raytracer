#pragma once

#include "core/background_color.hpp"
#include "core/camera.hpp"
#include "core/scene.hpp"
#include "core/ray.hpp"
#include <memory>
#include <optional>
class Integrator{
public:
    virtual ~Integrator() = default;
    static void make_integrator();
    std::unique_ptr<Camera> camera;
    virtual std::optional<Color> li(const Ray& r, const Scene &scene) const;
};