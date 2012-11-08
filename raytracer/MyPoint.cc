//Describes MyPoint functions

#include "MyPoint.h"

//Default constructor

MyPoint::MyPoint()
{
	x = 0;
	y = 0;
	z = 0;
}

//Constructor

MyPoint::MyPoint(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

//Multiplies point by a scalar

void MyPoint::times(float k)
{
	x *= k;
	y *= k;
	z *= k;
}

//print, for de-bugging

void MyPoint::print()
{
	cout << "(" << x << ", " << y << ", " << z << ")";
}

//equals another point

bool MyPoint::equals(const MyPoint & other)
{
	if((x == other.x) && (y == other.y) && (z == other.z))
		return true;
	return false;
}

//Assignment operator

MyPoint & MyPoint::operator=(const MyPoint& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

//add a vector to this point

void MyPoint::plus(MyVector & v)
{
	this->x += v.getX();
	this->y += v.getY();
	this->z += v.getZ();
}

//subtract a vector from this point

void MyPoint::minus(MyVector & v)
{
	this->x -= v.getX();
	this->y -= v.getY();
	this->z -= v.getZ();
}
