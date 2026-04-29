#pragma once

#include "core/film.hpp"
#include "core/look_at.hpp"
#include "core/param_set.hpp"
#include "ray.hpp"
#include <memory>
#include <sys/types.h>

class Camera {
public:
  virtual Ray generate_ray(u_int32_t x, u_int32_t y) = 0;
  virtual ~Camera() = default;

  std::unique_ptr<Film> film;

  Camera(std::unique_ptr<Film> _film) : film(std::move(_film)) {}

  static std::unique_ptr<Camera>
  make_camera(const ParamSet &ps, std::unique_ptr<Film> film, LookAt lookat);
};
