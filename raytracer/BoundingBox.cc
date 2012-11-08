//Implementation of BoundingBox

#include "BoundingBox.h"

//default constructor

BoundingBox::BoundingBox()
{
	min = MyPoint(0,0,0);
	max = MyPoint(0,0,0);
}

//constructor

BoundingBox::BoundingBox(MyPoint & min_point, MyPoint & max_point)
{
	min = min_point;
	max = max_point;
}

//print

void BoundingBox::print()
{
	cout << "Bounding Box: min: ";
	min.print();
	cout << "	max: ";
	max.print(); cout << endl;
}

//finds an intersection point with the bounding box at parameter t

MyPoint BoundingBox::findIntersection(float t, MyRay * r)
{
	//formula for ray is r(t) = p + td
	MyPoint p = r->getOrigin();
	MyVector d = r->getDirection();
	//get vector td
	MyVector td = d;
	td.times(t);
	//p + td, which is intersect
	p.plus(td); 
	return p;
}

