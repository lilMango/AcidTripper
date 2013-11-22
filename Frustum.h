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

  Frustum(){
    ratio=16.0/9.0;
    angle=90.0;
    nearD=10;
    farD=1000;

    
    //compute width and height of near and far plane sections
    tang = (double) tan(ANG2RAD * angle *.5);
    printf("FFEGGGE %3.4f\n",tang);
    nh = nearD* tang;
    nw = nh * ratio;
    fh = farD * tang;
    fw = fh * ratio;    
    /*
    //this produces same result if angle -- 90
    fh = 1000;
    fw = fh * ratio;
    nh = 10;
    nw = nh * ratio;
    */
  };
  ~Frustum(){};

  //stores same parameters as gluPerspective
  void setCamInternals(double angle, double ratio, double nearD,double farD);
  
  //store info form gluLookAt
  void setCamDef(Vector3 e, Vector3 d, Vector3 u);
  int pointInFrustum(Vector3 p);
  int sphereInFrustum(Vector3 p, double rad);
  //int boxInFrustum(int); //todo
  

};//end class Frustum
