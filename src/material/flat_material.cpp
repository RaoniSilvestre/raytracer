#include "material/flat_material.hpp"
#include "core/color.hpp"
#include "core/param_set.hpp"
#include <string>

Color FlatMaterial::get_color() const { return c; }

FlatMaterial::FlatMaterial(const ParamSet &ps) {
    this->c = ps.retrieve<Color>("color");
    this->type = ps.retrieve<std::string>("type");
}