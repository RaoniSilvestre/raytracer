#include "app.hpp"
#include "core/background_color.hpp"
#include "core/film.hpp"
#include "core/integrator.hpp"
#include "core/look_at.hpp"
#include "core/param_set.hpp"
#include "object_factory.hpp"
#include "tinyxml2.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>

ParseReturn App::parse(const RunningOptions &opts, Scene &scene) {
  std::cout << "Lendo arquivo: " << opts.input << std::endl;
  tinyxml2::XMLDocument doc;

  tinyxml2::XMLError eResult = doc.LoadFile(opts.input.c_str());

  if (eResult != tinyxml2::XML_SUCCESS) {
    std::cerr << "Erro ao abrir o arquivo XML: " << eResult << std::endl;
    throw(std::runtime_error("Não foi possivel abrir XML"));
  }

  std::cout << ">>> Iniciando parsing" << std::endl;

  auto rt3_xml = doc.RootElement();

  if (!rt3_xml) {
    throw(std::runtime_error("Root não encontrado"));
  }

  std::cout << ">>> RootElement: " << rt3_xml->Value() << std::endl;

  auto film_xml = rt3_xml->FirstChildElement("film");
  auto camera_xml = rt3_xml->FirstChildElement("camera");
  auto lookat_xml = rt3_xml->FirstChildElement("lookat");
  auto integrator_xml = rt3_xml->FirstChildElement("integrator");

  assert(camera_xml != nullptr);
  assert(film_xml != nullptr);
  assert(lookat_xml != nullptr);
  assert(integrator_xml != nullptr);

  auto film_ps = ObjectFactory::parse(film_xml);
  auto camera_ps = ObjectFactory::parse(camera_xml);
  auto lookat_ps = ObjectFactory::parse(lookat_xml);
  auto integrator_ps = ObjectFactory::parse(integrator_xml);

  auto film = std::make_unique<Film>(film_ps);
  auto lookat = LookAt(lookat_ps);

  auto camera = Camera::make_camera(camera_ps, std::move(film), lookat);

  auto integrator =
      Integrator::make_integrator(integrator_ps, std::move(camera));
  auto iter = rt3_xml->FirstChildElement("world_begin")->NextSiblingElement();

  assert(iter != nullptr);

  while (iter) {
    std::string tag_name = iter->Value();

    if (tag_name == "world_end") {
      std::cout << ">>> World end encontrado. Finalizando parsing."
                << std::endl;
      return {integrator};
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
  return {integrator};
}

void App::render(const Scene &scene,
                 const std::shared_ptr<Integrator> integrator) {
  std::cerr << ">>> Começando renderização\n";
  const int Y_RES = static_cast<int>(integrator->camera->film->y_res);
  const int X_RES = static_cast<int>(integrator->camera->film->x_res);
  integrator->preprocess(scene);

  for (int j = Y_RES - 1; j >= 0; j--) {
    const double y_proportion = double(j) / double(Y_RES);
    for (int i = 0; i < X_RES; i++) {
      const double x_proportion = double(i) / double(X_RES);
      auto ray = integrator->camera->generate_ray(static_cast<u_int32_t>(i),
                                                  static_cast<u_int32_t>(j));
      auto p = Point2{static_cast<u_int32_t>(i), static_cast<u_int32_t>(j)};

      std::optional<Color> hit = integrator->li(ray, scene);

      if (hit) {
        integrator->camera->film->write(p, *hit);
      } else {
        auto bg = scene.background->sampleUV(x_proportion, y_proportion);
        integrator->camera->film->write(p, bg);
      }
    }
  }
}

void App::run(const RunningOptions &opts) {
  Scene scene;
  std::shared_ptr<Integrator> integrator;
  ParseReturn p;
  p = App::parse(opts, scene);
  integrator = p.integrator;
  App::render(scene, integrator);
  integrator->camera->film->export_image();
}
