#include "Model3D.h"

void Model3D::draw(Matrix4 C){
  glPushMatrix();

  setModelView(C);

  //set color
  glEnableClientState(GL_VERTEX_ARRAY); 
  glEnableClientState(GL_COLOR_ARRAY); 
  
  glVertexPointer(3, GL_FLOAT, 0, readObj.vertices); 
  glColorPointer(3, GL_FLOAT,0, readObj.colors); 
  
  glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, readObj.indices); 
  glDisableClientState(GL_VERTEX_ARRAY); 
  glDisableClientState(GL_COLOR_ARRAY); 
  
  /* 
glBegin(GL_TRIANGLES); 
for (int i = 0; i<60; i++) { 
    glColor3f(colors[indices[i] * 3], colors[indices[i] * 3+1], colors[indices[i] * 3 +2]); //* 3 to get to next tuple(of three) 
    glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 +2]); 
}//end for i 
glEnd(); 
  */

}
