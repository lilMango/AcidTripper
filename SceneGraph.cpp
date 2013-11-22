#include "SceneGraph.h"

void Geode::draw(Matrix4 C){
}

void Group::draw(Matrix4 C){
}
/*
void Sphere::draw(Matrix4 C){
  glLoadMatrixd(camPtr->getCameraMatrix().multiply(C).getPointer());
  glColor3f(1,0,0);
  glutSolidSphere(Sphere::radius,12,12);

}

*/
