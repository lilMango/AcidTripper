#include "SceneGraph.h"

void Geode::draw(Matrix4 C){
}

void Group::draw(Matrix4 C){
}

void Sphere::draw(Matrix4 C){

  //  cout << "Sphere::draw():\n" << S_HELLO++ << endl;

  setModelView(C);
  glColor3f(rgb[0],rgb[1],rgb[2]);
  
  int intersect= -1;
  intersect= FRUSTUM->sphereInFrustum(Vector3(C.get(3,0),C.get(3,1),C.get(3,2)), Sphere::radius);
  
  if(intersect == -1){//outside
    glColor3f(1,0,0);
    if(SHOW_FRUSTUM)
      glutSolidSphere(Sphere::radius,12,12);
  }
  else if(intersect == 0){//intersect
    glColor3f(1,1,0);
    glutSolidSphere(Sphere::radius,12,12);
  }
  else{//inside
    glColor3f(0,1,0);
    glutSolidSphere(Sphere::radius,12,12);
  }
  
  //glutSolidSphere(Sphere::radius,12,12);
}


void MatrixTransform::draw(Matrix4 C){
  Matrix4 C_new=C;
  Matrix4 tmp=M;
  tmp=tmp.transpose();
  C_new=tmp*C_new;
  for( map<int, Node*>::iterator ii=childMap.begin(); ii!=childMap.end(); ++ii)
    {
      ii->second->draw(C_new);
    }
}
