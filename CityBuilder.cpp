#include "CityBuilder.h"

void Building::draw(Matrix4 C){
  glPushMatrix();
  setModelView(C);

  int intersect= -1;
  intersect= FRUSTUM->sphereInFrustum(Vector3(C.get(3,0),C.get(3,1),C.get(3,2)), Building::largestDim/2.0);
  //intersect= FRUSTUM->pointInFrustum(Vector3(C.get(3,0),C.get(3,1),C.get(3,2)));
  if(intersect <0 && DO_FRUSTUM_CULLING) return;

  if(SHOW_FRUSTUM){
    glColor3f(1,0,0);
    glutWireCube(largestDim);
  }

  glColor3f(0,0,1);
  int deltaX=width>>2;
  int deltaY=length>>2;
  int deltaZ=height>>2;
  deltaX=width/4;deltaY=length/4;deltaZ=height/4;
  
  //drawn from center
  //front face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
    glBegin(GL_TRIANGLE_STRIP);
    for(int x=-width/2; x<=width/2; x+=deltaX){
      glNormal3f(0,-1,0);
      glVertex3f(x,-length/2,z);
      glVertex3f(x,-length/2,z+deltaZ);
    }
    glEnd();
  }
  
  
  //right face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
    glBegin(GL_TRIANGLE_STRIP);
    for(int y=-length/2; y<=length/2; y+=deltaY){
      glNormal3f(1,0,0);
	glVertex3f(width/2,y,z);
	glVertex3f(width/2,y,z+deltaZ);
    }
    glEnd();
  }
  
    //back face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
    glBegin(GL_TRIANGLE_STRIP);
    for(int x=0; x<=width; x+=deltaX){
      glNormal3f(0,1,0);
      glVertex3f(width/2-x,length/2,z);
      glVertex3f(width/2-x,length/2,z+deltaZ);
      }
    glEnd();
  }
  
  //left face
  for(int z=0; z<height-deltaZ; z+=deltaZ){
      glBegin(GL_TRIANGLE_STRIP);
      for(int y=length/2; y>=-length/2; y-=deltaY){
	glNormal3f(-1,0,0);
	glVertex3f(-width/2,y,z);
	glVertex3f(-width/2,y,z+deltaZ);
      }
      glEnd();
  }

  glPopMatrix();
}


void CityBuilder::draw(Matrix4 C){
  Matrix4 C_new=C;
  Matrix4 tmp=M;
  tmp=tmp.transpose();
  C_new=tmp*C_new;
  for( map<int, Node*>::iterator ii=childMap.begin(); ii!=childMap.end(); ++ii)
    {
      ii->second->draw(C_new);
    }

}

void CityBuilder::build(){
  Road* road_vertical=new Road(streetWidth,gridSize);
  Road* road_horizontal=new Road(gridSize,streetWidth);//w * l

  MatrixTransform *gridPos[8][8];
  Matrix4 M;
  //TODO make separate for loop for initializing gridPos

  //create road
  for(int i=-dim/2,ic=0; i<dim/2; i+=gridSize,ic++){
    for(int j=-dim/2, jc=0; j<dim/2; j+=gridSize,jc++){
      M = Matrix4(1,0,0,i,
		  0,1,0,j,
		  0,0,1,0,
		  0,0,0,1);

      gridPos[ic][jc]= new MatrixTransform(M);

      M.set(1.0, 0.0, 0.0, (float)(gridSize-streetWidth),
	    0.0, 1.0, 0.0, (float)(gridSize>>1),
	    0.0, 0.0, 1.0, 0.0,
	    0.0, 0.0, 0.0, 1.0);
      
      //from bottom left corner of grid
      MatrixTransform* posV=new MatrixTransform(M);

      M.set(1.0, 0.0, 0.0, (float)(gridSize>>1),
	    0.0, 1.0, 0.0, (float)(gridSize-streetWidth),
	    0.0, 0.0, 1.0, 0.0,
	    0.0, 0.0, 0.0, 1.0);
      
      MatrixTransform* posH=new MatrixTransform(M);
      addChild(gridPos[ic][jc]);
      gridPos[ic][jc]->addChild(posV);
      posV->addChild(road_vertical);

      gridPos[ic][jc]->addChild(posH);
      posH->addChild(road_horizontal);

    }
  }

  const int subGrid = 16;
  int gridEstimates[subGrid][subGrid];

  float gaussDistr[]=  { .3, 0.5, 1.0, 1.7, 1.25, 1.1, 0.5, .3};

  //create buildings within grid
  for(int ic=0;ic<8;ic++){
    for(int jc=0;jc<8;jc++){
      //initialize and divide grid into 16x16 sections
      for(int x=0; x < subGrid; x++){
	for(int y=0; y < subGrid;y++){
	  gridEstimates[x][y]=0;
	}
      }
      //update max for each section of the grid
      //increment by width/length of inserted building
      for(int y=0;y<gridSize-8;){
	for(int x=0;x<gridSize-8;){
	  M.set(1,0,0,x,
		0,1,0,y,
		0,0,1,0,
		0,0,0,1);
	  MatrixTransform* pos = new MatrixTransform();
	  pos->set(M);
	  
	  gridPos[ic][jc]->addChild(pos);

	  int bw,bh,bl; bw=bl=4;
	  int maxHeight=40;
	  maxHeight = maxHeight * gaussDistr[ic] * gaussDistr[jc];
	  bh=rand() % maxHeight + 5;

  	  pos->addChild(new Building(1,bh,bl,bw));
	  
	  x+=bw<<1;
	}
	
	y+=8;
      }
    }
  }
}//end build()

void Road::draw(Matrix4 C){
  
  glPushMatrix();
  setModelView(C);
  glColor3f(0,1,0);
  
  int intersect = -1;
  intersect= FRUSTUM->sphereInFrustum(Vector3(C.get(3,0),C.get(3,1),C.get(3,2)), max(width>>1,length>>1));  
  
  if(intersect <0 && DO_FRUSTUM_CULLING) return;

  int deltaX=width>>2;
  int deltaY=length>>2;
  
  //create roads
  //drawn with center of road at center
  for(int j=-length/2; j<=length/2; j+=deltaY){
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=-width/2; i<=width/2; i+=deltaX){
      glNormal3f(0,0,1);
      glVertex3f(i,j,0);
      glVertex3f(i,j+deltaY,0);
    }
    glEnd();
  }
  
  glPopMatrix();
}
