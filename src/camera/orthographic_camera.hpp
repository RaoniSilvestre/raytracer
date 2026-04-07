
#include "core/app.hpp"
#include "core/look_at.hpp"
#include "math/vector_3.hpp"
#include <memory>
#include <utility>
#include <vector>

class OrthographicCamera : public Camera {
public:
  Vector3 u, v, w;
  float bl, br, tl, tr;

  OrthographicCamera(LookAt lookat, std::vector<float> sw,
                     std::unique_ptr<Film> &_film)
      : Camera(std::move(_film)) {

    bl = sw[0];
    br = sw[1];
    tl = sw[2];
    tr = sw[3];

    Vector3 w_ = lookat.look_at - lookat.look_from;
    w.make_unit_vector();

    w = w_;
    u = unit_vector(cross(lookat.up, w));

    v = cross(w, u);
  }

  Ray generate_ray(int x, int y) override;
};
