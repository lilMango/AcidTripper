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

void Cape::draw(Matrix4 C){
  
  setModelView(C);
  glColor3f(0,0,1);
  float dY = length/10.0;
  float dX = (bottomWidth-topWidth)/2.0/100.0;
  float dBT = (bottomWidth-topWidth)/2.0;
  
  /*
  for(float y=0; y < length; y+=dY){
    glBegin(GL_TRIANGLE_STRIP);
    for(float x=-bottomWidth/2.0 + y/length*dBT; x<0; x+=dY){
      glNormal3f(0,-1,0);
      glVertex3f(x,0,y);
      glVertex3f(x,0,y+dY);
    }
    glEnd();
  }
  */

  int intersect= -1;
  intersect= FRUSTUM->sphereInFrustum(Vector3(C.get(3,0),C.get(3,1),C.get(3,2)), 7);
  if(intersect == 1)return;

  const float DIM=30.0f;
  const float DELTA=DIM/100.0f;

  int offset=10;
  for(float y=0; y<DIM-2; y+=DELTA){
    glBegin(GL_TRIANGLE_STRIP);
    for(float x=-10.0+y/4.0; x<10.0-y/4.0; x+=DELTA){
      glNormal3f(0,-1,0);      
      glVertex3f(x,0,y);
      glVertex3f(x,0,y+DELTA);
    }
    glEnd();
  }//end forx

}
