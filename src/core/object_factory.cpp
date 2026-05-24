#include "object_factory.hpp"
#include "core/color.hpp"
#include "core/param_set.hpp"
#include "math/vector_3.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/**
  Returns a ParamSet with the fields inside the XML element
  throws runtime_error with an invalid XML element
 */
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
  if (x_res_ptr == nullptr) {
    x_res_ptr = tag->Attribute("x_res");
  }
  if (y_res_ptr == nullptr) {
    y_res_ptr = tag->Attribute("y_res");
  }
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

  if (type_attr == "4_colors") {
    const char *bl = tag->Attribute("bl");
    const char *tl = tag->Attribute("tl");
    const char *tr = tag->Attribute("tr");
    const char *br = tag->Attribute("br");

    if (bl && tl && tr && br) {
      ps.insert("type", "4_colors");
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

    std::vector<double> screen_window;
    std::stringstream ss(screen_window_str);
    double temp;

    while (ss >> temp) {
      screen_window.push_back(temp);
    }

    ps.insert("screen_window", screen_window);

    return ps;
  } else if (type == "perspective") {
    ps.insert("type", type);
    auto screen_window = tag->Attribute("screen_window");
    auto fovyinput = tag->Attribute("fovy");
    auto frame_aspectratio = tag->Attribute("frame_aspectratio");

    std::vector<double> screen_window_vec;
    double fovy = 0.f;
    double aspect_ratio = 0.f;

    if (screen_window) {
      std::stringstream ss(screen_window);
      double temp;
      while (ss >> temp) {
        screen_window_vec.push_back(temp);
      }
      if (screen_window_vec.size() != 4) {
        screen_window = nullptr;
      } else {
        ps.insert("screen_window", screen_window_vec);
      }
    }
    if (fovyinput) {
      std::stringstream ss(fovyinput);
      if (!(ss >> fovy)) {
        fovyinput = nullptr;
      } else {
        ps.insert("fovy", fovy);
        if (frame_aspectratio) {
          std::stringstream fa_ss(frame_aspectratio);
          if (fa_ss >> aspect_ratio) {
            ps.insert("frame_aspectratio", aspect_ratio);
          }
        }
      }
    }
    if (!screen_window && !fovyinput) {
      throw std::runtime_error("Fovy e Screen Window não foram encontrados");
    }

    return ps;
  }
  throw std::runtime_error("Tipo de camera não implementado.");
}

ParamSet ObjectFactory::parseObject(tinyxml2::XMLElement *tag) {
  auto type = tag->Attribute("type");
  if (!type) {
    throw std::runtime_error("Tipo de objeto não encontrado");
  }

  auto type_ = std::string(type);
  ParamSet ps;
  ps.insert("type", type_);

  if (type_ == "sphere") {
    auto radius_raw = tag->Attribute("radius");
    auto center_raw = tag->Attribute("center");
    if (!radius_raw || !center_raw) {
      throw std::runtime_error("Sphere sem centro ou raio.");
    }
    auto center = parseSingleString(center_raw);
    double radius = std::stod(radius_raw);

    ps.insert("radius", radius);
    ps.insert("center", center);
  } else if (type_ == "triangle") {
    auto A_raw = tag->Attribute("a");
    auto B_raw = tag->Attribute("b");
    auto C_raw = tag->Attribute("c");
    if (!A_raw || !B_raw || !C_raw) {
      throw std::runtime_error("Triangle sem vértice A, B ou C.");
    }
    auto A = parseSingleString(A_raw);
    auto B = parseSingleString(B_raw);
    auto C = parseSingleString(C_raw);
    ps.insert("A", A);
    ps.insert("B", B);
    ps.insert("C", C);
  } else if (type_ == "plane") {
    auto point_raw = tag->Attribute("point");
    auto normal_raw = tag->Attribute("normal");

    if (!point_raw || !normal_raw) {
      throw std::runtime_error("Plano sem ponto ou vetor normal");
    }

    auto point = parseSingleString(point_raw);
    auto normal = parseSingleString(normal_raw);

    ps.insert("point", point);
    ps.insert("normal", normal);
  } else if (type_ == "trianglemesh") {
    // 1. Arquivo OBJ (geralmente o principal)
    auto filename_raw = tag->Attribute("filename");
    if (filename_raw) {
      ps.insert("filename", std::string(filename_raw));
    } else {
      // TODO: Caso não tenha filename, é pra pegar as coisas que teriam no .obj
      // pela tag.
      ps.insert("filename", std::string(""));
    }

    auto bfc_raw = tag->Attribute("backface_cull");
    if (bfc_raw) {
      ps.insert("backface_cull", std::string(bfc_raw));
    }

    auto rvo_raw = tag->Attribute("reverse_vertex_order");
    if (rvo_raw) {
      ps.insert("reverse_vertex_order", std::string(rvo_raw));
    }

    auto cn_raw = tag->Attribute("compute_normals");
    if (cn_raw) {
      ps.insert("compute_normals", std::string(cn_raw));
    }
  } else {
    throw std::runtime_error("Objeto não suportado.");
  }

  return ps;
}

