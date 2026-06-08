#include "primitive/aggregate_primitive.hpp"
#include "aggregates/aggregate_list.hpp"
#include "aggregates/aggregate_bvh.hpp"
#include <memory>
#include <utility>
void AggregatePrimitive::make_aggregate(const ParamSet& ps, Scene &s){
  auto type = ps.retrieve<std::string>("type");
  if(type == "list"){
    s.objects_aggregate = std::make_shared<AggregateList>(std::move(s.objects));
  }  
  else if(type == "bvh"){
    s.objects_aggregate = std::make_shared<AggregateBVH>(std::move(s.objects), ps.retrieve<size_t>("max_prim_per_node"));
  }
}