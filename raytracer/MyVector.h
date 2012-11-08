//MyVector header file

#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "MyPoint.h"
class MyPoint;

#include <iostream>
#include <cmath>

using namespace std;

class MyVector
{
	public:
		//default constructor
		MyVector();
		//constructor from components
		MyVector(float a, float b, float c);
		//constructor from two points, from a to b
		MyVector(MyPoint & a, MyPoint & b);
		//check if equal to another vector
		bool equals(const MyVector & other);
		//Assignment operator
		MyVector & operator=(const MyVector & other);
		//add a vector to this vector
		void plus(const MyVector & other);
		//subtract a vector from this vector
		void minus(const MyVector & other);
		//multiply by a scalar
		void times(float k);
		//normalize this vector
		void normalize();
		//calculate dot product with another vector
		float dotProduct(const MyVector & other);
		//generate cross product with another vector
		MyVector crossProduct(const MyVector & other);
		//calculate magnitude
		void calcMagnitude();
		
		//getters
		float getX() {return x;}
		float getY() {return y;}
		float getZ() {return z;}
		float getMagnitude() {return magnitude;}

		//setters
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		
		//for debugging

		void print();
	private:
		float x, y, z; //components
		float magnitude; // length
};

#endif

