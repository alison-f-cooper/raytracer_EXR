//Describes intersect functions

#include "Intersection.h"

//Constructor

Intersection::Intersection()
{
	t1 = 0;
	t2 = 0;
	intersect1 = MyPoint(0,0,0);
	intersect2 = MyPoint(0,0,0);
	norm1 = MyVector(0,0,0);
	norm2 = MyVector(0,0,0);
	twice = false;
}

void Intersection::print()
{
	cout << "t1: " << t1 << "	t2: " << t2 << endl;
	cout << "p1: ";
	intersect1.print();
	cout << "	p2: ";
	intersect2.print();
	cout << endl << "norm1: ";
	norm1.print();
	cout << "	norm2: ";
	norm2.print();
	cout << endl << "twice?: " << twice;
}


//functions to calculate and set normals

void Intersection::setNorm1(MyPoint & intersect, MyPoint & origin)
{
	norm1 = MyVector(origin, intersect);
	norm1.normalize();
}

void Intersection::setNorm2(MyPoint & intersect, MyPoint & origin)
{
	norm2 = MyVector(origin, intersect);
	norm2.normalize();
}
		
