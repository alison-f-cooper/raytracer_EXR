//Main for testing

#include "MyPoint.h"
#include "MyVector.h"
#include "MyRay.h"
#include "Sphere.h"
#include "Surface.h"
#include "MyCamera.h"
#include <vector>
#include "PointLight.h"
#include "Plane.h"
#include "AmbLight.h"
#include "Tri.h"
#include "ALight.h"

vector<Surface*> shapes;
MyCamera * cam;	
Sphere * temp;
Plane * plane_temp;
Tri * tri_temp; 
vector<PointLight*> p_lights;
PointLight * point_light;
Material * temp_material;
AmbLight * ambient;
ALight * area_light;
int PRIMARY_N;
int SHADOW_N;
int BOXES_FLAG;

float getTokenAsFloat (string inString, int whichToken);
void parseSceneFile (char *filnam);

int main(int argc, char *argv[])
{
	if (argc < 3 || argc > 6 || argc == 4) 
	{
        cerr << "useage: raytra scenefilename outputfile" << endl;
		cerr << "useage: raytra scenefilename outputfile primary_n shadow_n" <<endl;
		cerr << "useage: raytra scenefilename outputfile primary_n shadow_n boxes_flag (==1)" <<endl;
        return -1;
    }
	else if(argc == 3)
	{
		PRIMARY_N = 3;
		SHADOW_N = 1;
		BOXES_FLAG = 0;
	}
	else if(argc == 5)
	{
		PRIMARY_N = atoi(argv[3]);
		SHADOW_N = atoi(argv[4]);
		BOXES_FLAG = 0;
	}
	else if(argc == 6)
	{
		PRIMARY_N = atoi(argv[3]);
		SHADOW_N = atoi(argv[4]);
		BOXES_FLAG = 1;
	}

	char * sceneFileName = argv[1]; //scene to be parsed
	char * exrFileName = argv[2]; //output exr file
	parseSceneFile(sceneFileName);
	cout << "PRIMARY N: " << PRIMARY_N << "		SHADOW N: " << SHADOW_N << endl;

	cout << "Number of shapes: " << (int) shapes.size() << endl;
		
	//construct default ambient light, if one not provided
	if(ambient == NULL)
	{
		cout << "Using default ambient light " << endl;
		ambient = new AmbLight();
	}
	//cout << "before render" << endl;
	cam->renderScene(shapes);
	//cout << "after render" << endl;
	cam->writeImage(exrFileName);
	//cout << "after write" << endl;
	delete cam;
	for(int i = 0; i < (int) shapes.size(); i++)
		delete shapes[i];
	for(int j = 0; j < (int) p_lights.size(); j++)
		delete p_lights[j];
	delete temp_material;
	delete ambient;
	delete area_light;
	
	cout << "Program executed" << endl;

	return 0;
}
