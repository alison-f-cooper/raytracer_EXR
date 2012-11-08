//Describes sphere objects

#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.h"
#include "MyPoint.h"
#include <cmath>

class Sphere: public Surface
{
	public:
		//default constructor
		Sphere();
		//constructor
    	Sphere(const MyPoint & o, const float r);
		//tests for intersection between sphere and ray
		virtual bool intersects(MyRay * r, Intersection * i, float r_x, float r_y, float r_z);
		//print for debugging
		void print();
		
	private:
		MyPoint origin;
		float radius;
		double calculateDiscriminant(MyRay * r);
		
		MyPoint intersection(float t, MyRay * r);
};

#endif
