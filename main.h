#include <stdio.h>
#include<string>
#include <stdlib.h>
#include <iostream>
#include <GLUT/glut.h>
#include "Camera.h"
#include "ReadObjGlobals.h"
#include "light.h"
#include "shader.h"
#include "SceneGraph.h"
#include "CityBuilder.h"
#include "fps.h"
#include "SOIL.h"
#include "Frustum.h"
#include "MyWindow.h"
void mouseClick(int,int,int,int);
void mouseDrag(int,int);
void drawObj();
void changeObj();
void drawCube();
void drawPlane();
void drawCape();
void drawMiniScene();
void drawObj();
void buildSceneGraph();
unsigned char* loadPPM(const char* filename, int& width, int& height);
void loadTexture();

using namespace std;


int pgmWidth,pgmHeight;

Building *oneBuilding=new Building(0,10,10,10);

//static Camera* camPtr=new Camera(-15,5,10,  -5,0,0,		 0,1,0.5		); //left corner top
//static Camera* camPtr=new Camera(0,10,3,  0,10,2,	 0,1,0		); //camera for facing front OBJ drawings
static Camera* camPtr=new Camera(0,-1,7,  0,0,7,	 0,0,1		); //camera for facing front OBJ drawings
Matrix4* Mobj2world=new Matrix4();
bool isDragging=false;
int prevXpix=0,prevYpix=0;
bool isScaling=false;
float scaleFactor=1;
int prevScaleDrag=0;//keep track of delta mouse drags
bool isPaused=false;

//ObjReader::readObj("teapot.obj", nVerts, &vertices, &normals, &texcoords, nIndices, &indices);
float *colors;;//pointer to colors array
bool isSpin=false;
bool isAdjust=true;
bool keepDrawing=false; //tell whether to redraw or not
bool moveObject=true;
bool isShader=true;
int shaderIdx=0;
Shader* shad;
Shader* tripShad, *waveShad, *inceptionShad;

Light *pointLight = new Light(0, 10, 20,0,
			      1,1,1,1);

/*
class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void processNormalKeys(unsigned char,int,int);
    static void processSpecialKeys(int,int,int);
};

 */
int Window::width=512;int Window::height=512;

Frustum* frustum=new Frustum(100.0, Window::width/Window::height, 10.0, 1000);
int Node::S_HELLO=0;
Frustum* Node::FRUSTUM=frustum;
bool Node::DO_FRUSTUM_CULLING=true;
bool Node::SHOW_FRUSTUM=false;
MatrixTransform *world = new MatrixTransform();

Fps* fps= new Fps();

time_t startTime;
float mytimer=0.0; // use for fake time counter

const int NUM_TEXTURES=2;
GLuint textures[NUM_TEXTURES];
GLuint mytextureo;

void setModelView(Matrix4 C){
  
  glMatrixMode(GL_MODELVIEW);
  Matrix4 CM=camPtr->getCameraMatrix();
  CM=C*CM;
  glLoadMatrixd(CM.getPointer());
}



//---------------------------------------------------------------------------- 
//method when Mouse is clicked 
void mouseClick(int button, int state, int x, int y) { 
  isDragging = 1; 

  
  if(button == GLUT_LEFT_BUTTON) { 
    if(state == GLUT_DOWN) { 
  
      prevXpix=x;prevYpix=y; 
              
    }//end if GLUT_DOWN 
    else
      isDragging = 0; 
  }//end if GLUT_LEFT_button 
  
  //SCALING 
  else if(button == GLUT_RIGHT_BUTTON) { 
    if(state == GLUT_DOWN) { 
      isDragging=1; 
      isScaling=1; 
      //for scaling 
      prevScaleDrag=y; 
    }//end if GLUT_DOWN 
    else { 
      isDragging=0;isScaling=0; 
    } 
  }//end if button GLUT_RIGHT_BUTTON 
}//end mouseClick() 
  
//---------------------------------------------------------------------------- 
//method when user drags mouse and a mouse Button at the same  
void mouseDrag(int x, int y) { 
  
  if(isDragging) { 
    if(isScaling){ 
      //printf("isScaling\n"); 
      float diff=prevScaleDrag-y;//diff<0 scale down 
      //diff>0 scale up 
      //diff/100;//to lower sensitivity 
      if(diff<0){ //zoom out

	camPtr->zoomOut();
      } 
      else { //zoom in
	camPtr->zoomIn();
      } 
      
              
      prevScaleDrag=y; 
      drawObj(); 
    }else{//rotation 
      if(moveObject)
	Mobj2world->trackballRotation(Window::width,Window::height,prevXpix,prevYpix,x,y);
      
      //save end vector to start vector for next iteration 
      prevXpix=x;prevYpix=y; 
  
      drawObj(); 
    }//end rotating 
  }//end fi isDragging 
      
}//end mouseDrag() 
  
void drawCube(){

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,textures[1]);//TODO can change to textures[1] for diff img of PPM, textures[0] is SOIL's
  // Draw sides of cube in object coordinate system:
  glBegin(GL_QUADS);
  //glColor3f(139.0f/256.0f,  119.0f/256.0f,   101.0f/256.0f);
  glColor3f(1,1,1);
  glTexCoord2f(0, 1); glVertex3f(-2, -1, 0);
  glTexCoord2f(1, 1); glVertex3f(2, -1, 0);
  glTexCoord2f(1, 0); glVertex3f(2, 1, 0);
  glTexCoord2f(0, 0); glVertex3f(-2, 1, 0);
  glEnd();

}//end drawCube()

