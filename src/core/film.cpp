#include "film.hpp"
#include <fstream>
#include <iostream>

void Film::export_ppm(){
  const u_int32_t Y_RES = this->y_res;
  const u_int32_t X_RES = this->x_res;
  std::ofstream file(this->filename);
  file << "P3" << "\n";
  file << X_RES << " " << Y_RES << "\n";
  file << "255" << "\n";
  for(u_int32_t i = 0; i<Y_RES; i++){
    for(u_int32_t j=0; j<X_RES; j++){
      file << this->buffer[i][j];
    }
    file << "\n";
  }
  file.close();
}

void Film::export_image(){
  std::cout << ">>> Exportando imagem do tipo: " << this->img_type << "\n";
  if(this->img_type == "ppm"){
    export_ppm();
  }
}