ParamSet ObjectFactory::parseMaterial(tinyxml2::XMLElement *tag) {
  ParamSet ps;
  auto type_raw = tag->Attribute("type");

  if (!type_raw) {
    throw std::runtime_error("Material tipo válido");
  }
  auto type = std::string(type_raw);
  if (type == "flat") {
    auto color_raw = tag->Attribute("color");
    if (!color_raw) {
      throw std::runtime_error("Material sem cor válida");
    }
    auto color = Color::parseColorString(color_raw);
    ps.insert("color", color);
  } else if (type == "blinn") {
    auto ambient = Color::parseColorString(tag->Attribute("ambient"));
    auto diffuse = Color::parseColorString(tag->Attribute("diffuse"));
    auto specular = Color::parseColorString(tag->Attribute("specular"));
    auto glossiness = std::stod(tag->Attribute("glossiness"));
    auto mirror_raw = tag->Attribute("mirror");
    if (!mirror_raw)
      ps.insert("mirror", Color{0., 0., 0.});
    else {
      auto mirror = parseSingleString(mirror_raw);
      ps.insert("mirror", mirror);
    }

    ps.insert("glossiness", glossiness);
    ps.insert("ambient", ambient);
    ps.insert("diffuse", diffuse);
    ps.insert("specular", specular);
  }

  ps.insert("type", type);

  return ps;
}

ParamSet ObjectFactory::parseIntegrator(tinyxml2::XMLElement *tag) {
  ParamSet ps;
  std::string integratortype = tag->Attribute("type");
  ps.insert("type", integratortype);
  if (integratortype == "flat") {
  } else if (integratortype == "depth" || integratortype == "depth_map" ||
             integratortype == "color_depth") {
    double zmin, zmax;
    zmin = std::stod(tag->Attribute("zmin"));
    zmax = std::stod(tag->Attribute("zmax"));

    const char *near_string = tag->Attribute("near_color");
    const char *far_string = tag->Attribute("far_color");
    Color near(Color::parseColorString(near_string)),
        far(Color::parseColorString(far_string));
    ps.insert("zmin", zmin);
    ps.insert("zmax", zmax);
    ps.insert("near_color", near);
    ps.insert("far_color", far);

  } else if (integratortype == "normal_map" || integratortype == "normal") {
    // nothing to add
  } else if (integratortype == "blinn" || integratortype == "blinn_phong") {
    auto depth_raw = tag->Attribute("depth");
    int depth;
    if (!depth_raw) {
      std::cout << "No depth provided, defaulting to 3";
      depth = 3;
    } else {
      depth = std::stoi(depth_raw);
    }
    ps.insert("depth", depth);

  } else {
    throw(std::runtime_error("Invalid Integrator type"));
  }
  return ps;
}
ParamSet ObjectFactory::parseLight(tinyxml2::XMLElement *tag) {
  ParamSet ps;
  const char *type_raw = tag->Attribute("type");
  if (!type_raw) {
    throw std::runtime_error("Tipo não informado na luz");
  }
  std::string type(type_raw);
  Color intensity = Color::parseColorString(tag->Attribute("I")),
        scale = Color::parseColorString(tag->Attribute("scale"));
  if (type == "point" || type == "directional") {
    auto from = parseSingleString(tag->Attribute("from"));
    if (type == "directional") {
      auto to = parseSingleString(tag->Attribute("to"));
      ps.insert("to", to);
    }
    ps.insert("from", from);
  }
  ps.insert("intensity", intensity);
  ps.insert("scale", scale);
  ps.insert("type", type);
  return ps;
}

ParamSet ObjectFactory::parseNamedMaterial(tinyxml2::XMLElement *tag) {
  ParamSet ps;
  auto name_raw = tag->Attribute("name");
  if (!name_raw) {
    throw std::runtime_error("Nome do material inválido");
  }
  auto name = std::string(name_raw);
  ps.insert("name", name);

  return ps;
}
ParamSet ObjectFactory::parseMakeNamedMaterial(tinyxml2::XMLElement *tag) {
  ParamSet ps;
  auto type_raw = tag->Attribute("type");
  auto name_raw = tag->Attribute("name");
  if (!type_raw || !name_raw) {
    throw std::runtime_error("Material de tipo ou nome inválido");
  }
  auto type = std::string(type_raw);
  auto name = std::string(name_raw);
  ps.insert("type", type);
  ps.insert("name", name);
  if (type == "flat") {
    auto color_raw = tag->Attribute("color");
    if (!color_raw) {
      throw std::runtime_error("Material sem cor válida");
    }
    auto color = Color::parseColorString(color_raw);
    ps.insert("color", color);
  } else if (type == "blinn" || type == "blinn_phong") {
    auto ambient = Color::parseColorString(tag->Attribute("ambient"));
    auto diffuse = Color::parseColorString(tag->Attribute("diffuse"));
    auto specular = Color::parseColorString(tag->Attribute("specular"));
    auto glossiness = std::stod(tag->Attribute("glossiness"));
    auto mirror_raw = tag->Attribute("mirror");
    if (!mirror_raw)
      ps.insert("mirror", Color{0., 0., 0.});
    else {
      auto mirror = Color::parseColorString(mirror_raw);
      ps.insert("mirror", mirror);
    }
    ps.insert("ambient", ambient);
    ps.insert("glossiness", glossiness);
    ps.insert("diffuse", diffuse);
    ps.insert("specular", specular);
  }

  return ps;
}
