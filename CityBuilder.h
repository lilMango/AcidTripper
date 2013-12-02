#pragma once
#include <stdio.h>
#include <iostream>
#include "VecMatrix4.h"
#include "SceneGraph.h"
#include "ReadObj.h"
#include "Model3D.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

class Building:public Geode{
  //  enum{MODERN,BLOCKY};
  
 public:
  int tiers;
  int height;
  int length;
  int width;
  bool useObj;
  int largestDim;

  Building(){
    printf("From Building\n");
    tiers=1;
    height = 128;
    length = 16;
    width = 16;
    
    largestDim = (width>length)?width:length;;
    
  }
  
  Building(int t,int h, int l, int w){
    tiers=t; height=h; length = l; width=w;
    largestDim = (width>length)?width:length;
  }

  void draw(Matrix4 C);
};

class Road:public Geode{
 public:
  int width;
  int length;
  Road(){
    width = 8;
    length = 128;
  }
  
  Road(int w,int l){
    width = w;
    length = l;
  }

  void draw(Matrix4 C);
};


class CityBuilder:public MatrixTransform{
 public:
  int dim;
  int gridSize;
  int density;//how packed you want the buildings to be [0,100] 100 being really packed
  int towerFreq;//frequency of big towers [0,100] 100 being all big skyscrapers
  int maxHeight;
  int streetWidth;

  CityBuilder(){
    dim = 1024;
    gridSize = 128;
    density = 75;
    towerFreq = 25;
    maxHeight = 70;
    streetWidth = 8;
    M=Matrix4(1,0,0,0,
	      0,1,0,0,
	      0,0,1,0,
	      0,0,0,1);

  }
  void draw(Matrix4 C);
  void build();
};

