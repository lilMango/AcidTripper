#pragma once
#include <map>
#include <string>
#include <GLUT/glut.h>
#include "VecMatrix4.h"
#include <stdint.h>
#include "shader.h"
#include "Frustum.h"

using namespace std;

void setModelView(Matrix4 C);

class Node{
 public:
  static Frustum* FRUSTUM;
  static int S_HELLO;
  static bool DO_FRUSTUM_CULLING;
  static bool SHOW_FRUSTUM;
  string name;
  Node* parent;
  //bounding box
  
  ~Node(){};
  virtual void draw(Matrix4 C)=0;
};//end class Node

class Group:public Node{
 public:
  map <int,Node* > childMap;

  Group(){
    name="Group";
  }
  
  ~Group();
  
  //add child
  void addChild(Node * child){
    childMap[(intptr_t)child]=child;
  };
  
  //remove child
  void removeChild(Node * child){
    childMap.erase((intptr_t)child);
  };
  void draw(Matrix4 C);
};//end class Group

class Geode:public Node{
 public:
  float rgb[3];
  Shader* shad;
  float boundingBoxRadius;
  void findBound();
  void setShader(Shader);
  void draw(Matrix4 C);
  
};//end class Geode

class MatrixTransform:public Group{
	public:

		Matrix4 M;//

		
		MatrixTransform(Matrix4 C){
			//M=new Matrix4();
			M=C;
		}//end constructor()
		MatrixTransform(){
			M=Matrix4();
		}//end constructor()
		
		MatrixTransform(double a0,double a1,double a2,double a3,
			double a4,double a5,double a6,double a7,
			double a8,double a9,double a10,double a11,
			double a12,double a13,double a14,double a15){

		  M=Matrix4(a0,a1,a2,a3,
			    a4,a5,a6,a7,
			    a8,a9,a10,a11,
			    a12,a13,a14,15);
		}
		void set(Matrix4 C){
		  M=C;
		}
		void draw(Matrix4 C);
		

};//end class MatrixTransform


class Sphere:public Geode{
	public:
		float radius;

		Sphere(char* n,float rad){
			name=n;
			radius=rad;
			rgb[0]=1;
			rgb[1]=rgb[2]=0;
		}
		Sphere(float rad){
			radius=rad;
			rgb[0]=1;
			rgb[1]=rgb[2]=0;
		}

		void draw(Matrix4 C);
};//end class Sphere

class BoundSphere:public Geode{
	public:
		float radius;
		BoundSphere(char*n,float rad){
			name=n;radius=rad;
			rgb[0]=1;
			rgb[1]=rgb[2]=0;
		}
		BoundSphere(float rad){
			radius=rad;
			rgb[0]=1;
			rgb[1]=rgb[2]=0;
		}
		void draw(Matrix4 C);
};//end class BoundSphere
class Cylinder:public Geode{
	public:
		int radius;
		int height;
		Cylinder(char*n,int rad,int h){
			name=n;
			radius=rad;
			height=h;
		}
		Cylinder(int rad,int h){
			radius=rad;
			height=h;
		}
		void draw(Matrix4 C);
};//end class Cylinder

class Cube:public Geode{
	public :
		int height,width,depth;
		Cube(char*n,int h){
			name=n;height=h;;
		}
		Cube(int h,int w,int depth){
			height=h;width=w;
		}
		Cube(int h){
			height=h;width=h;
		}
		void draw(Matrix4 C);
};//end class Cube

class RectPrism:public Geode{
	public :
		float h,w,d;
		RectPrism(char*n,float height,float width,float depth){
			name=n;h=height;w=width;d=depth;
		}
		void draw(Matrix4 C);
};//end class Cube

class Cape:public Geode{
 public : 
  float topWidth, bottomWidth, length;
  Cape(float tw, float bw, float l){
    topWidth=tw;
    bottomWidth=bw;
    length=l;
  }
  void draw(Matrix4 C);
};//end class Cape

class FrustumShape:public Geode{
 public :
  FrustumShape(){}
  
  void draw(Matrix4 C);
};//end class FrustumShape

class SandPlane:public Geode{
 public:
  SandPlane(){}

  void draw(Matrix4 C);
};//end class SandPlane

