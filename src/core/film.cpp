#include "film.hpp"
#include "../lib/lodepng/lodepng.h"
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <vector>

void Film::export_ppm() {
  const u_int32_t Y_RES = this->y_res;
  const u_int32_t X_RES = this->x_res;
  std::ofstream file(this->filename);
  file << "P3" << "\n";
  file << X_RES << " " << Y_RES << "\n";
  file << "255" << "\n";
  for (u_int32_t i = 0; i < Y_RES; i++) {
    for (u_int32_t j = 0; j < X_RES; j++) {
      file << this->buffer[i][j];
    }
    file << "\n";
  }
  file.close();
}

bool Film::export_png() {
  const u_int32_t Y_RES = this->y_res;
  const u_int32_t X_RES = this->x_res;
  std::vector<unsigned char> export_buffer;
  export_buffer.reserve(X_RES * Y_RES * 4);

  for (u_int32_t i = Y_RES - 1; i >= 0 && i < 1000000; i--) {
    for (u_int32_t j = 0; j < X_RES; j++) {
      export_buffer.push_back(this->buffer[i][j].red_int());
      export_buffer.push_back(this->buffer[i][j].green_int());
      export_buffer.push_back(this->buffer[i][j].blue_int());
      export_buffer.push_back(255);
    }
  }
  return lodepng::encode(this->filename, export_buffer.data(), X_RES, Y_RES) ==
         0;
}

void Film::export_image() {
  std::cout << ">>> Exportando imagem do tipo: " << this->img_type << "\n";
  if (this->img_type == "ppm") {
    export_ppm();
  } else if (this->img_type == "png") {
    bool worked = export_png();
    if (!worked) {
      std::cout << ">>> Erro na exportação da imagem png";
    }
  }
}

Film::Film(const ParamSet &ps) {
  u_int32_t _x_res = ps.retrieve<u_int32_t>("x_res");
  u_int32_t _y_res = ps.retrieve<u_int32_t>("y_res");
  std::string _type = ps.retrieve<std::string>("type");
  std::string _filename = ps.retrieve<std::string>("filename");
  std::string _img_type = ps.retrieve<std::string>("img_type");

  std::cout << ">>> Film initialized: " << _x_res << "x" << _y_res
            << " target: " << _filename << std::endl;

  x_res = _x_res;
  y_res = _y_res;
  type = _type;
  filename = _filename;
  img_type = _img_type;

  buffer.assign(static_cast<size_t>(y_res),
                std::vector<Color>(static_cast<size_t>(x_res), Color{0, 0, 0}));
}

void Film::write(Point2 p, Color c) { buffer.at(p.j).at(p.i) = c; }
