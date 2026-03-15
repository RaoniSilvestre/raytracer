#include "object_factory.hpp"
#include "core/background_color.hpp"
#include "tinyxml2.h"
#include <stdexcept>
#include <string>

ParamSet ObjectFactory::parse(tinyxml2::XMLElement *tag) {
  if (!tag) {
    throw std::runtime_error("Tag XML nula fornecida ao parser.");
  }

  std::string tag_name = tag->Value();

  auto it = map.find(tag_name);

  if (it != map.end()) {
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

  const char *x_res_ptr = tag->Attribute("x_res");
  const char *y_res_ptr = tag->Attribute("y_res");
  const char *filename_ptr = tag->Attribute("filename");
  const char *img_type_ptr = tag->Attribute("img_type");

  if (!x_res_ptr || !y_res_ptr || !filename_ptr || !img_type_ptr) {
    throw std::runtime_error("Atributos obrigatórios (x_res, y_res, filename "
                             "ou img_type) faltando em Film.");
  }

  int x_res, y_res;

  try {
    x_res = std::stoi(x_res_ptr);
    y_res = std::stoi(y_res_ptr);

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
  const char *type_attr = tag->Attribute("type");
  if (!type_attr || std::string(type_attr) != "colors") {
    throw std::runtime_error("Tipo de background deve ser 'colors'.");
  }

  const char *color_str = tag->Attribute("color");

  if (color_str) {
    ps.insert("color", Color::parseColorString(color_str));
  } else {
    const char *bl = tag->Attribute("bl");
    const char *tl = tag->Attribute("tl");
    const char *tr = tag->Attribute("tr");
    const char *br = tag->Attribute("br");

    if (bl && tl && tr && br) {
      ps.insert("bl", Color::parseColorString(bl));
      ps.insert("tl", Color::parseColorString(tl));
      ps.insert("tr", Color::parseColorString(tr));
      ps.insert("br", Color::parseColorString(br));
    } else {
      throw std::runtime_error("Background deve ter ou o atributo 'color' ou "
                               "os quatro cantos (bl, tl, tr, br).");
    }
  }

  const char *mapping = tag->Attribute("mapping");
  ps.insert("mapping", std::string(mapping ? mapping : "screen"));

  return ps;
}
