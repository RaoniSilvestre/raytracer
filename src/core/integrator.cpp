#include "integrator/blinn_integrator.hpp"
#include "integrator/color_depth_integrator.hpp"
#include "integrator/depth_integrator.hpp"
#include "integrator/flat_integrator.hpp"
#include "integrator/normal_map_integrator.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

std::shared_ptr<Integrator>
Integrator::make_integrator(const ParamSet &ps, std::unique_ptr<Camera> c) {
  std::string integrator_type = ps.retrieve<std::string>("type");
  if (integrator_type == "flat") {
    std::cout << ">>> FlatIntegrator inicializado\n" << std::endl;
    return std::make_shared<FlatIntegrator>(std::move(c));
  } else if (integrator_type == "depth_map" || integrator_type == "depth") {
    double zmin, zmax;
    zmin = ps.retrieve<double>("zmin");
    zmax = ps.retrieve<double>("zmax");

    Color near(ps.retrieve<Color>("near_color")),
        far(ps.retrieve<Color>("far_color"));
    std::cout << ">>> DepthIntegrator inicializado\n" << std::endl;
    return std::make_shared<DepthIntegrator>(std::move(c), zmin, zmax, near,
                                             far);
  } else if (integrator_type == "color_depth") {
    double zmin, zmax;
    zmin = ps.retrieve<double>("zmin");
    zmax = ps.retrieve<double>("zmax");

    Color near(ps.retrieve<Color>("near_color")),
        far(ps.retrieve<Color>("far_color"));
    std::cout << ">>> ColorDepthIntegrator inicializado\n" << std::endl;
    return std::make_shared<ColorDepthIntegrator>(std::move(c), zmin, zmax,
                                                  near, far);
  } else if (integrator_type == "normal" || integrator_type == "normal_map") {
    return std::make_shared<NormalMapIntegrator>(std::move(c));
  } else if (integrator_type == "normal" || integrator_type == "normal_map") {
    return std::make_shared<NormalMapIntegrator>(std::move(c));
  } else if (integrator_type == "blinn" || integrator_type == "blinn_phong") {
    return std::make_shared<BlinnIntegrator>(std::move(c),
                                             ps.retrieve<int>("depth"));
  } else
    throw(std::runtime_error("Invalid integrator type"));
}
