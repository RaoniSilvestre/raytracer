#include "param_set.hpp"
#include "tinyxml2.h"
#include <functional>
#include <set>
#include <sys/stat.h>
#include <unordered_map>

class ObjectFactory {
public:
  // fn(XMLElement) -> Arc<GenericObject>
  using TagParser = std::function<ParamSet(tinyxml2::XMLElement *)>;

  static ParamSet parse(tinyxml2::XMLElement *tag);

private:
  static inline const std::unordered_map<std::string, std::set<std::string>>
      valid_attributes = {
          {"film", {"type", "x_res", "y_res", "filename", "img_type"}},
          {"background", {"type", "color"}},
  };

  static ParamSet parseFilm(tinyxml2::XMLElement *object);
  static ParamSet parseBackground(tinyxml2::XMLElement *object);

  static inline const std::unordered_map<std::string, TagParser> map = {
      {"background", &ObjectFactory::parseBackground},
      {"film", &ObjectFactory::parseFilm},
  };
};
