
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
  float l, r, b, t;

  OrthographicCamera(LookAt lookat, std::vector<float> sw,
                     std::unique_ptr<Film> &_film)
      : Camera(std::move(_film)) {

    l = sw[0];
    r = sw[1];
    b = sw[2];
    t = sw[3];

    origin = lookat.look_from;
    Vector3 w_ = lookat.look_at - lookat.look_from;
    w_.make_unit_vector();

    w = w_;
    u = unit_vector(cross(lookat.up, w));

    v = cross(w, u);
  }

  Ray generate_ray(u_int32_t x, u_int32_t y) override;
};
