#include "object_factory.hpp"
#include "core/background_color.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

ParamSet ObjectFactory::parse(tinyxml2::XMLElement *tag) {
  if (!tag) {
    throw std::runtime_error("Tag XML nula fornecida ao parser.");
  }

  std::string tag_name = tag->Value();

  auto it = param_set_parser_map.find(tag_name);

  if (it != param_set_parser_map.end()) {
    return it->second(tag);
  } else {
    throw std::runtime_error("Tag desconhecida encontrada no XML: " + tag_name);
  }
}

ParamSet ObjectFactory::parseFilm(tinyxml2::XMLElement *tag) {
  if (!tag) {
    throw std::runtime_error("Tag XML nula fornecida ao parseFilm.");
  }

  const char *tag_name = tag->Value();
  if (std::string(tag_name) != "film") {
    throw std::runtime_error("Deveria ter sido chamado para um Film.");
  }

  auto ps = ParamSet();

  ps.insert("type", std::string(tag_name));

  const char *type_attr = tag->Attribute("type");
  if (!type_attr)
    throw std::runtime_error("Atributo 'type' faltando em Film.");

  std::string type(type_attr);
  if (type != "image") {
    throw std::runtime_error("Tipo para film deve ser 'image'.");
  }

  const char *x_res_ptr = tag->Attribute("w_res");
  const char *y_res_ptr = tag->Attribute("h_res");
  const char *filename_ptr = tag->Attribute("filename");
  const char *img_type_ptr = tag->Attribute("img_type");

  for (const tinyxml2::XMLAttribute *attr = tag->FirstAttribute();
       attr != nullptr; attr = attr->Next()) {
    const char *nome = attr->Name();
    const char *valor = attr->Value();

    std::cout << nome << ": " << valor << std::endl;
  }

  if (!x_res_ptr || !y_res_ptr || !filename_ptr || !img_type_ptr) {
    throw std::runtime_error("Atributos obrigatórios (x_res, y_res, filename "
                             "ou img_type) faltando em Film.");
  }

  u_int32_t x_res, y_res;

  try {
    x_res = static_cast<uint32_t>(std::stoul(x_res_ptr));
    y_res = static_cast<uint32_t>(std::stoul(y_res_ptr));

    if (x_res <= 0 || y_res <= 0) {
      throw std::runtime_error(
          "As resoluções x_res e y_res devem ser maiores que zero.");
    }

  } catch (const std::invalid_argument &e) {
    throw std::runtime_error(
        "Erro de formato: x_res ou y_res não são números válidos.");
  } catch (const std::out_of_range &e) {
    throw std::runtime_error(
        "Erro de valor: x_res ou y_res estão fora do limite de um inteiro.");
  }

  std::string filename(filename_ptr);
  std::string img_type(img_type_ptr);

  ps.insert("x_res", x_res);
  ps.insert("y_res", y_res);
  ps.insert("filename", filename);
  ps.insert("img_type", img_type);

  return ps;
}

ParamSet ObjectFactory::parseBackground(tinyxml2::XMLElement *tag) {
  if (!tag)
    throw std::runtime_error("Tag XML nula em parseBackground.");

  auto ps = ParamSet();
  std::string type_attr = std::string(tag->Attribute("type"));

  if (type_attr.empty()) {
    throw std::runtime_error("Tipo de background vazio.");
  }

  // Multiplas cores!
  if (type_attr == "colors") {
    const char *bl = tag->Attribute("bl");
    const char *tl = tag->Attribute("tl");
    const char *tr = tag->Attribute("tr");
    const char *br = tag->Attribute("br");

    if (bl && tl && tr && br) {
      ps.insert("type", "colors");
      ps.insert("bl", Color::parseColorString(bl));
      ps.insert("tl", Color::parseColorString(tl));
      ps.insert("tr", Color::parseColorString(tr));
      ps.insert("br", Color::parseColorString(br));

      return ps;
    } else {
      throw std::runtime_error("Background deve ter ou o atributo 'color' ou "
                               "os quatro cantos (bl, tl, tr, br).");
    }
  }

  // Uma cor só
  if (type_attr == "single_color") {
    const char *color_str = tag->Attribute("color");
    ps.insert("type", "single_color");
    ps.insert("color", Color::parseColorString(color_str));
    return ps;
  }

  throw std::runtime_error("Tipo de background não encontrado.");
}

Vector3 parseSingleString(const std::string &s) {
  std::stringstream ss(s);
  Vector3 v;
  ss >> v;
  return v;
}

ParamSet ObjectFactory::parseLookAt(tinyxml2::XMLElement *tag) {
  auto ps = ParamSet();

  auto look_at_str = tag->Attribute("look_at");
  auto look_from_str = tag->Attribute("look_from");
  auto up_str = tag->Attribute("up");

  if (!look_at_str || !look_from_str || !up_str) {
    throw std::runtime_error("Atributo obrigatório não encontrado em lookat");
  }

  auto look_at = parseSingleString(look_at_str);
  auto look_from = parseSingleString(look_from_str);
  auto up = parseSingleString(up_str);

  ps.insert("look_at", look_at);
  ps.insert("look_from", look_from);
  ps.insert("up", up);

  return ps;
}

ParamSet ObjectFactory::parseCamera(tinyxml2::XMLElement *tag) {
  auto ps = ParamSet();
  std::string type = std::string(tag->Attribute("type"));

  if (type == "orthographic") {
    ps.insert("type", type);
    auto screen_window_str = tag->Attribute("screen_window");

    if (!screen_window_str) {
      throw std::runtime_error(
          "Screen window da câmera orthografica não encontrado.");
    }

    std::vector<float> screen_window;
    std::stringstream ss(screen_window_str);
    float temp;

    while (ss >> temp) {
      screen_window.push_back(temp);
    }

    ps.insert("screen_window", screen_window);

    return ps;
  }

  throw std::runtime_error("Tipo de camera não implementado.");
}
