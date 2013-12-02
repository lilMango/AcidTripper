#include "main.h"
//------------------------
void drawObj()
{
//ObjReader::readObj(objFileArray[objIdx], nVerts, &vertices, &normals, &texcoords, nIndices, &indices);

glMatrixMode(GL_MODELVIEW);

 Matrix4 C=camPtr->getCameraMatrix();
 //C=C.transpose();
 //C=C*(*Mobj2world);
 //C=C.transpose();
 C=(*Mobj2world)*C;
 //since we're using column order Matrix stack we use M*C not C*M
 glLoadMatrixd(  C.getPointer());


 GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
 GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
 GLfloat low_shininess[] = { 5.0 };
 GLfloat high_shininess[] = { 100.0 };


 if(objIdx&1==1){//shiny
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_mat);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

 }else{//shiny and diffuse
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);

 }
 if(objIdx==4)//cube
   {
     drawCube();
   }
 else if(objIdx == 5)//sphere
   {
     drawPlane();
     drawCape();
     drawMiniScene();
   }else{

	glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glNormalPointer(GL_FLOAT,0,normals);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT,0, colors);

	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, indices);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

 }

 glLoadIdentity();



}//end drawObj()

void buildSceneGraph()
{
  MatrixTransform *subRoot = new MatrixTransform();
  world->addChild(subRoot);

  Sphere* sphere=new Sphere(1.0);
  //  Cube* cube=new Cube(3);
  Cape* cape=new Cape(6,2,9);
  MatrixTransform*pos0=new MatrixTransform(5,0,0,0,
					   0,5,0,0,
					   0,0,5,0,
					   0,0,0,1);
  //  world->addChild(pos0);
  pos0->addChild(cape);

  MatrixTransform*pos1=new MatrixTransform(10,0,0,0,
					   0,10,0,0,
					   0,0,10,0,
					   0,0,0,1);

  world->addChild(pos1);
  Building* skyscraper= new Building();
 
  Model3D* teapot=new Model3D(ObjMap["teapot.obj"]);
  Road* road = new Road();
  //pos1->addChild(skyscraper);
  //   pos1->addChild(teapot);
  //  world->addChild(road);

  FrustumShape* frustumShape=new FrustumShape();
  world->addChild(frustumShape);
     


  sphere->rgb[0]=0;
  sphere->rgb[1]=0;
  sphere->rgb[2]=1;

  const int MAX_ARMY=0;

  for(int i=-MAX_ARMY;i<=MAX_ARMY;i++){
    for(int j=-MAX_ARMY;j<=MAX_ARMY;j++){
      Matrix4 M=Matrix4(1,0,0, i*16,
			0,1,0, j*16,
			0,0,1, 0,
			0,0,0, 1);
      MatrixTransform* pos=new MatrixTransform(M);
      
      subRoot->addChild(pos);
      float tmpHeight = 8+rand() % 70;
      pos->addChild(new Building(1, tmpHeight,8,8));
    }
  }

  ////////////////////////////////////////////////////////  

  world->addChild(new SandPlane());
  
  CityBuilder* city = new CityBuilder();
  city->build();
    world->addChild(city);
  //pos1->addChild(city);
  
}//end buildSceneGraph()


void changeObj()
{
  if(objIdx>=numObjs)return;

	//ObjReader::readObj(objFileArray[objIdx], nVerts, &vertices, &normals, &texcoords, nIndices, &indices);
	nVerts=objArr[objIdx].nVerts;
	vertices=objArr[objIdx].vertices;
	normals=objArr[objIdx].normals;
	texcoords=objArr[objIdx].texcoords;
	nIndices=objArr[objIdx].nIndices;
	indices=objArr[objIdx].indices;
	maxMagnitude=objArr[objIdx].maxMagnitude;
	midPtr=objArr[objIdx].midPtr;

	printf("change Obj-----%3.2f,%3.2f,%3.2f\n",(float)-midPtr[0],(float)-midPtr[1],(float)-midPtr[2]);
	
	//42
  // These are the RGB colors corresponding to the vertices, in the same order
	colors=objArr[objIdx].colors;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	drawObj();

}//end changeObj






