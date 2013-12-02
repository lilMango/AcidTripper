#pragma once
#define ANG2RAD 3.14159265/180.0
#include "Plane.h"
#include "VecMatrix4.h"

class Frustum{
 private:
  enum{
    TOP=0,BOTTOM,LEFT,RIGHT,NEARP,FARP
  };
  
 public:
  enum{OUTSIDE=-1, INTERSECT,INSIDE};
  
  Plane pl[6];
  Vector3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
  double nearD, farD, ratio, angle, tang;
  double nw, nh, fw,fh;

  Frustum();
  Frustum(double angle, double ratio, double nearD, double farD);
    
  ~Frustum(){};

  //stores same parameters as gluPerspective
  void setCamInternals(double angle, double ratio, double nearD,double farD);
  
  //store info form gluLookAt
  void setCamDef(Vector3 e, Vector3 d, Vector3 u);
  int pointInFrustum(Vector3 p);
  int sphereInFrustum(Vector3 p, double rad);
  //int boxInFrustum(int); //todo
  

};//end class Frustum
