#pragma once
#include "core/primitive.hpp"
#include "core/shape.hpp"
#include <memory>
#include <string>

class GeometricPrimitive : public Primitive{
private:
    
    GeometricPrimitive(std::shared_ptr<Material> m, std::shared_ptr<Shape> s) : material{m}, geoshape{s} {}
    
    

    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> geoshape;

};