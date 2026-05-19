#pragma once

#include "generic_object.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <ostream>

class ParamSet {
private:
  std::unordered_map<std::string, std::shared_ptr<GenericObject>> map;

public:
  ParamSet() = default;
  /**
  * @throws std::out_of_range if the key is not found
  */
  template <typename T> const T &retrieve(const std::string &key) const {
    auto it = map.find(key);
    if (it == map.end()) {
      throw std::out_of_range("Chave não encontrada: " + key);
    }

    auto derivedPtr = std::dynamic_pointer_cast<ValueType<T>>(it->second);

    if (!derivedPtr) {
      throw std::runtime_error("Erro de tipo ao recuperar a chave: " + key);
    }

    return derivedPtr->value;
  }

  bool has(const std::string &key) const {
    auto it = map.find(key);
    return it != map.end();
  }

  // Necessário fazer desse jeito pra não ter aquele object slicing.
  // Se instanciar a genérica direto ai ele dá o slicing, mas como eu to
  // instanciando o ValueType e to criando o ponteiro pra o ValueType, ai ele
  // não faz o slicing.
  template <typename T> void insert(const std::string &key, T obj) {
    ValueType<T> value_obj = ValueType<T>(obj);
    map[key] = std::make_shared<ValueType<T>>(value_obj);
  }
  friend std::ostream& operator<<(std::ostream& os, const ParamSet &p){
    os << "Paramset Keys = { ";
    for(auto a :p.map){
      os << a.first << ", ";
    }
    os << "}";
    return os;
  }
  bool empty() { return this->map.empty(); }
};
