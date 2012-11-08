//Header file for intersection

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "MyPoint.h"
#include "MyVector.h"

using namespace std;

class Intersection
{
	public:
		//Default constructor
		Intersection();

		//print

		void print();

		//setters

		void setT1(float t){t1 = t;};
		void setT2(float t){t2 = t;};
		void setPoint1(const MyPoint & p){intersect1 = p;};
		void setPoint2(const MyPoint & p){intersect2 = p;};
		void setTwice(bool t){twice = t;};

		//calculates normal to the intersection; sets the norms
		void setNorm1(MyPoint & intersect, MyPoint & origin);
		void setNorm2(MyPoint & intersect, MyPoint & origin);
		void setNorm1(MyVector & norm){norm1 =norm;};
		void setNorm2(MyVector & norm){norm2 = norm;};

		//getters

		float getT1(){return t1;};
		float getT2(){return t2;};
		MyPoint getPoint1(){return intersect1;};
		MyPoint getPoint2(){return intersect2;};
		MyVector getNorm1(){return norm1;};
		MyVector getNorm2(){return norm2;};
		bool getTwice(){return twice;};

	private:
		float t1; //parametrization 1 of intersection
		float t2; //parametrization 2 of intersection
		bool twice;
		MyPoint intersect1;
		MyPoint intersect2;
		MyVector norm1;	
		MyVector norm2;
};

#endif