//----------------------------------------------------------------------------
//Process key events (ie letters)
void Window::processNormalKeys(unsigned char key,int x,int y)
{


  //        int mod = glutGetModifiers();
	//	printf("\t mod:%d\n",mod);


	printf("pressed key %c\n",key);
	switch(key){
	case '1'://point light
	  pointLight->toggle();
	  if(pointLight->isLightOn())printf("pointLight: ON\n");
	  else printf("pointLight: off\n");
	  break;
        case 'p':
	  isPaused=!isPaused;
	  break;
	case 'h': //head
	  printf("shiny\n");
		objIdx=1;
		
		changeObj();
		displayCallback();
		Mobj2world->setIdentity();
		break;
	case 'b'://bunny
	  printf("shiny-diffuse\n");

		objIdx=2;
		changeObj();
		displayCallback();
		Mobj2world->setIdentity();
		break;

	case 't'://teapot
	  printf("shiny\n");


		objIdx=3;
		changeObj();
		displayCallback();
		Mobj2world->setIdentity();
		break;
	case 'c'://cube
	  printf("shiny-diffuse\n");

		objIdx=4;
		changeObj();
		displayCallback();
		Mobj2world->setIdentity();
		break;

	case 'q'://waves
	  printf("waves\n");
	  //camPtr->set(-0.5,-5,2,  0,0,0,	 0,1,0		); //camera for facing front OBJ drawings
	  objIdx=5;
	  changeObj();
	  displayCallback();
	  Mobj2world->setIdentity();
	  break;
	case 'e'://toggle wave and tripper shader
	  shaderIdx++;
	  if(shaderIdx>2)shaderIdx=0;

	  isShader=1;
	  
	  if(shaderIdx==0){
	    shad=waveShad;
	    printf("WaveShader:On\n");
	  }else if(shaderIdx==1){
	    mytimer=0;
	    shad=tripShad;
	    printf("TripShader:On\n");
	  }else{
	    shad=inceptionShad;
	    printf("InceptionShader:On\n");
	  }
	  shad->bind();
	  break;
	case 'x': //shader on
	  isShader=!isShader;
	  if(isShader){
	    shad->bind();
	    
	
	    printf("Shader:ON\n");
	  }
	  else{
	    shad->unbind();
	    printf("Shader:off\n");
	  }
	  break;

	case 'm':

	  moveObject=!moveObject;
	  if(moveObject)printf("moveObject:ON\n");
	  else printf("moveObject: off\n");
	  break;
	case 'w':
	  camPtr->zoomIn();
	  frustum->setCamDef(*(camPtr->e),*(camPtr->d),*(camPtr->up));
	  break;
	case 's':
	  camPtr->zoomOut();
	  frustum->setCamDef(*(camPtr->e),*(camPtr->d),*(camPtr->up));
	  break;
	case 'a':
	  camPtr->strafeLeft();
	  frustum->setCamDef(*(camPtr->e),*(camPtr->d),*(camPtr->up));
	  break;
	case 'd':
	  camPtr->strafeRight();
	  frustum->setCamDef(*(camPtr->e),*(camPtr->d),*(camPtr->up));
	  break;
	case 'r': //reset
	  mytimer=0;
	  Mobj2world->setIdentity();
	  camPtr->reset();
	  frustum->setCamDef(*(camPtr->e),*(camPtr->d),*(camPtr->up));
	  break;
	case 'f': //do frustum culling
	  Node::DO_FRUSTUM_CULLING = !Node::DO_FRUSTUM_CULLING;
	  if(Node::DO_FRUSTUM_CULLING){
	    printf("Frustum CUlling : ON\n");
	  }
	  else{
	    printf("Frustum culling: off\n");
	  }
	  break;
	case 'g': //show frustum
	  Node::SHOW_FRUSTUM =! Node::SHOW_FRUSTUM;
	  break;
	}//end switch

	
}//end processNormalKeys()


