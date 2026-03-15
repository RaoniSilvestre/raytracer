#pragma once

#include "core/background_color.hpp"
#include <string>
#include <vector>

class Film {
public:
  std::string type;
  std::string img_type;
  std::string filename;
  int x_res;
  int y_res;
  std::vector<std::vector<Color>> buffer;

  Film(const std::string &t, const std::string &i_type,
       const std::string &fname, int x, int y)
      : type(t), img_type(i_type), filename(fname), x_res(x), y_res(y),
        buffer(static_cast<size_t>(y),
               std::vector<Color>(static_cast<size_t>(x), Color{0, 0, 0})) {}
};
