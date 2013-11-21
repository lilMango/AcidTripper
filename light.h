#include "VecMatrix4.h"
class Light   // output window related routines 
{ 
 public: 
  bool lightOn; 
  float final_position[4];//x,y,z,w 
  float position[4];//x,y,z,w 
  float  np[4];
  Matrix4* M; 
  float black[4];
  float color[4]; 
  float scaleFactor; 

  Light(){ 
    position[0]=0;position[1]=0;position[2]=1;position[3]=0;     
      
    color[0]=0;color[1]=0;color[2]=1;color[3]=0;//default green  
    black[3]=1;

    M=new Matrix4(); 
    M->setIdentity();
    scaleFactor=1.0; 
    lightOn=true; 
  } 
  Light(float x,float y,float z,float w, 
        float a,float b,float c,float d){ 
    position[0]=x;position[1]=y;position[2]=z;position[3]=w;     
  
    color[0]=a;color[1]=b;color[2]=c;color[3]=d;//default green  
      black[3]=1;

    M=new Matrix4(); 
    M->setIdentity();

    scaleFactor=1.0; 
    lightOn=true; 
  }//end constructor 

  void toggle(){
    lightOn=!lightOn;
  }
  bool isLightOn(){ 
    return lightOn; 
  } 
  void setLight(bool boob){ 
    lightOn=boob; 
  } 
  Matrix4*getMatrix(){ 
    return M; 
  } 
  void reset(){ 
    M->setIdentity(); 
    scaleFactor=1.0; 
    //lightOn=true; 
  } 
  float getScale(){
    return scaleFactor;
  }
  void setScaleFactor(float a){ 
    scaleFactor=a; 
    if(scaleFactor<0)scaleFactor=0.1f;
    else if(scaleFactor>20)scaleFactor=20.0f;
  }//end setScaleFactor() 
  float getScaleFactor(){ 
    return scaleFactor; 
  }//end getScaleFactor() 

  void setPosition(float x,float y,float z,float w){ 
    position[0]=x;position[1]=y;position[2]=z;position[3]=w; 
  }//end set 

  float* getPosition(){ 
    Vector4 tmp(position);
    tmp=tmp.scale((double)scaleFactor);
    tmp=(*M)*tmp;
    np[0]=tmp[0];np[1]=tmp[1]; np[2]=tmp[2]; np[3]=tmp[3];
    return np; 
    //return position;
  } 
  
  void setColor(float x,float y,float z,float w){ 
    color[0]=x;color[1]=y;color[2]=z;color[3]=w; 
  }//end set 
  
  float* getColor(){ 
    if(lightOn)
      return color; 
    else
      return black;
  } 
      
}; 
