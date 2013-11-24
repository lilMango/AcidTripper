#pragma once
#include <stdio.h>
#include <iostream>
#include "VecMatrix4.h"
#include "SceneGraph.h"
#include "ReadObj.h"

using namespace std;

class Model3D:public Geode{
 public:

  ReadOBJ readObj;

  Model3D(ReadOBJ arg){
    readObj=arg;
  }

  void draw(Matrix4 C);
};
