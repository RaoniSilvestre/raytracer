#include "core/integrator.hpp"
#include "integrator/flat_integrator.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

std::shared_ptr<Integrator> Integrator::make_integrator(const ParamSet &ps, std::unique_ptr<Camera> c){
    std::string integrator_type = ps.retrieve<std::string>("type");
    if(integrator_type == "flat"){
        std::cout << ">>> FlatIntegrator inicializado\n" << std::endl;
        return std::make_shared<FlatIntegrator>(std::move(c));
    }
    else throw(std::runtime_error("Invalid integrator type"));
}