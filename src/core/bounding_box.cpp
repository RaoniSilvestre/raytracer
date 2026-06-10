#include "core/bounding_box.hpp"
#include <algorithm>
#include <limits>

bool BoundingBox::intersect_p(const Ray& r, double &hit0, double &hit1) const{
  double tmin = -std::numeric_limits<double>::infinity(), tmax = std::numeric_limits<double>::infinity();
  for(size_t i = 0;i<3;i++){
    double inv_dir = 1./r.direcao.e[i];
    double t0 = (lower_limit.e[i] - r.origem.e[i]) * inv_dir;
    double t1 = (upper_limit.e[i] - r.origem.e[i]) * inv_dir;
    if(inv_dir < 0.){
      std::swap(t0, t1);
    }
    tmin = std::max(tmin, t0);
    tmax = std::min(tmax, t1);
    
    if(tmin >= tmax){
      return false;
    }
  }
  hit0 = tmin;
  hit1 = tmax;
  return true;
}

