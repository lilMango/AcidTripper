#include "VecMatrix4.h"

class Plane{
 private:
  Vector3 point;
  Vector3 normal;
  
 public:

  Plane(){};
  ~Plane(){};
  
  void setNormal(Vector3 n){
    this->normal = n;
  }
  void setPoint(Vector3 p){
    this->point= p;
  }

  double distance(Vector3 x){
    return (x-point).dot(normal);
  }
  
};//end class Plane