void drawPlane(){
  const float DIM=500.0f;
  const float DELTA=DIM/100.0f;
  glColor3f(1,0,0);

  for(float y=-DIM; y<DIM; y+=DELTA){
    //glBegin(GL_TRIANGLE_STRIP);
	glBegin(GL_POINTS);glPointSize(1);
    for(float x=-DIM; x<DIM; x+=DELTA){
      glNormal3f(0,1,0);      
            glVertex2f(x,y);
	    //    glVertex3f(x,y,0);
	    //glVertex3f(x,y+DELTA,0);
    }
    glEnd();
  }//end forx
  
}//end drawPlane()
  
void drawCape(){
  glColor3f(1,0,0);
  
  const float DIM=30.0f;
  const float DELTA=DIM/100.0f;
  glColor3f(1,0,0);
  int offset=10;
  for(float y=0; y<DIM-2; y+=DELTA){
    glBegin(GL_TRIANGLE_STRIP);
    for(float x=-10.0+y/4.0; x<10.0-y/4.0; x+=DELTA){
      glNormal3f(0,-1,0);      
      glVertex3f(x-offset,0,y);
      glVertex3f(x-offset,0,y+DELTA);
    }
    glEnd();
  }//end forx
  
}

 
void drawMiniScene(){


  const float DIM=2000.0f;
  const float DELTA=DIM/100.0f;
  
  
  for(float y=-DIM/10; y<DIM/10; y+=10){
    int xCount=0;
    for(float x=-DIM/10; x<DIM/10; x+=20){
      xCount++;
       glPushMatrix();
       glTranslatef(x,y,0);
       if(y>100){
	 if(xCount==4){
	   xCount=0;

	   for(int z=0;z<100;z+=7){
	     glPushMatrix();
	     glTranslatef(0,0,z);
	     glColor3f(1,0,1);
	     glutSolidCube(7.0);
	     glPopMatrix();
	     
	     if(z==0){
	       
	       Matrix4 tm=Matrix4(1,0,0,0,
				  0,1,0,0,
				  0,0,1,0,
				  0,0,5,1);
	       oneBuilding->draw(tm);
	     }
	   }
	   
	 }
       }
       else{
	 glColor3f(0,1,0);
	 glutSolidSphere(1.5,20,20);
       }
       glPopMatrix();
    }
  }//end forx
  
 
 }

unsigned char* loadPPM(const char* filename, int& width, int& height){

  const int BUFSIZE = 128;
  FILE* fp;
  unsigned int read;
  unsigned char* rawData;
  char buf[3][BUFSIZE];
  char* retval_fgets;
  size_t retval_sscanf;

  if ( (fp=fopen(filename, "rb")) == NULL)
    {
      std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
      width = 0;
      height = 0;
      return NULL;
    }

  // Read magic number:
  retval_fgets = fgets(buf[0], BUFSIZE, fp);

  // Read width and height:
  do
    {
      retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
  retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
  width  = atoi(buf[1]);
  height = atoi(buf[2]);

  // Read maxval:
  do
    {
      retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');

  // Read image data:
  rawData = new unsigned char[width * height * 3];
  read = fread(rawData, width * height * 3, 1, fp);
  fclose(fp);
  if (read != 1)
    {
      std::cerr << "error parsing ppm file, incomplete data" << std::endl;
      delete[] rawData;
      width = 0;
      height = 0;
      return NULL;
    }

  return rawData;
}//end loadPPM

  //http://stackoverflow.com/questions/8866904/need-help-understanding-the-differences-and-relationship-between-glactivetexture
//const int NUM_TEXTURES=2;
//GLuint textures[NUM_TEXTURES];
//GLuint mytexture;
void loadTexture(){
  //  glGenTextures(NUM_TEXTURES, &textures[0]);  
 printf("HEHEHE\n");
 ////using the SOIL function one shot function
 glActiveTexture(GL_TEXTURE0+0);
 glBindTexture(GL_TEXTURE_2D, textures[0]);
 textures[0] = SOIL_load_OGL_texture
   //mytexture= SOIL_load_OGL_texture
      (
       //"smiley.png",
       "explosion.png",
       SOIL_LOAD_AUTO,
       //textures[0],       
         SOIL_CREATE_NEW_ID,

      SOIL_FLAG_MIPMAPS
              | SOIL_FLAG_TEXTURE_RECTANGLE 
       //| SOIL_FLAG_NTSC_SAFE_RGB 
       //| SOIL_FLAG_COMPRESS_TO_DXT
       );
    

  for(int i=1;i<NUM_TEXTURES;i++){
    //glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, textures[i]);  
   

    int twidth, theight;
    unsigned char* tdata;
    
    //tdata = loadPPM("explosion.ppm", twidth, theight);
    tdata = loadPPM("baratheon.ppm", twidth, theight);
    //tdata = loadPPM("confederate.ppm", twidth, theight);
    if(tdata==NULL){
      printf("Null PPM\n");
      return;
    }    
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    glTexImage2D(GL_TEXTURE_2D, 0 , 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
    delete [] tdata;

  }//end for
      
  glEnable(GL_TEXTURE_2D);
}//end loadTexture
