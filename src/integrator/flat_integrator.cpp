#include "integrator/flat_integrator.hpp"

#include "core/background_color.hpp"
#include <optional>

/**
  If no object is hit the function returns a nullptr
*/
std::optional<Color> FlatIntegrator::li(const Ray& ray, const Scene &scene) const {
      std::optional<Color> c = std::nullopt;

      for (const auto &obj : scene.objects) {
        if (obj->intersect_p(ray)) {
          c = obj->get_material()->color;
          break;
        }
      }

      return c;
    }