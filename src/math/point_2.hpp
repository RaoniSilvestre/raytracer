#ifndef POINT2H
#define POINT2H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Point2 {
public:
  Point2() {}
  Point2(double e0, double e1) {
    e[0] = e0;
    e[1] = e1;
  }
  inline double x() const { return e[0]; }
  inline double y() const { return e[1]; }
  inline double u() const { return e[0]; }
  inline double v() const { return e[1]; }

  inline const Point2 &operator+() const { return *this; }
  inline Point2 operator-() const { return Point2(-e[0], -e[1]); }
  inline double operator[](int i) const { return e[i]; }
  inline double &operator[](int i) { return e[i]; }

  inline Point2 &operator+=(const Point2 &v2);
  inline Point2 &operator-=(const Point2 &v2);
  inline Point2 &operator*=(const Point2 &v2);
  inline Point2 &operator/=(const Point2 &v2);
  inline Point2 &operator*=(const double t);
  inline Point2 &operator/=(const double t);

  inline double length() const { return sqrt(e[0] * e[0] + e[1] * e[1]); }
  inline double squared_length() const { return e[0] * e[0] + e[1] * e[1]; }
  inline void make_unit_vector();

  double e[2];
};

inline std::istream &operator>>(std::istream &is, Point2 &t) {
  is >> t.e[0] >> t.e[1];
  return is;
}

inline std::ostream &operator<<(std::ostream &os, const Point2 &t) {
  os << t.e[0] << " " << t.e[1];
  return os;
}

inline void Point2::make_unit_vector() {
  double k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1]);
  e[0] *= k;
  e[1] *= k;
}

inline Point2 operator+(const Point2 &v1, const Point2 &v2) {
  return Point2(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
}

inline Point2 operator-(const Point2 &v1, const Point2 &v2) {
  return Point2(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
}

inline Point2 operator*(const Point2 &v1, const Point2 &v2) {
  return Point2(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1]);
}

inline Point2 operator/(const Point2 &v1, const Point2 &v2) {
  return Point2(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1]);
}

inline Point2 operator*(double t, const Point2 &v) {
  return Point2(t * v.e[0], t * v.e[1]);
}

inline Point2 operator/(Point2 v, double t) {
  return Point2(v.e[0] / t, v.e[1] / t);
}

inline Point2 operator*(const Point2 &v, double t) {
  return Point2(t * v.e[0], t * v.e[1]);
}

inline double dot(const Point2 &v1, const Point2 &v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1];
}

inline Point2 &Point2::operator+=(const Point2 &v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  return *this;
}

inline Point2 &Point2::operator*=(const Point2 &v) {
  e[0] *= v.e[0];
  e[1] *= v.e[1];
  return *this;
}

inline Point2 &Point2::operator/=(const Point2 &v) {
  e[0] /= v.e[0];
  e[1] /= v.e[1];
  return *this;
}

inline Point2 &Point2::operator-=(const Point2 &v) {
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  return *this;
}

inline Point2 &Point2::operator*=(const double t) {
  e[0] *= t;
  e[1] *= t;
  return *this;
}

inline Point2 &Point2::operator/=(const double t) {
  double k = 1.0f / t;

  e[0] *= k;
  e[1] *= k;
  return *this;
}

inline Point2 unit_vector(const Point2 &v) { return v / v.length(); }

using Point3 = Point2;

#endif
