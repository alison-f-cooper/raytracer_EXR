//Plane class header

#ifndef PLANE_H
#define PLANE_H

#include "Surface.h"
#include "MyRay.h"
#include "Intersection.h"


class Plane: public Surface
{
	public:
		//default constructor
		Plane();
		//constructor from vector coordinates and scalar d, distance from the origin
		Plane(float nx, float ny, float nz, float distance);
		//intersection method inherited from abstract superclass surface
		virtual bool intersects(MyRay * r, Intersection * i, float r_x, float r_y, float r_z);
		//assignment operator
		Plane & operator=(const Plane & other);
		//print
		void print();

		//setters

		void setNorm(const MyVector & v){ norm = v;};
		void setD(const float dist){ d = dist;};

		//getters

		MyVector getNorm(){return norm;};
		float getD(){return d;};

	private:
		MyVector norm;
		MyPoint p;
		float d;
	
};
#endif 
