#include "film.hpp"
#include "../lib/lodepng/lodepng.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <vector>


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

bool Film::export_png(){
    const u_int32_t Y_RES = this->y_res;
    const u_int32_t X_RES = this->x_res;
    std::vector<unsigned char> export_buffer(Y_RES*X_RES*4); 
    for(u_int32_t i=0;i<Y_RES;i++){
        for(u_int32_t j=0;j<X_RES;j++){
            for(int c=0;c<4;c++){
                uint8_t export_color;
                if(c==0){
                    export_color = this->buffer[i][j].red_int();
                }
                else if(c==1){
                    export_color = this->buffer[i][j].green_int();
                }
                else if(c==2){
                    export_color = this->buffer[i][j].blue_int();
                }
                else{
                    export_color = 255;
                }
                export_buffer.push_back(export_color);
            }
        }
    }
    return lodepng::encode(this->filename, export_buffer.data(), X_RES, Y_RES) == 0;

}

void Film::export_image(){
  std::cout << ">>> Exportando imagem do tipo: " << this->img_type << "\n";
  if(this->img_type == "ppm"){
    export_ppm();
  }
  else if(this->img_type == "png"){
    bool worked = export_png();
    if(!worked){
        std::cout << ">>> Erro na exportação da imagem png";
    }
  }
}