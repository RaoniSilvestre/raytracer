#include "camera/orthographic_camera.hpp"
#include "math/vector_3.hpp"
#include <iostream>

Ray OrthographicCamera::generate_ray(int x, int y) {
  std::cout << "Gerando raio para: " << x << ", " << y << std::endl;

  // Renomeamos para 'dir' e 'orig' para não conflitar com 'x' e 'y'
  Vector3 dir = Vector3(1.0f, 2.0f, 3.0f);
  Point3 orig = Point3{1.0f, 1.0f, 1.0f};

  return Ray(orig, dir);
}
