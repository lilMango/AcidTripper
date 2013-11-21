class readOBJ{

public:
	
	int nVerts;
	float *vertices;
	float *normals;
	float *texcoords;
	int nIndices;
	int *indices;
	double maxMagnitude; //the biggest magnitude of all vertices
	double* maxVertex;//xyz 
	double* minVertex;//xyz
	char * fileName;

	readOBJ(){};
};//end class readOBJ

