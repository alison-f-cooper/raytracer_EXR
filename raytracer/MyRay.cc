//Implementation of MyRay functions

#include "MyRay.h"

//default constructor

MyRay::MyRay()
{
	origin = MyPoint(0,0,0);
	dir = MyVector(0,0,0);
}


//ray from two points. the origin is the first one

MyRay::MyRay(MyPoint & p1, MyPoint & p2)
{
	origin = p1;
	dir = MyVector(p1, p2);
	dir.normalize();
}

MyRay::MyRay(MyPoint & p, MyVector & d)
{
	origin = p;
	dir = d;
	dir.normalize();
}

void MyRay::print()
{
	cout << "Origin: ";
	origin.print();
	cout << "	Direction: ";
	dir.print();
}
