#pragma once

#include "core/primitive.hpp"

class Primitive;
class Surfel {
public:
  Point3 point;
  Vector3 norm;
  Vector3 outg;
  double t;
  const Primitive *primitive;
  // Point2 parametric;
  // const Primitive* prim = nullptr;
  void set_primitive(const Primitive *p) { primitive = p; }
  Surfel(const Point3 &p, const Vector3 &n, const Vector3 &o,
         double dist /*const Point2 &param,*/)
      : point{p}, norm{n}, outg{o},
        t{dist} /*parametric{param},*/ /*(prim{pr}*/ {}
};