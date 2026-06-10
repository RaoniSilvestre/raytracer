#include "aggregates/aggregate_bvh.hpp"
#include "core/primitive.hpp"
#include "math/vector_3.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <optional>
#include <vector>

size_t skipcount = 0;

std::vector<std::unique_ptr<Primitive>>* AggregateBVH::BVHNode::objectsptr = nullptr;

bool AggregateBVH::intersect_p(const Ray &r) const{
  auto s = intersect(r);
  return s.has_value();
}
std::optional<Surfel> AggregateBVH::intersect(const Ray &r) const{
  
  std::optional<Surfel> s = std::nullopt;
  double closest_t = std::numeric_limits<double>::infinity();

  BVHNode* nodes_to_visit[64];
  size_t stack_ptr = 0; 
  nodes_to_visit[stack_ptr++] = tree_root;
  while(stack_ptr > 0){
    double hit_t1 = 0., hit_t2 = 0.;
    BVHNode* tovisit = nodes_to_visit[--stack_ptr];
    if(tovisit != nullptr && tovisit->box_node.intersect_p(r, hit_t1, hit_t2)){
      if(hit_t1 > closest_t){
        continue;
      }
      else{
        if(tovisit->children[0] == nullptr){
          for(size_t i = tovisit->indx_begin; i < tovisit->indx_begin + tovisit->indx_count; i++){
            auto test_s = (*BVHNode::objectsptr)[i]->intersect(r);
            if(test_s && test_s->t < closest_t){
              s = test_s;
              closest_t = test_s->t;
            }
          }
        }
        else{
          nodes_to_visit[stack_ptr++] = (tovisit->children[1]);
          nodes_to_visit[stack_ptr++] = (tovisit->children[0]);
        }
      }
    }
  }
  return s;
}
const Material *AggregateBVH::get_material() const{
  throw(std::runtime_error("Cannot call get_material from an aggregate"));
}
size_t biggest_axis_in_vec(const Vector3 &v){
  size_t maxindx = 0;
  double maxval = v.e[0];
  for (size_t i = 1; i < 3; i++) {
    if (v.e[i] > maxval) {
      maxval = v.e[i];
      maxindx = i;
    }
  }
  return maxindx;
}

bool x_axis_index_cmp(const std::unique_ptr<Primitive> &a, const std::unique_ptr<Primitive> &b){
  return a.get()->get_bounding_box().get_centroid().x() < 
         b.get()->get_bounding_box().get_centroid().x();
}
bool y_axis_index_cmp(const std::unique_ptr<Primitive> &a, const std::unique_ptr<Primitive> &b){
  return a.get()->get_bounding_box().get_centroid().y() < 
         b.get()->get_bounding_box().get_centroid().y();
}
bool z_axis_index_cmp(const std::unique_ptr<Primitive> &a, const std::unique_ptr<Primitive> &b){
  return a.get()->get_bounding_box().get_centroid().z() < 
         b.get()->get_bounding_box().get_centroid().z();
}

void AggregateBVH::construct_tree(BVHNode* b){
  constexpr bool (*axis_index_cmp[3])(const std::unique_ptr<Primitive>&, const std::unique_ptr<Primitive>&) 
               = {x_axis_index_cmp, y_axis_index_cmp, z_axis_index_cmp};
  if(b->indx_count <= max_prims_per_node){
    return;
  }
  const auto cmp_func = axis_index_cmp[biggest_axis_in_vec(b->box_node.upper_limit-b->box_node.lower_limit)];
  std::sort((*b->objectsptr).data() + b->indx_begin, (*b->objectsptr).data()+(b->indx_begin + b->indx_count), cmp_func);

  const size_t mid_floor = static_cast<size_t>(std::floor(static_cast<double>(b->indx_count)/static_cast<double>(2)));
  const size_t mid_ceil = static_cast<size_t>(std::ceil(static_cast<double>(b->indx_count)/static_cast<double>(2)));
  b->children[0] = new BVHNode(b->indx_begin, mid_floor);
  b->children[1] = new BVHNode(b->indx_begin+mid_floor, mid_ceil);
  construct_tree(b->children[0]);
  construct_tree(b->children[1]);
}

AggregateBVH::BVHNode::BVHNode(size_t begin, size_t count){
  this->indx_begin=begin;
  this->indx_count = count;
  this->box_node = (*objectsptr)[begin]->get_bounding_box();
  for (size_t i = indx_begin+1; i<indx_begin+count; i++) {
    this->box_node = unite((*objectsptr)[i]->get_bounding_box(), this->box_node);
  }
  children[0] = nullptr;
  children[1] = nullptr;
}

AggregateBVH::BVHNode::BVHNode(std::vector<std::unique_ptr<Primitive>> &obj){
  BVHNode::objectsptr = &obj;
  indx_begin = 0;
  indx_count = obj.size();
  this->box_node = obj[0]->get_bounding_box();
  for (size_t i = indx_begin+1; i<indx_count; i++) {
    this->box_node = unite(obj[i]->get_bounding_box(), this->box_node);
  }
  children[0] = nullptr;
  children[1] = nullptr;
}
