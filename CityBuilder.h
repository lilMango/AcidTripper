#pragma once
#include <stdio.h>
#include <iostream>
#include "VecMatrix4.h"
#include "SceneGraph.h"
#include "ReadObj.h"
#include "Model3D.h"

using namespace std;

class Skyscraper:public Geode{
  //  enum{MODERN,BLOCKY};
  
 public:
  int tiers;
  int height;
  int depth;
  int width;
  bool useObj;

  Skyscraper(){
    printf("From Skyscraper\n");
    tiers=1;
    height = 128;
    depth = 16;
    width = 16;
  }
  
  Skyscraper(int t,int h, int d, int w){
    tiers=t; height=h; depth=d; width=w;
  }

  void draw(Matrix4 C);
};

class CityBuilder{
 public:
  int dim;
  int cityBlockSize;
  int density;//how packed you want the buildings to be [0,100] 100 being really packed
  int towerFreq;//frequency of big towers [0,100] 100 being all big skyscrapers
  int maxHeight;
  int streetWidth;

  CityBuilder(){
    dim = 1024;
    cityBlockSize = 128;
    density = 75;
    towerFreq = 25;
    maxHeight = 70;
    streetWidth = 4;
  }
  void build();
};

