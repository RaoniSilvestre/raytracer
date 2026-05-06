#include "shape/triangle.hpp"
#include "core/surfel.hpp"
#include "math/vector_3.hpp"
#include <optional>

bool Triangle::intersect_p(const Ray &r) const {
  if (dot(r.direcao, norm) < 0) {
    std::cout << "no_intersection because of the normal\n";
    return false;
  }
  double beta, gamma, t;
  double ei_minus_hf, gf_minus_di, dh_minus_eg, ak_minus_jb, jc_minus_al,
      bl_minus_kc;
  Vector3 Ad = this->A - this->B;
  Vector3 D = this->A - this->C;
  Vector3 G = r.direcao;
  Vector3 J = this->A - r.origem;

  ei_minus_hf = D.y() * G.z() - G.y() * D.z();
  gf_minus_di = G.x() * D.z() - D.x() * G.z();
  dh_minus_eg = D.x() * G.z() - D.y() * G.x();

  double M = Ad.x() * ei_minus_hf + Ad.y() * gf_minus_di + Ad.z() * dh_minus_eg;
  if (M <= 0) {
    return false;
  }

  beta = (J.x() * ei_minus_hf + J.y() * gf_minus_di + J.z() * dh_minus_eg) / M;
  if (beta < 0 || beta > 1) {
    return false;
  }
  ak_minus_jb = A.x() * J.y() - J.x() * A.y();
  jc_minus_al = J.x() * A.x() - A.x() * J.z();
  bl_minus_kc = A.y() * J.z() - J.y() * A.x();

  gamma =
      (Ad.x() * jc_minus_al + Ad.y() * bl_minus_kc + Ad.z() * ak_minus_jb) / M;
  if (gamma < 0 || gamma > 1) {
    return false;
  }

  if (beta + gamma > 1) {
    return false;
  }

  t = (Ad.x() * gf_minus_di + Ad.y() * dh_minus_eg + Ad.z() * ak_minus_jb) / M;
  if (t < 0) {
    return false;
  }
  return true;
}
std::optional<Surfel> Triangle::intersect(const Ray &r) const {
  std::optional<Surfel> retsurf = std::nullopt;

  // if (dot(r.direcao, norm) < 0) {
  //   std::cout << "no_intersection because of the normal\n";
  //   return retsurf;
  // }
  double beta, gamma, t;
  double ei_minus_hf, gf_minus_di, dh_minus_eg, ak_minus_jb, jc_minus_al,
      bl_minus_kc;
  Vector3 Ad = this->A - this->B;
  Vector3 D = this->A - this->C;
  Vector3 G = r.direcao;
  Vector3 J = this->A - r.origem;

  ei_minus_hf = D.y() * G.z() - G.y() * D.z();
  gf_minus_di = G.x() * D.z() - D.x() * G.z();
  dh_minus_eg = D.x() * G.z() - D.y() * G.x();

  double M = Ad.x() * ei_minus_hf + Ad.y() * gf_minus_di + Ad.z() * dh_minus_eg;
  if (M <= 0) {
    return retsurf;
  }
  beta = (J.x() * ei_minus_hf + J.y() * gf_minus_di + J.z() * dh_minus_eg) / M;
  if (beta < 0 || beta > 1) {
    return retsurf;
  }
  ak_minus_jb = A.x() * J.y() - J.x() * A.y();
  jc_minus_al = J.x() * A.x() - A.x() * J.z();
  bl_minus_kc = A.y() * J.z() - J.y() * A.x();

  gamma =
      (Ad.x() * jc_minus_al + Ad.y() * bl_minus_kc + Ad.z() * ak_minus_jb) / M;
  if (gamma < 0 || gamma > 1) {
    return retsurf;
  }

  if (beta + gamma > 1) {
    return retsurf;
  }

  t = (Ad.x() * gf_minus_di + Ad.y() * dh_minus_eg + Ad.z() * ak_minus_jb) / M;
  if (t < 0) {
    return retsurf;
  }
  Vector3 outg = r.direcao - 2 * (dot(r.direcao, norm)) * norm;
  retsurf = Surfel(r(t), norm, outg, t);
  return retsurf;
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
}

bool Triangle::is_degenerate() {
  return norm.x() == 0. && 
  norm.y() == 0. && 
  norm.z() == 0.;
}