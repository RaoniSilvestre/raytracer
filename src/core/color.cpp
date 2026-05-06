
#include "core/background_color.hpp"
#include <sstream>
#include <stdexcept>

Color Color::parseColorString(const char *color_str) {
  if (!color_str) {
    throw std::runtime_error("String de cor nula.");
  }

  std::stringstream ss(color_str);
  double r, g, b;

  if (!(ss >> r >> g >> b)) {
    throw std::runtime_error("Formato de cor inválido. Esperado 'r g b'.");
  }

  if (r < 0.0 || g < 0.0 || b < 0.0) {
    throw std::runtime_error("Valores de cor não podem ser negativos.");
  }

  // Se todos os valores forem <= 1.0, assume que vieram normalizados e converte
  // para 0-255
  if (r > 1.0 && g > 1.0 && b > 1.0) {
    r /= 255.0;
    g /= 255.0;
    b /= 255.0;
  }

  if (r > 1 || g > 1 || b > 1) {
    throw std::runtime_error("Valores de cor fora do intervalo suportado.");
  }

  return Color{r, g, b};
}

double Color::interpolate(const double a, const double b, double t){
  return a * (1.0f - t) + b * t;
}
Color Color::interpolate(const Color &a, const Color &b, double t) {
  return {a.red * (1.0f - t) + b.red * t, 
          a.green * (1.0f - t) + b.green * t,
          a.blue * (1.0f - t) + b.blue * t};
}