#pragma once
#include "math/vector_3.hpp"
#include "core/ray.hpp"
#include <cmath>

struct BoundingBox{
  Point3 lower_limit;
  Point3 upper_limit;
  Point3 get_centroid() const{
    return 0.5*lower_limit+0.5*upper_limit;
  }
  friend BoundingBox unite(const BoundingBox& b1, const BoundingBox &b2){
    Point3 new_lower =
     {std::min(b1.lower_limit.x(), b2.lower_limit.x()), 
      std::min(b1.lower_limit.y(), b2.lower_limit.y()),
      std::min(b1.lower_limit.z(), b2.lower_limit.z())};
    Point3 new_upper =
    {std::max(b1.upper_limit.x(), b2.upper_limit.x()), 
      std::max(b1.upper_limit.y(), b2.upper_limit.y()),
      std::max(b1.upper_limit.z(), b2.upper_limit.z())};
    
    return {new_lower, new_upper};
  }
  bool intersect_p(const Ray& r, double &hit1, double &hit2) const;
};

