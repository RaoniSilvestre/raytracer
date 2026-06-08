#include "core/bounding_box.hpp"

bool BoundingBox::intersect_p(const Ray& r, [[maybe_unused]]double hit1, [[maybe_unused]]double hit2){
  double tl0, tl1, tl2;
  double th0, th1, th2;
  tl0 = (this->lower_limit.x() - r.origem.x())/r.direcao.x();
  tl1 = (this->lower_limit.y() - r.origem.y())/r.direcao.y();
  tl2 = (this->lower_limit.z() - r.origem.z())/r.direcao.z();

  th0 = (this->upper_limit.x() - r.origem.x())/r.direcao.x();
  th1 = (this->upper_limit.y() - r.origem.y())/r.direcao.y();
  th2 = (this->upper_limit.z() - r.origem.z())/r.direcao.z();

  double tclose0, tclose1, tclose2;
  double tfar0, tfar1, tfar2;

  tclose0 = std::fmin(tl0, th0);
  tclose1 = std::fmin(tl1, th1);
  tclose2 = std::fmin(tl2, th2);

  tfar0 = std::fmax(tl0, th0);
  tfar1 = std::fmax(tl1, th1);
  tfar2 = std::fmax(tl2, th2);

  double tclose, tfar;
  tclose = std::fmax(tclose0, std::fmin(tclose1, tclose2));
  tfar = std::fmin(tfar0, std::fmax(tfar1, tfar2));
  if(tclose < tfar){
    if(tfar < 0){
      return false;
    }
    hit1 = tclose;
    hit2 = tfar;
    return true;
  }
  else{
    return false;
  }
}

