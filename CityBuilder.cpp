#include "CityBuilder.h"

void Skyscraper::draw(Matrix4 C){
  glPushMatrix();
  setModelView(C);

  glColor3f(.3,.2,.5);
  int deltaX=width>>2;
  int deltaY=depth>>2;
  int deltaZ=height>>2;
  
  //front face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
    glBegin(GL_TRIANGLE_STRIP);
    for(int x=0; x<=width; x+=deltaX){
      glVertex3f(x,0,z);
      glVertex3f(x,0,z+deltaZ);
    }
    glEnd();
  }
  
  
  //right face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
    glBegin(GL_TRIANGLE_STRIP);
    for(int y=0; y<=depth; y+=deltaY){
	glVertex3f(width,y,z);
	glVertex3f(width,y,z+deltaZ);
    }
    glEnd();
  }
  
    //back face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
    glBegin(GL_TRIANGLE_STRIP);
    for(int x=0; x<=width; x+=deltaX){
      glVertex3f(width-x,depth,z);
      glVertex3f(width-x,depth,z+deltaZ);
      }
    glEnd();
  }
  
  //left face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
      glBegin(GL_TRIANGLE_STRIP);
      for(int y=depth; y>=0; y-=deltaY){
	glVertex3f(0,y,z);
	glVertex3f(0,y,z+deltaZ);
      }
      glEnd();
  }
    
  glPopMatrix();
}

void CityBuilder::build(){

}
