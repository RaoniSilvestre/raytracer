#pragma once

class ParamSet;

class GenericObject {
public:
  virtual ~GenericObject() = default;
};

template <typename T> class ValueType : public GenericObject {
public:
  T value;

  ValueType<T>(T val) : value(val) {}
};
