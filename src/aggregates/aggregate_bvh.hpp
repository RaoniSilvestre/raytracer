#pragma once

#include "core/primitive.hpp"
#include "primitive/aggregate_primitive.hpp"
#include <memory>
#include <utility>

class AggregateBVH : public AggregatePrimitive {
public:
  bool intersect_p(const Ray &r) const override;
  std::optional<Surfel> intersect(const Ray &r) const override;
  const Material *get_material() const override;

  void print_tree();

private:
  friend size_t biggest_axis_in_vec(const Vector3 &v);
  const std::vector<std::unique_ptr<Primitive>> &
  get_objects_list() const override {
    return objects;
  };
  std::vector<std::unique_ptr<Primitive>> objects;
  size_t max_prims_per_node;
  struct BVHNode {
  
    static std::vector<std::unique_ptr<Primitive>> *objectsptr;
    BoundingBox box_node;
    size_t indx_begin;
    size_t indx_count;
    BVHNode *children[2];
    BVHNode(size_t begin, size_t end);
    BVHNode(std::vector<std::unique_ptr<Primitive>> &obj);
  };

  friend bool x_axis_index_cmp(const size_t a, const size_t b);
  friend bool y_axis_index_cmp(const size_t a, const size_t b);
  friend bool z_axis_index_cmp(const size_t a, const size_t b);

  BVHNode *tree_root;
  void construct_tree(BVHNode *v);

public:
  AggregateBVH(std::vector<std::unique_ptr<Primitive>> &&v,
               size_t max_prims = 2)
      : objects(std::move(v)), max_prims_per_node(max_prims) {
    tree_root = new BVHNode(objects);
    construct_tree(tree_root);
  }
};
