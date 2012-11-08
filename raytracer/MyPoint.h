//MyPoint header file

#ifndef MYPOINT_H
#define MYPOINT_H

#include <iostream>
#include "MyVector.h"

class MyVector;

using namespace std;

class MyPoint
{
	public:
		//default constructor
		MyPoint();
		//constructor
		MyPoint(float a, float b, float c);
		//multiply by a scalar
		void times(float k);
		//print, for de-bugging
		void print();
		//equals another point
		bool equals(const MyPoint & other);
		//Assignment operator
		MyPoint &operator=(const MyPoint&);
		//add a vector to this point
		void plus(MyVector & v);
		//subtract a vector from this point
		void minus(MyVector & v);

		//getters

		float getX() { return x;}
		float getY() { return y;}
		float getZ() { return z;}

		//setters

		void setX(float newX) { x = newX;}
		void setY(float newY) { y = newY;}
		void setZ(float newZ) { z = newZ;}

	private:
		float x, y, z; //coordinates

};

#endif
