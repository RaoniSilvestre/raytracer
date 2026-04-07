#include "core/film.hpp"
#include "core/look_at.hpp"
#include "core/param_set.hpp"
#include "ray.hpp"
#include <memory>

class Camera {
public:
  virtual Ray generate_ray(int x, int y) = 0;
  virtual ~Camera() = default;

  std::unique_ptr<Film> film;

  Camera(std::unique_ptr<Film> _film) : film(std::move(_film)) {}

  Camera(const ParamSet &ps, Film film, LookAt lookat);
  static std::unique_ptr<Camera>
  make_camera(const ParamSet &ps, std::unique_ptr<Film> film, LookAt lookat);
};
