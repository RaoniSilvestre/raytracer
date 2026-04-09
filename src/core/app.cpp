#include "app.hpp"
#include "core/background_color.hpp"
#include "core/film.hpp"
#include "core/look_at.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"
#include "object/sphere.hpp"
#include "object_factory.hpp"
#include "tinyxml2.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <sys/types.h>

std::unique_ptr<BackgroundColor> App::background = nullptr;
std::unique_ptr<Camera> App::camera = nullptr;

void App::parse(const RunningOptions &opts) {
  std::cout << "Lendo arquivo: " << opts.input << std::endl;
  tinyxml2::XMLDocument doc;

  tinyxml2::XMLError eResult = doc.LoadFile(opts.input.c_str());

  if (eResult != tinyxml2::XML_SUCCESS) {
    std::cerr << "Erro ao abrir o arquivo XML: " << eResult << std::endl;
    return;
  }

  std::cout << ">>> Iniciando parsing" << std::endl;

  auto rt3_xml = doc.RootElement();

  if (!rt3_xml) {
    std::cerr << "Root não encontrado" << std::endl;
    return;
  }

  std::cout << ">>> RootElement: " << rt3_xml->Value() << std::endl;

  auto film_xml = rt3_xml->FirstChildElement("film");
  auto camera_xml = rt3_xml->FirstChildElement("camera");
  auto lookat_xml = rt3_xml->FirstChildElement("lookat");

  assert(camera_xml != nullptr);
  assert(film_xml != nullptr);
  assert(lookat_xml != nullptr);

  auto film_ps = ObjectFactory::parse(film_xml);
  auto camera_ps = ObjectFactory::parse(camera_xml);
  auto lookat_ps = ObjectFactory::parse(lookat_xml);

  auto film = std::make_unique<Film>(film_ps);
  auto lookat = LookAt(lookat_ps);

  camera = Camera::make_camera(camera_ps, std::move(film), lookat);

  auto iter = rt3_xml->FirstChildElement("world_begin")->NextSiblingElement();

  assert(iter != nullptr);

  while (iter) {
    std::string tag_name = iter->Value();

    if (tag_name == "world_end") {
      std::cout << ">>> World end encontrado. Finalizando parsing."
                << std::endl;
      return;
    }

    std::cout << ">>> Indo para: " << tag_name << std::endl;

    auto it = dispatch_map.find(tag_name);
    if (it != dispatch_map.end()) {
      ParamSet ps = ObjectFactory::parse(iter);

      it->second(ps);
    } else {
      std::cout << ">>> Tag desconhecida: " << tag_name << std::endl;
    }

    iter = iter->NextSiblingElement();
  }
}

void App::render() {
  std::cout << ">>> Começando renderização\n";
  const u_int32_t Y_RES = camera->film->y_res;
  const u_int32_t X_RES = camera->film->x_res;

  auto s1 = Sphere(0.4f, Point3{0, 1, 5});
  auto s2 = Sphere(0.4f, Point3{1, 0, 100000});
  // auto s3 = Sphere(0.4f, Point3{-1, -1.5, 3.5});
  // auto s4 = Sphere(0.4f, Point3{-1, 2, 4.5});

  // <object type="sphere" radius="0.4" center="-1 0.5 5" />
  //       <object type="sphere" radius="0.4" center="1 -0.5 8" />
  //       <object type="sphere" radius="0.4" center="-1 -1.5 3.5" />

  for (u_int32_t j = Y_RES - 1; j > 0; j--) {
    const float y_proportion = float(j) / float(Y_RES);
    for (u_int32_t i = 0; i < X_RES; i++) {

      const float x_proportion = float(i) / float(X_RES);
      auto ray = camera->generate_ray(i, j);

      auto p = Point2{i, j};

      if (s1.intersect_p(ray)) {
        camera->film->write(p, Color{255.0f, 0.0f, 0.0f});
      } else if (s2.intersect_p(ray)) {
        camera->film->write(p, Color{255.0f, 0.0f, 0.0f});
      // } 
      // else if (s3.intersect_p(ray) || s4.intersect_p(ray)) {
        // camera->film->write(p, Color{255.0f, 0.0f, 0.0f});
      } else {
        auto bg = background->sampleUV(x_proportion, y_proportion);

        camera->film->write(p, bg);
      }
    }
  }
}

void App::run(const RunningOptions &opts) {
  App::parse(opts);
  App::render();
  camera->film->export_image();
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
