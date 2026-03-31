#include "../math/vector_3.hpp"
#include <cmath>

class Ray {
private:
  Point3 origem;
  Vector3 direcao;
  mutable float start, end;

public:
  Ray(const Point3 &o, const Vector3 &d, float s = 0, float e = INFINITY) {
    origem = o;
    direcao = d;
    start = s;
    end = e;
  }

  Ray() : origem{0, 0, 0}, direcao{0, 0, 1}, start{0.f}, end{INFINITY} {}

  Point3 operator()(float t) const { return origem + direcao * t; }

  float min_t() const { return start; }
  float max_t() const { return end; }
};
