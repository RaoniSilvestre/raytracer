

#include "core/app.hpp"
class Primitive {
public:
  virtual ~Primitive() = default;
  virtual bool intersect_p(const Ray &r) const = 0;
};
