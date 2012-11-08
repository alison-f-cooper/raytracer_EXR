//MyCamera header file

#ifndef MYCAMERA_H
#define MYCAMERA_H

#include "MyPoint.h"
#include "MyVector.h"
#include "MyRay.h"
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <vector>
#include <iostream>
#include "Surface.h"
#include "Intersection.h"
#include <cfloat>
#include "PointLight.h"
#include "ALight.h"
#include <cmath>
#include <stdlib.h>

using namespace Imf;
using namespace Imath;

class MyCamera
{

	public:
		//default constructor
		MyCamera();
		//Constructor
		MyCamera(const MyPoint & e, MyVector & direction, float focalLen,
			   float iw, float ih, int pw, int ph);
		//print for debugging
		void print();
		//Generates ray from e to pixel i,j
		MyRay * generateRay(float i, float j);
		//Renders the scene
		void renderScene(vector<Surface*> & surfaces);
		//writes exr file
		void writeImage(const char fileName[]);

	private:
		MyPoint eye;
		Array2D<Rgba> pixels;
		float d; // focal length
		MyVector u;
		MyVector v;
		MyVector w;
		int nx; //pixel width
		int ny; //pixel height
		float l, r, t, b; // or just w,h if film is centered

		//helper method for calculating Lambertian shading
		MyVector * calcLambertian(Material * m, MyPoint & intersect, MyPoint & light_pos,
								MyVector & normal, float r, float g, float b);

		//helper method for calculating specular shading
		MyVector * calcSpecular(Material * m, MyPoint & intersect, MyPoint & light_pos,
				                MyVector & normal, float r, float g, float b);
		//helper method for shadow
		bool inShadow(MyPoint & light_pos, MyPoint & intsect, vector<Surface*> & surfaces);

		//helper recursive method for ideal specular reflection

		MyVector lightColor(MyRay * ray, int recurse_limit, vector<PointLight*> & lights,
							vector<Surface*> & surfaces, ALight * area_light);
};
#endif
