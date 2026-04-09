#include "../math/vector_3.hpp"
#include <cmath>

class Ray {
public:
  Point3 origem;
  Vector3 direcao;
  mutable float start, end;

  Ray(const Point3 &o, const Vector3 &d, float s = 0, float e = INFINITY) {
    origem = o;
    direcao = d;
    start = s;
    end = e;
  }

  friend std::ostream &operator<<(std::ostream &os, const Ray &r) {
    os << "Ray(orig: [" << r.origem << "], "
       << "dir: [" << r.direcao << "], "
       << "t: [" << r.start << ", "
       << (r.end == INFINITY ? "INF" : std::to_string(r.end)) << "])";
    return os;
  }

  Ray() : origem{0, 0, 0}, direcao{0, 0, 1}, start{0.f}, end{INFINITY} {}

  Point3 operator()(float t) const { return origem + direcao * t; }

  float min_t() const { return start; }
  float max_t() const { return end; }
};
