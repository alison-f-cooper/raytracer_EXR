//Triangle class header

#ifndef TRI_H
#define TRI_H

#include "Surface.h"
#include "MyRay.h"
#include "Intersection.h"
#include "MyPoint.h"


class Tri: public Surface
{
	public:
		//default constructor
		Tri();
		//constructor from coordinates for three vertices, delineated
		//in counter-clockwise order
		Tri(float x_1, float y_1, float z_1, 
			float x_2, float y_2, float z_2, 
			float x_3, float y_3, float z_3);
		//constructor from three vertices in counterclockwise order
		Tri(const MyPoint & v_1, const MyPoint & v_2, const MyPoint & v_3);
		//intersection method inherited from abstract superclass surface
		virtual bool intersects(MyRay * r, Intersection * i, float r_x, float r_y, float r_z);
		//assignment operator
		Tri & operator=(const Tri & other);

		//setters

		void setV1(const MyPoint & v_1){ v1 = v_1;};
		void setV2(const MyPoint & v_2){ v2 = v_2;};
		void setV3(const MyPoint & v_3){ v3 = v_3;};

		//getters

		MyPoint getV1(){return v1;};
		MyPoint getV2(){return v2;};
		MyPoint getV3(){return v3;};

		//print
		void print();

	private:
		MyPoint v1, v2, v3;
		MyVector norm;
		//helper to calculate mins and maxes

		float calcMin(float a, float b, float c);
		float calcMax(float a, float b, float c);
};
#endif 

