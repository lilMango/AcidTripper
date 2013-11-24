#pragma once
#include <map>
#include <stdio.h>
#include <string>
#include "objreader.h"
#include "ReadObj.h"
#include "VecMatrix4.h"

using namespace std;

void parseOBJs();

ReadOBJ curObj;

int nVerts=0;
float *vertices;
float *normals;
float *texcoords;
int nIndices=0;
int *indices;
double maxMagnitude;
double * midPtr;

string objFileArray[]={"dragon_smooth.obj","head_n.obj","bunny_n.obj","teapot.obj"};
const int numObjs=sizeof(objFileArray)/sizeof(char*);;

ReadOBJ* objArr=new ReadOBJ[numObjs];
int objIdx=5;

typedef std::map<std::string, ReadOBJ> TYPE_MAP_OBJ;;
TYPE_MAP_OBJ ObjMap;

typedef TYPE_MAP_OBJ::iterator MAPOBJ_ITER;

void parseOBJs()
{
	printf("Parsing ALL OBJ files....\n");
	for(int k=0;k<numObjs;k++)
	{

		//int nVerts;
		//float *vertices;
		//float *normals;
		//float *texcoords;
		//int nIndices;
		//int *indices;
		//double maxMagnitude; //the biggest magnitude of all vertices
		//double* maxVertex;//xyz 
		//double* minVertex;//xyz
		//char * fileName;

		objArr[k].fileName=objFileArray[k];//assign file name to object
		
		//initialize each obj with OBJ attributes
		ObjReader::readObj(objFileArray[k].c_str(), objArr[k].nVerts, &(objArr[k].vertices), &(objArr[k].normals), 
			&(objArr[k].texcoords), objArr[k].nIndices, &(objArr[k].indices));

		nVerts=objArr[k].nVerts;
		vertices=objArr[k].vertices;
		normals=objArr[k].normals;
		texcoords=objArr[k].texcoords;
		nIndices=objArr[k].nIndices;
		indices=objArr[k].indices;
		


		objArr[k].colors= new float[nVerts*3];
		for(int i=0;i<nVerts;i++){

		  objArr[k].colors[i*3]=139.0f/256.0f;//rand()&1;
		  objArr[k].colors[i*3+1]=119/256.0f;//rand()&1;
		  objArr[k].colors[i*3+2]=101/256.0f;//rand()&1;
		}


		printf("======= ");
		printf(objFileArray[k].c_str());
		
		printf(" =======:\n");
		cout <<"nVerts:"<<nVerts <<" nIndices:"<<nIndices<<"\n";
		

		double* tmpMaxVertex=new double[3];;//xyz
		double* tmpMinVertex=new double[3];;//xyz
		double magnitudeArr[]={0,0,0,0,0}; 

		tmpMaxVertex[0]=tmpMaxVertex[1]=tmpMaxVertex[2]=-1000000;
		tmpMinVertex[0]=tmpMinVertex[1]=tmpMinVertex[2]=1000000;


		float maxMagn=-100000;
		float tmpMax=-100000;
		int maxMagnIdx=-1;
		 //find min/max xyz coordinates AND find vertex with largest magnitude
  		for (int i = 0; i<nIndices; i++) {
			if((objArr[k]).vertices[(objArr[k]).indices[i] * 3 + 0]>tmpMaxVertex[0]) tmpMaxVertex[0]=(objArr[k]).vertices[(objArr[k]).indices[i]*3+0]; //x max 
			if((objArr[k]).vertices[(objArr[k]).indices[i] * 3 + 1]>tmpMaxVertex[1]) tmpMaxVertex[1]=(objArr[k]).vertices[(objArr[k]).indices[i]*3+1]; //y max
			if((objArr[k]).vertices[(objArr[k]).indices[i] * 3 + 2]>tmpMaxVertex[2]) tmpMaxVertex[2]=(objArr[k]).vertices[(objArr[k]).indices[i]*3+2]; //x max

			if(vertices[indices[i] * 3 + 0]<tmpMinVertex[0]) tmpMinVertex[0]=vertices[indices[i]*3+0]; //x min
			if(vertices[indices[i] * 3 + 1]<tmpMinVertex[1]) tmpMinVertex[1]=vertices[indices[i]*3+1]; //y min
			if(vertices[indices[i] * 3 + 2]<tmpMinVertex[2]) tmpMinVertex[2]=vertices[indices[i]*3+2]; //x min
			
			float x=vertices[indices[i] * 3 + 0];
			float y=vertices[indices[i] * 3 + 1];
			float z=vertices[indices[i] * 3 + 2];
			
			//find index with highest magnitude from vertex
			Vector3* tmpVec=new Vector3(x,y,z);
			tmpMax=tmpVec->magnitude();
			if(tmpMax>maxMagn){
				maxMagnIdx=i;
				maxMagn=tmpMax;
			}
		}//end for i
		
		printf("max x:%4.2f y:%4.2f z:%4.2f\n",tmpMaxVertex[0],tmpMaxVertex[1],tmpMaxVertex[2]);
		printf("min x:%4.2f y:%4.2f z:%4.2f\n",tmpMinVertex[0],tmpMinVertex[1],tmpMinVertex[2]);
		printf("max magnitude:%4.2f @ index:%d\n",maxMagn,maxMagnIdx);
		objArr[k].maxMagnitude=maxMagn;
		objArr[k].midPtr=new double[3];
		objArr[k].midPtr[0]=(tmpMaxVertex[0]-tmpMinVertex[0])/2+tmpMinVertex[0];
		objArr[k].midPtr[1]=(tmpMaxVertex[1]-tmpMinVertex[1])/2+tmpMinVertex[1];	
		objArr[k].midPtr[2]=(tmpMaxVertex[2]-tmpMinVertex[2])/2+tmpMinVertex[2];
		printf("midpoint(%4.2f,%4.2f,%4.2f)\n",objArr[k].midPtr[0],objArr[k].midPtr[1],objArr[k].midPtr[2]);
		
		ObjMap[objArr[k].fileName] = objArr[k];
	}//end for k OBJfiles
}//end parseOBJs

