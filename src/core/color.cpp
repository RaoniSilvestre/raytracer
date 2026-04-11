
#include "core/background_color.hpp"
#include <sstream>
#include <stdexcept>

Color Color::parseColorString(const char *color_str) {
  if (!color_str) {
    throw std::runtime_error("String de cor nula.");
  }

  std::stringstream ss(color_str);
  int r, g, b;

  if (!(ss >> r >> g >> b)) {
    throw std::runtime_error("Formato de cor inválido. Esperado 'r g b'.");
  }

  if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
    throw std::runtime_error("Valores de cor fora do intervalo [0, 255].");
  }

  return Color{static_cast<double>(r), static_cast<double>(g),
               static_cast<double>(b)};
}
