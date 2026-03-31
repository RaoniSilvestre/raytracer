#include "core/film.hpp"
#include "ray.hpp"
#include <memory>

class Camera {
  virtual Ray generate_ray(int x, int y) = 0;
  virtual ~Camera() = 0;

  std::unique_ptr<Film> film;
};
