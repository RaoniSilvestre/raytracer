#pragma once

#include "core/background_color.hpp"
#include "core/param_set.hpp"
#include <cstddef>
#include <string>
#include <sys/types.h>
#include <vector>

class Film {
public:
  std::string type;
  std::string img_type;
  std::string filename;
  u_int32_t x_res;
  u_int32_t y_res;
  std::vector<std::vector<Color>> buffer;

  void export_image();
  static std::unique_ptr<Film> make_film(const ParamSet &ps);

  Film(const std::string &t, const std::string &i_type,
       const std::string &fname, u_int32_t x, u_int32_t y) {
    type = t;
    img_type = i_type;
    filename = fname;
    x_res = x;
    y_res = y;
    buffer.assign(static_cast<size_t>(y),
                  std::vector<Color>(static_cast<size_t>(x), Color{0, 0, 0}));
  }

private:
  void export_ppm();
  bool export_png();
};
