#include "core/film.hpp"
#include "ray.hpp"
#include <memory>
#include <utility>

class Camera {
public:
  Camera(std::unique_ptr<Film> _film) { film = std::move(_film); }

  virtual Ray generate_ray(int x, int y) = 0;
  virtual ~Camera() {};

  void set_film(std::unique_ptr<Film> &_film) { film = std::move(_film); }

  std::unique_ptr<Film> film;
};
