#include "shape/triangle.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"
#include <optional>

bool Triangle::intersect_p(const Ray &r) const {
  return intersect(r) != std::nullopt;
}

constexpr double EPSILON = 1e-8;

std::optional<Surfel> Triangle::intersect(const Ray &r) const {
  // Eixo X nas coordenadas baricêntricas (Edge 1)
  Vector3 edge1 = B - A;
  // Eixo Y nas coordenadas baricêntricas (Edge 2)
  Vector3 edge2 = C - A;

  Vector3 pvec = cross(r.direcao, edge2);
  Vector3 tvec = r.origem - A;
  Vector3 qvec = cross(tvec, edge1);

  // Determinante a partir do produto misto
  //
  // Faz tipo um paralelogramo com os 3 vetores e gera o determinante (volume)
  // desse paralelogramo.
  double det = dot(edge1, pvec);

  // Divisões de crammer
  double beta = dot(tvec, pvec) / det;
  double gamma = dot(r.direcao, qvec) / det;
  double t = dot(edge2, qvec) / det;

  if (std::abs(det) < EPSILON) {
    return std::nullopt;
  }

  if (beta < 0.0 || beta > 1.0) {
    return std::nullopt;
  }

  if (gamma < 0.0 || beta + gamma > 1.0) {
    return std::nullopt;
  }

  if (t > EPSILON) {
    Vector3 outg = r.direcao - 2.0 * dot(r.direcao, norm) * norm;
    return Surfel(r(t), norm, outg, t);
  }

  return std::nullopt;
}

Triangle::Triangle(const ParamSet &ps) {
  auto Am = ps.retrieve<Point3>("A");
  auto Bm = ps.retrieve<Point3>("B");
  auto Cm = ps.retrieve<Point3>("C");

  this->A = Am;
  this->B = Bm;
  this->C = Cm;
  this->center = (Am + Bm + Cm) / 3.;
  norm =
      unit_vector(cross(Cm - Am, Bm - Am)); // the call parameters are reversed
                                            // to use a right hand cross product

  std::cout << "Construido um triângulo com A = " << A << ", B = " << B
            << ", C = " << C << " e Norm = " << norm << " center = " << center
            << std::endl;
}

bool Triangle::is_degenerate() {
  return norm.x() == 0. && norm.y() == 0. && norm.z() == 0.;
}
