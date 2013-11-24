#include "Frustum.h"

//Takes parameters of gluPerspective
void Frustum::setCamInternals(double angle, double ratio, double nearD, double farD){
  this->ratio=ratio;
  this->angle=angle;
  this->nearD = nearD;
  this->farD = farD;
  
  //compute width and height of near and far plane sections
  tang = (double) tan(ANG2RAD * angle *.5);
  printf("HEYO: %3.4f\n");
  nh = nearD* tang;
  nw = nh * ratio;
  fh = farD * tang;
  fw = fh * ratio;
}//end setCamInternals


//Takes parameters of gluLookAt
void Frustum::setCamDef(Vector3 e, Vector3 d, Vector3 up){
  Vector3 dir, nc, fc, X,Y,Z;
  Z = e - d;
  Z.normalize();
  
  X = Vector3();
  X.cross(up,Z);
  X.normalize();

  Y = Vector3();
  Y.cross(Z,X);

  //compute centers of near and far plane
  nc = e - Z*nearD;
  fc = e - Z*farD;


  //////////////////////
  //compute the 4 corners of the frustum on near plane
  ntl = nc + Y * nh - X * nw;
  ntr = nc + Y * nh + X * nw;
  nbl = nc - Y * nh - X * nw;
  nbr = nc - Y * nh + X * nw;
  
  //compute the 4 corners of the frustum on far plane
  ftl = fc + Y * fh - X * fw;
  ftr = fc + Y * fh + X * fw;
  fbl = fc - Y * fh - X * fw;
  fbr = fc - Y * fh + X * fw;

  /////////////////////////

  //TODO WHY ISN"T GREEN CIRCLES IN FRUSTUM
  pl[NEARP].setNormal(Z*(-1));
  pl[NEARP].setPoint(nc);
  
  pl[FARP].setNormal(Z);
  pl[FARP].setPoint(fc);

  Vector3 aux, normal,tmp;
  tmp= nc+Y*nh;
  aux = tmp - e;
  aux.normalize();
  normal = aux.cross( X);
  pl[TOP].setNormal(normal);
  pl[TOP].setPoint(tmp);

  tmp=nc-Y*nh;
  aux = tmp - e;
  aux.normalize();
  normal = X.cross( aux);
  pl[BOTTOM].setNormal(normal);
  pl[BOTTOM].setPoint(tmp);

  tmp= nc - X * nw;
  aux = tmp - e;
  aux.normalize();
  normal = aux.cross( Y);
  pl[LEFT].setNormal(normal);
  pl[LEFT].setPoint(tmp);

  tmp = nc + X * nw;
  aux = tmp - e;
  aux.normalize();
  normal = Y.cross( aux);
  pl[RIGHT].setNormal(normal);
  pl[RIGHT].setPoint(tmp);

}//end setCamDef



int Frustum::sphereInFrustum(Vector3 p, double rad){
  
  double distance;
  int result = 1;//INSIDE;
  
  for(int i=0; i < 6; i++){
    //TODO could use -1,1 unit cube and multiply projection_inv to get ModeViewl vertex
    distance = pl[i].distance(p);
    if(distance < - rad)
      return -1;//OUTSIDE;
    else if (distance < rad)
      result = 0 ;// INTERSECT;
  }

  return result;
}//end sphereInFrustum
