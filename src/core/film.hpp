#pragma once

#include "core/background_color.hpp"
#include "core/param_set.hpp"
#include <cstddef>
#include <string>
#include <sys/types.h>

struct Point2 {
  u_int32_t i;
  u_int32_t j;
};

class Film {
public:
  std::string type;
  std::string img_type;
  std::string filename;
  u_int32_t x_res;
  u_int32_t y_res;
  unsigned char *buffer;
  size_t buffer_size;

  void export_image();
  Film(const ParamSet &ps);

  Film(const std::string &t, const std::string &i_type,
       const std::string &fname, u_int32_t x, u_int32_t y) {
    type = t;
    img_type = i_type;
    filename = fname;
    x_res = x;
    y_res = y;

    buffer_size = static_cast<size_t>(y) * static_cast<size_t>(x) * 4;
    buffer = new unsigned char[buffer_size];
  }

  void write(Point2 p, Color c);

private:
  void export_ppm();
  bool export_png();
  void write_buffer_row(u_int32_t work_id, u_int32_t thread_count,
                        unsigned char *export_buffer, u_int32_t Y_RES,
                        u_int32_t X_RES);
};
