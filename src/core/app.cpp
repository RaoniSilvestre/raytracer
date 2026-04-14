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

void App::parse(const RunningOptions &opts, Scene &scene) {
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

  scene.camera = Camera::make_camera(camera_ps, std::move(film), lookat);

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

      it->second(ps, scene);
    } else {
      std::cout << ">>> Tag desconhecida: " << tag_name << std::endl;
    }

    iter = iter->NextSiblingElement();
  }
}

void App::render(const Scene &scene) {
  const int Y_RES = static_cast<int>(scene.camera->film->y_res);
  const int X_RES = static_cast<int>(scene.camera->film->x_res);
  std::cerr << ">>> Começando renderização\n";

  for (int j = Y_RES - 1; j >= 0; j--) {
    const double y_proportion = (double(j) + 0.5) / double(Y_RES);
    for (int i = 0; i < X_RES; i++) {
      const double x_proportion = (double(i) + 0.5) / double(X_RES);
      auto ray = scene.camera->generate_ray(static_cast<u_int32_t>(i),
                                            static_cast<u_int32_t>(j));
      auto p = Point2{static_cast<u_int32_t>(i), static_cast<u_int32_t>(j)};

      bool hit = false;
      Color hit_color{0.0f, 0.0f, 0.0f};
      for (const auto &obj : scene.objects) {
        if (obj->intersect_p(ray)) {
          hit = true;
          hit_color = obj->get_material()->color;
          break;
        }
      }

      if (hit) {
        scene.camera->film->write(p, hit_color);
      } else {
        auto bg = scene.background->sampleUV(x_proportion, y_proportion);
        scene.camera->film->write(p, bg);
      }
    }
  }
}

void App::run(const RunningOptions &opts) {
  Scene scene;
  App::parse(opts, scene);
  App::render(scene);
  scene.camera->film->export_image();
}
