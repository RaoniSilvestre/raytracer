

#include "camera/orthographic_camera.hpp"
#include "camera/perspective_camera.hpp"
#include "core/app.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// camera.cpp
std::unique_ptr<Camera> Camera::make_camera(const ParamSet &ps,
                                            std::unique_ptr<Film> film,
                                            LookAt lookat) {
  auto type = ps.retrieve<std::string>("type");

  if (type == "orthographic") {
    std::vector<double> sw = ps.retrieve<std::vector<double>>("screen_window");
    std::cout << ">>> Câmera ortográfica inicializada" << std::endl;
    return std::make_unique<OrthographicCamera>(lookat, sw, film);
  }
  else if(type == "perspective"){
    // try{
    //   std::vector<double> sw = ps.retrieve<std::vector<double>>("screen_window");
    //   std::cout << ">>> Câmera perspectiva inicializada com Screen Window" << "\n";  
    //   return std::make_unique<PerspectiveCamera>(lookat, sw, film);
    // } 
    // catch(std::runtime_error){
      double fovy = ps.retrieve<double>("fovy");
      std::cout << ">>> Câmera perspectiva inicializada com FOVy" << "\n";
      return std::make_unique<PerspectiveCamera>(lookat, fovy, film);
    // }
  }

  throw std::runtime_error("Paramset com tipo de camera inválido");
}
