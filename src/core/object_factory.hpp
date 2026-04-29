#include "param_set.hpp"
#include "tinyxml2.h"
#include <functional>
#include <sys/stat.h>
#include <unordered_map>

class ObjectFactory {
public:
  // fn(XMLElement) -> Arc<GenericObject>
  using TagParser = std::function<ParamSet(tinyxml2::XMLElement *)>;

  static ParamSet parse(tinyxml2::XMLElement *tag);

private:
  static ParamSet parseFilm(tinyxml2::XMLElement *tag);
  static ParamSet parseBackground(tinyxml2::XMLElement *tag);
  static ParamSet parseLookAt(tinyxml2::XMLElement *tag);
  static ParamSet parseCamera(tinyxml2::XMLElement *tag);
  static ParamSet parseSphere(tinyxml2::XMLElement *tag);
  static ParamSet parseMaterial(tinyxml2::XMLElement *tag);
  static ParamSet parseIntegrator(tinyxml2::XMLElement *tag);

  static inline const std::unordered_map<std::string, TagParser>
      param_set_parser_map = {
          {"background", &ObjectFactory::parseBackground},
          {"film", &ObjectFactory::parseFilm},
          {"lookat", &ObjectFactory::parseLookAt},
          {"camera", &ObjectFactory::parseCamera},
          {"integrator", &ObjectFactory::parseIntegrator},
          {"object", &ObjectFactory::parseSphere},
          {"material", &ObjectFactory::parseMaterial},

  };
};