//----------------------------------------------------------------------------
//Process key events (ie F1, up)
void Window::processSpecialKeys(int key,int x,int y)
{
  printf("special:%d\n",key);
  int mod = glutGetModifiers();
  printf("\t mod:%d\n",mod);

}//end processSpecialKeys()

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
  if(isPaused)return;

  mytimer+=.005;
  GLint myTime = glGetUniformLocationARB(shad->getPid(), "time");
  time_t timet;
  time(&timet);
  float diff= difftime(timet,startTime); 
    // glUniform1fARB(myTime,diff*.0025);
  glUniform1fARB(myTime,mytimer);

  //http://stackoverflow.com/questions/8866904/need-help-understanding-the-differences-and-relationship-between-glactivetexture
  glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, textures[0]);
  //glBindTexture(GL_TEXTURE_2D, mytexture);//using SOIL
  int tex_loc = glGetUniformLocationARB(shad->getPid(), "tExplosion");
  glUniform1i(tex_loc,0); //referes to glActiveTexture(GL_TEXTURE<i=0>)

  glBindTexture(GL_TEXTURE_2D, 0);

  glLoadIdentity();
   // Generate light source:
 if(pointLight->isLightOn())
   glEnable(GL_LIGHT0);
 else{
   glDisable(GL_LIGHT0);
 }
 

 glLightfv(GL_LIGHT0, GL_POSITION, pointLight->getPosition());
 //glLightfv(GL_LIGHT0, GL_AMBIENT, pointLight->color);
 glLightfv(GL_LIGHT0, GL_DIFFUSE, pointLight->getColor());
 glLightfv(GL_LIGHT0, GL_SPECULAR,pointLight->getColor());

  //    if(keepDrawing)
  displayCallback();    // call display routine to redraw cube
  
  fps->update();
		
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();//set to move w.r.t. origin
  //left,right,bottom,top,nearVal,farVal
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10.0, 1000.0); // set perspective projection viewing frustum
  frustum->setCamInternals(frustum->angle, width/height, 10.0, 1000);
  
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  
  if(objIdx>=0 && objIdx<numObjs+2){
    //drawObj();
    //drawSceneGraph();
      world->draw((*Mobj2world));
  }

  
  glFlush();  
  glutSwapBuffers();

}//end displayCallBack()


int main(int argc, char *argv[])
{

  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float red[]={1,0,0,1};
  float green[]={0,1,0,1};
  float blue[]={0,0,1,1};

  float shininess[] = {100.0};
  float point_position[]  = {0.0, 10.0, 15.0, 1.0};	// lightsource position
  float spot_position[] = {10,10,10,0};
  float dir_position[] = {0,10,5,0};


  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(512,512);      // set initial window size
  glutCreateWindow("OuRs is the FurY");    	      // open window and set window title
  if (glutGet(GLUT_WINDOW_COLORMAP_SIZE) != 0) 
  {
    cerr << "Fatal Error: bad RGBA colormap size\n" << endl;
    exit(1);
  }
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //for wireframe
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, pointLight->getPosition());
  
  glEnable(GL_NORMALIZE);

  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

  //key entries
  glutKeyboardFunc(Window::processNormalKeys);
  glutSpecialFunc(Window::processSpecialKeys);

  //mouse movements
  glutMouseFunc(mouseClick);
  glutMotionFunc(mouseDrag);
  

  char* dotVert="tripper.vert";
  char* dotFrag="tripper.frag";
  waveShad=new Shader("waves.vert","waves.frag");
  tripShad=new Shader("tripper.vert","tripper.frag");
  inceptionShad=new Shader("inception.vert","inception.frag");

  shad=waveShad;
  shad->bind();


  //initialize array of read objects
  parseOBJs();
  //initialize object
  changeObj();
  //drawObj();
  time(&startTime);
  loadTexture();

  //
  printf("SHOWING MAP!!\n");

  for(MAPOBJ_ITER iter= ObjMap.begin(); iter!=ObjMap.end();iter++){
    string tmp= iter->first;
    cout << "\t" << iter->first << "\tnVerts:" << (iter->second).nVerts << endl;
  }

  printf("GL VERSION:");  glGetString(GL_VERSION);

  buildSceneGraph();
  frustum->setCamDef(*(camPtr->e),*(camPtr->d),*(camPtr->up));
  //  world->FRUSTUM = frustum;

  glutMainLoop();

  return 0;
}//end main()

