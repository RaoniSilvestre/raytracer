#include "aggregates/aggregate_bvh.hpp"
#include "math/vector_3.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <optional>

const std::vector<std::unique_ptr<Primitive>>* AggregateBVH::BVHNode::objectsptr = nullptr;

bool AggregateBVH::intersect_p(const Ray &r) const{
  auto s = intersect(r);
  return s.has_value();
}
std::optional<Surfel> AggregateBVH::intersect(const Ray &r) const{
  
  std::optional<Surfel> s = std::nullopt;
  double closest_t = std::numeric_limits<double>::infinity();

  std::vector<BVHNode*> nodes_to_visit; 
  nodes_to_visit.push_back(tree_root);
  while(!nodes_to_visit.empty()){
    double hit_t1 = 0., hit_t2 = 0.;
    BVHNode* tovisit = nodes_to_visit.back();
    nodes_to_visit.pop_back();
    if(tovisit != nullptr && tovisit->box_node.intersect_p(r, hit_t1, hit_t2)){
      if(tovisit->children[0] == nullptr){
        for(size_t i = 0; i < max_prims_per_node; i++){
          auto test_s = (*BVHNode::objectsptr)[tovisit->indexes[i]]->intersect(r);
          if(test_s && test_s->t < closest_t){
            s = test_s;
            closest_t = test_s->t;
          }
        }
      }
      else{
        // if(hit_t1 > closest_t){
        //   continue;
        // }
        nodes_to_visit.push_back(tovisit->children[1]);
        nodes_to_visit.push_back(tovisit->children[0]);
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

bool x_axis_index_cmp(const size_t a, const size_t b){
  return (*AggregateBVH::BVHNode::objectsptr)[a]->get_bounding_box().get_centroid().x() < 
         (*AggregateBVH::BVHNode::objectsptr)[b]->get_bounding_box().get_centroid().x();
}
bool y_axis_index_cmp(const size_t a, const size_t b){
  return (*AggregateBVH::BVHNode::objectsptr)[a]->get_bounding_box().get_centroid().y() < 
         (*AggregateBVH::BVHNode::objectsptr)[b]->get_bounding_box().get_centroid().y();
}
bool z_axis_index_cmp(const size_t a, const size_t b){
  return (*AggregateBVH::BVHNode::objectsptr)[a]->get_bounding_box().get_centroid().z() < 
         (*AggregateBVH::BVHNode::objectsptr)[b]->get_bounding_box().get_centroid().z();
}

void AggregateBVH::construct_tree(BVHNode* b){
  constexpr bool (*axis_index_cmp[3])(const size_t, const size_t) = {x_axis_index_cmp, y_axis_index_cmp, z_axis_index_cmp};
  if(b->indexes.size() <= max_prims_per_node){
    return;
  }
  const auto cmp_func = axis_index_cmp[biggest_axis_in_vec(b->box_node.get_centroid())];
  std::sort(b->indexes.begin(), b->indexes.end(), cmp_func);

  const size_t vec_size = b->indexes.size();
  const size_t mid = vec_size/2;
  size_t mid_more = mid;
  size_t mid_less = mid;
  
  if(mid < max_prims_per_node){
    mid_more += max_prims_per_node-mid;
  }
  if(vec_size-mid < max_prims_per_node){
    mid_less -= (max_prims_per_node-(vec_size-mid));
  }
  b->children[0] = new BVHNode(b->indexes, 0ul, mid_more);
  b->children[1] = new BVHNode(b->indexes, mid_less, vec_size);
  construct_tree(b->children[0]);
  construct_tree(b->children[1]);
}

AggregateBVH::BVHNode::BVHNode(std::vector<size_t> &father_indexes, size_t begin, size_t end){
  
  indexes.reserve(end - begin);
  indexes.emplace_back(father_indexes[0]);
  this->box_node = (*objectsptr)[begin]->get_bounding_box();
  for (size_t i = begin+1; i<end; i++) {
    indexes.emplace_back(father_indexes[i]);
    this->box_node = unite((*objectsptr)[i]->get_bounding_box(), this->box_node);
  }
  children[0] = nullptr;
  children[1] = nullptr;
}

AggregateBVH::BVHNode::BVHNode(const std::vector<std::unique_ptr<Primitive>> &obj){
  BVHNode::objectsptr = &obj;
  indexes.reserve(obj.size());
  indexes.push_back(0);
  this->box_node = obj[0]->get_bounding_box();
  for (size_t i = 1; i<obj.size(); i++) {
    indexes.push_back(i);
    this->box_node = unite(obj[i]->get_bounding_box(), this->box_node);
  }
  children[0] = nullptr;
  children[1] = nullptr;
}
