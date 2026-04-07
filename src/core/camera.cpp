

#include "camera/orthographic_camera.hpp"
#include "core/app.hpp"
#include <memory>
#include <string>
#include <vector>

// camera.cpp
std::unique_ptr<Camera> Camera::make_camera(const ParamSet &ps,
                                            std::unique_ptr<Film> film,
                                            LookAt lookat) {
  auto type = ps.retrieve<std::string>("type");

  if (type == "orthographic") {
    std::vector<float> sw = ps.retrieve<std::vector<float>>("screen_window");
    std::cout << ">>> Câmera ortográfica inicializada" << std::endl;
    return std::make_unique<OrthographicCamera>(lookat, sw, film);
  }

  throw std::runtime_error("Paramset com tipo de camera inválido");
}
