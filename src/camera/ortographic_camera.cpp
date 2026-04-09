#include "camera/orthographic_camera.hpp"
#include "math/vector_3.hpp"

Ray OrthographicCamera::generate_ray(u_int32_t i, u_int32_t j) {

  auto u_coord = l + (r - l) * (static_cast<float>(i) + 0.5f) /
                         static_cast<float>(film->x_res);
  auto v_coord = b + (t - b) * (static_cast<float>(j) + 0.5f) /
                         static_cast<float>(film->y_res);

  Point3 orig = origin + (u * u_coord) + (v * v_coord);

  return Ray(orig, w);
}
