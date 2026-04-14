
#include "core/app.hpp"
#include "core/look_at.hpp"
#include "math/vector_3.hpp"
#include <memory>
#include <utility>
#include <vector>

class OrthographicCamera : public Camera {
public:
  Vector3 u, v, w;
  Point3 origin;
  double l, r, b, t;

  OrthographicCamera(LookAt lookat, std::vector<double> sw,
                     std::unique_ptr<Film> &_film)
      : Camera(std::move(_film)) {

    l = sw[0];
    r = sw[1];
    b = sw[2];
    t = sw[3];

    origin = lookat.look_from;

    w = unit_vector(lookat.look_at - lookat.look_from);
    u = unit_vector(cross(lookat.up, w));
    v = unit_vector(cross(w, u));
  }

  Ray generate_ray(u_int32_t x, u_int32_t y) override;
};
