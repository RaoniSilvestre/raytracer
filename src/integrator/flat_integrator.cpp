#include "integrator/flat_integrator.hpp"
#include <cmath>
#include "core/background_color.hpp"
#include "core/surfel.hpp"
#include <limits>
#include <optional>

/**
  If no object is hit the function returns a nullopt
*/
std::optional<Color> FlatIntegrator::li(const Ray& ray, const Scene &scene) const {
      std::optional<Color> c = std::nullopt;
      double hit_t = std::numeric_limits<double>::infinity();
      for (const auto &obj : scene.objects) {
        auto s = obj->intersect(ray);
        if(s && s->t < hit_t){
          hit_t = s->t;
          c = obj->get_material()->color;
        }
      }

      return c;
    }