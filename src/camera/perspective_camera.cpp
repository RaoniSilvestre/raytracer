#include "camera/perspective_camera.hpp"
#include "math/vector_3.hpp"

Ray PerspectiveCamera::generate_ray(u_int32_t i, u_int32_t j) {
  double i_ = static_cast<double>(i);
  double j_ = static_cast<double>(j);
  double nx = static_cast<double>(film->x_res);
  double ny = static_cast<double>(film->y_res);

  double u = m_l + (m_r - m_l) * (i_ + 0.5f) / nx;
  double v = m_b + (m_t - m_b) * (j_ + 0.5f) / ny;

  Vector3 direction = m_focal_dist * m_w + u * m_u + v * m_v;

  return Ray(m_origin, direction);
}

double PerspectiveCamera::deg_to_rad(double deg) {
  return (M_PIf * deg) / 180.f;
}
