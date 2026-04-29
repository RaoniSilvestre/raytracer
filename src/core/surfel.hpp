#pragma once

#include "core/primitive.hpp"

class Primitive;
class Surfel{
public:
    Point3 point;
    Vector3 norm;
    Vector3 outg;
    // Point2 parametric;
    // const Primitive* prim = nullptr;

    Surfel(const Point3 &p, const Vector3 &n,
           const Vector3 &o /*const Point2 &param,*/ /*const Primitive* pr*/)
           : point{p}, norm{n}, outg{o} /*parametric{param},*/ /*(prim{pr}*/{}

};