#include <math.h>   // include math functions, such as sin, cos, M_PI
#include <cstdarg> //for variable arguments
#include <iostream>
#include <vector>

#include "VecMatrix4.h"


class Camera{

public: 
	Vector3 *e,//center of projection
		*d, //looking at
		*up;//up vector

	Vector3 *begE,*begD,*begUp;
	
	Matrix4 *c;//internal camera matrix

	double angle;                   // rotation angle [degrees]

	Camera()							 
	{
		e=new Vector3(0,10,10);d=new Vector3(0,0,0);up=new Vector3(0,1,0);
		c=new Matrix4();
		setCam();
					  
		
	}//end constructor


	Camera(float e0,float e1,float e2,
		   float d0,float d1,float d2,
		   float up0,float up1,float up2)
	{
		e=new Vector3(e0,e1,e2);
		d=new Vector3(d0,d1,d2);
		up=new Vector3(up0,up1,	up2);
		
		begE=new Vector3(e0,e1,e2);
		begD=new Vector3(d0,d1,d2);
		begUp=new Vector3(up0,up1,up2);

		c=new Matrix4();
		setCam();
	}//end constructor

	void reset(){
	  delete e;
	  e=new Vector3(begE->getX(), begE->getY(), begE->getZ());

	  delete d;
	  d= new Vector3(begD->getX(), begD->getY(), begD->getZ());
	  
	  delete up;
	  up= new Vector3(begUp->getX(), begUp->getY(), begUp->getZ());
	}
	void set(float e0,float e1,float e2,
		   float d0,float d1,float d2,
		   float up0,float up1,float up2)
	  {
		delete e;
		e=new Vector3(e0,e1,e2);
		delete d;
		d=new Vector3(d0,d1,d2);
		delete up;
		up=new Vector3(up0,up1,	up2);
		setCam();
	}//end set

	double * getValues()
	{
		return c->getPointer();
	}//end getValues()

	//rotate aroundY-axis
	void spin()
	{
		angle=.001;
		if(angle>360.0 || angle<-360.0) angle=0.0;
		c->rotateArbitrary(0,1,0,angle);
	}//end spin()

	void strafeLeft(){
	  Vector3 etmp=*e;
	  
	  Vector3 dist=Vector3();
	  dist.subtract(*d,*e);
	  dist.normalize();
	  
	  Vector3 dir=Vector3();
	  dir.cross(*up,dist);
	  dir.normalize();

	  dir=dir*2.0;
	  
	  e->add(dir);
	  d->add(dir);
	  setCam();
	}
	
	void strafeRight(){
	  Vector3 etmp=*e;
	  
	  Vector3 dist=Vector3();
	  dist.subtract(*d,*e);
	  dist.normalize();
	  
	  Vector3 dir=Vector3();
	  dir.cross(*up,dist);
	  dir.normalize();
	  
	  e->subtract(dir);
	  d->subtract(dir);
	  setCam();
	}

	void zoomIn(){
	  Vector3 etmp=*e;

	  Vector3 dist=Vector3();
	  dist.subtract(*e,*d);
	  dist.normalize();
	  //dist.scale(.1);
	  e->subtract(dist);
	  d->subtract(dist);
	  setCam();
	}
	
	void zoomOut(){
	  Vector3 etmp=*e;

	  Vector3 dist=Vector3();
	  dist.subtract(*e,*d);
	  dist.normalize();
	  //dist.scale(.1);
	  e->add(dist);
	  d->add(dist);
	  setCam();
	}


	void adjust(double x,double y, double z){
		
	}//end adjust()


	void setE(float x,float y,float z)
	{
	  delete e;
		e=new Vector3(x,y,z);
	}//end setE()
	
	void setD(float x,float y,float z)
	{
	  delete d;
		d=new Vector3(x,y,z);
	}//end setD()

	void setUp(float x,float y,float z)
	{
	  delete up;
		up=new Vector3(x,y,z);
	}//end setUp()

	void setCam()
	{
		Vector3* zc=new Vector3();;
		zc-> subtract(*e,*d);
		zc->normalize();
		
		Vector3* xc=new Vector3();;
		xc->cross(*up,*zc);
		xc->normalize();

		Vector3* yc=new Vector3();;
		yc->cross(*zc,*xc);
		
		delete c;
		c=new Matrix4(*xc,*yc,*zc,*e);
	}//end setCam()


	//returns C^(-1)
	Matrix4 getCameraMatrix()
	{	
	  // 1st image
	  /*return Matrix4( 1,0,0,0,
							0,.707214,-.707214,0,
							0,.707214,.707214,-14.1443,
						0,0,0,1).transpose();
	  */
		

	  //2nd image
	  /*
		return Matrix4(.5573,-.3713,.74269,2.78938,
							.494588,.866596,.06194,2.46644,
							-.666795,.333057,.666176,-18.329,
					   0,0,0,1).transpose();
	  */	
		

	  return c->inverseM();
	}//end getCameraMatrix
};//end class Camera
