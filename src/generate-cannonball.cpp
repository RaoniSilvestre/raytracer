#include "math/vector_3.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <string>

using namespace std;

struct Point3m {
  double x;
  double y;
  double z;
};

struct Sphere {
  Point3m center;
  double radius;
  bool operator<(const Sphere &b) const {
    if (this->center.x != b.center.x) {
      return this->center.x < b.center.x;
    } else if (this->center.y != b.center.y) {
      return this->center.y < b.center.y;
    } else if (this->center.z != b.center.z) {
      return this->center.z < b.center.z;
    } else if (this->radius != b.radius) {
      return this->radius < b.radius;
    }
    return false;
  }
};
std::set<Sphere> sphereset;
void make_cannon(Sphere top, int currentcamada, int maxcamada) {
  if (currentcamada == maxcamada) {
    return;
  }
  if (sphereset.find(top) != sphereset.end()) {
    return;
  }
  sphereset.insert(top);

  make_cannon({{top.center.x - top.radius, top.center.y - top.radius * sqrt(2),
                top.center.z - top.radius},
               top.radius},
              currentcamada + 1, maxcamada);
  make_cannon({{top.center.x - top.radius, top.center.y - top.radius * sqrt(2),
                top.center.z + top.radius},
               top.radius},
              currentcamada + 1, maxcamada);
  make_cannon({{top.center.x + top.radius, top.center.y - top.radius * sqrt(2),
                top.center.z - top.radius},
               top.radius},
              currentcamada + 1, maxcamada);
  make_cannon({{top.center.x + top.radius, top.center.y - top.radius * sqrt(2),
                top.center.z + top.radius},
               top.radius},
              currentcamada + 1, maxcamada);

  cout << "<object type=\"sphere\" radius=\"" << top.radius << "\" center=\""
       << top.center.x << " " << top.center.y << " " << top.center.z
       << "\"/>\n";
}

int main(int argc, char **argv) {
  if (argc < 5) {
    cout
        << "modo de uso: generate <raio das esferas> <centro do topo da piramide x> <centro do topo da piramide y> <centro do topo da piramide z> \
        <quantidade de camadas>";
    return 0;
  }
  Point3m centro_topo = {stod(argv[2]), stod(argv[3]), stod(argv[4])};
  double raio = stod(argv[1]);
  Sphere top_og = {centro_topo, raio};
  int camadas = stoi(argv[5]);
  make_cannon(top_og, 0, camadas);
}