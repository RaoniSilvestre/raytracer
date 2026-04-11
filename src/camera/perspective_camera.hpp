#include "core/app.hpp"
#include "math/vector_3.hpp"
#include <cstdlib>

class PerspectiveCamera : public Camera {
public:
  Vector3 m_u, m_v, m_w;
  Point3 m_origin;
  
  double m_fovy;
  double m_aspect_ratio;
  double m_focal_dist;

  double m_l, m_r, m_b, m_t;

  PerspectiveCamera(LookAt lookat, double fovy,
                     std::unique_ptr<Film> &_film, double focal_dist = 1)
      : Camera(std::move(_film)), m_fovy(fovy), m_focal_dist(focal_dist) {
    
    m_aspect_ratio = abs(static_cast<double>(film->x_res)/static_cast<double>(film->y_res));

    m_t = tan(deg_to_rad(m_fovy/2))*m_focal_dist;
    m_b = -m_t;
    m_r = m_aspect_ratio*m_t;
    m_l = -m_r;
    
    m_origin = lookat.look_from;
    
    m_w = unit_vector(lookat.look_at - lookat.look_from);
    m_u = unit_vector(cross(lookat.up, m_w));
    m_v = unit_vector(cross(m_u, m_w));

  }

  Ray generate_ray(u_int32_t x, u_int32_t y) override;    
private:
  /**
    Converts the given angle from degrees to double
  */
  double deg_to_rad(double deg);
};
