//MyRay header file

#ifndef MYRAY_H
#define MYRAY_H

#include "MyPoint.h"
#include "MyVector.h"
using namespace std;

class MyRay
{
	public:
		//default constructor
		MyRay();
		//ray from two points
		MyRay(MyPoint & p1, MyPoint & p2);
		//constructor from a point and a direction
		MyRay(MyPoint & p, MyVector & d);
		
		//getters
		MyPoint getOrigin() {return origin;}
		MyVector getDirection() {return dir;}

		//for debugging
		void print();

	private:
		MyPoint origin;
		MyVector dir; 
};

#endif
