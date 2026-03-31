#include "app.hpp"
#include "core/film.hpp"
#include "object_factory.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>

std::unique_ptr<BackgroundColor> App::background = nullptr;
std::unique_ptr<Film> App::film = nullptr;

void App::process_tag(tinyxml2::XMLElement *element) {
  std::string tag_name = element->Value();

  auto it = dispatch_map.find(tag_name);
  if (it != dispatch_map.end()) {
    ParamSet ps = ObjectFactory::parse(element);

    it->second(ps);
  } else {
    std::clog << "Unknown tag: " << tag_name << std::endl;
  }
}

void App::parse(const RunningOptions &opts) {
  std::cout << "Lendo arquivo: " << opts.input << std::endl;
  tinyxml2::XMLDocument doc;

  tinyxml2::XMLError eResult = doc.LoadFile(opts.input.c_str());

  if (eResult != tinyxml2::XML_SUCCESS) {
    std::cerr << "Erro ao abrir o arquivo XML: " << eResult << std::endl;
    return;
  }

  auto root = doc.RootElement();

  if (!root) {
    std::cerr << "Root não encontrado" << std::endl;
    return;
  }

  auto element = root->FirstChildElement();

  std::unique_ptr<Film> film_ = nullptr;

  while (element) {
    std::string tag_name = element->Value();

    std::cout << ">>> Indo para: " << tag_name << std::endl;

    if (tag_name == "world_begin") {
      auto world_element = element->FirstChildElement();
      while (world_element) {
        process_tag(world_element);
        // salva o film pradepois
        // quando chega na camera
        // coloca o film dentro da camera
        world_element = world_element->NextSiblingElement();
      }
    } else if (tag_name == "world_end") {
      return;
    } else {
      process_tag(element);
    }

    element = element->NextSiblingElement();
  }
}

void App::render() {
  std::cout << ">>>Começando renderização\n";
  const u_int32_t Y_RES = film->y_res;
  const u_int32_t X_RES = film->x_res;
  for (u_int32_t i = 0; i < Y_RES; i++) {
    const float y_proportion = float(i) / float(Y_RES);
    for (u_int32_t j = 0; j < X_RES; j++) {
      const float x_proportion = float(j) / float(X_RES);
      film->buffer[i][j] = background->sampleUV(x_proportion, y_proportion);
    }
  }
}

void App::initialize() {
  if (!film || !camera) {
    throw new std::runtime_error("Camera ou filme não inicializados.");
  }

  camera->set_film(film);
}

void App::run(const RunningOptions &opts) {
  App::parse(opts);
  App::initialize();
  App::render();
  film->export_image();
}

void App::make_film(const ParamSet &ps) {
  int x_res = ps.retrieve<int>("x_res");
  int y_res = ps.retrieve<int>("y_res");
  std::string type = ps.retrieve<std::string>("type");
  std::string filename = ps.retrieve<std::string>("filename");
  std::string img_type = ps.retrieve<std::string>("img_type");

  App::film = std::make_unique<Film>(type, img_type, filename, x_res, y_res);

  std::cout << ">>> Film initialized: " << x_res << "x" << y_res
            << " target: " << filename << std::endl;
}

void App::make_background(const ParamSet &ps) {
  if (ps.has("color")) {
    Color c = ps.retrieve<Color>("color");
    App::background = std::make_unique<BackgroundColor>(c, c, c, c);
    std::cout << ">>> Background Solid Color initialized." << std::endl;
  } else {
    Color bl = ps.retrieve<Color>("bl");
    Color tl = ps.retrieve<Color>("tl");
    Color tr = ps.retrieve<Color>("tr");
    Color br = ps.retrieve<Color>("br");

    App::background = std::make_unique<BackgroundColor>(bl, br, tl, tr);
    std::cout << ">>> Background 4-Colors Interpolated initialized."
              << std::endl;
  }
}
