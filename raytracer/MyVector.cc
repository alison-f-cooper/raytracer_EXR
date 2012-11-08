//Describes MyVector functions

#include "MyVector.h"

//Default constructor

MyVector::MyVector()
{
	x = 0;
	y = 0;
	z = 0;
	calcMagnitude();
}

//Constructor from components x, y, z

MyVector::MyVector(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
	calcMagnitude();
}

//Constructor from two points

MyVector::MyVector(MyPoint & a, MyPoint & b)
{
	x = b.getX() - a.getX();
	y = b.getY() - a.getY();
	z = b.getZ() - a.getZ();
	calcMagnitude();
}

//check if equal to another vector

bool MyVector::equals(const MyVector & other)
{
	if((x==other.x)&&(y==other.y)&&(z==other.z))
		return true;
	return false;
}

//assignment operator

MyVector & MyVector::operator=(const MyVector & other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->magnitude = other.magnitude;
	return *this;
}

//adds a vector to this vector

void MyVector::plus(const MyVector & other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	calcMagnitude();
}

//subtracts a vector from this vector

void MyVector::minus(const MyVector & other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	calcMagnitude();
}

//multiply by a scalar

void MyVector::times(float k)
{
	this->x *= k;
	this->y *= k;
	this->z *= k;
	calcMagnitude();
}

//normalize this vector

void MyVector::normalize()
{
	calcMagnitude(); //to be safe
	if(magnitude != 0)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		calcMagnitude();
	}
}

//calculate dot product with another vector

float MyVector::dotProduct(const MyVector & other)
{
	float x_val = (this->x) * other.x;
	float y_val = (this->y) * other.y;
	float z_val = (this->z) * other.z;
	return (x_val + y_val + z_val);
}

//generate cross product with another vector

MyVector MyVector::crossProduct(const MyVector & other)
{
	float x_val = ((this->y) * other.z) - ((this->z) * other.y);
	float y_val = ((this->z) * other.x) - ((this->x) * other.z);
	float z_val = ((this->x) * other.y) - ((this->y) * other.x);
	return MyVector(x_val, y_val, z_val);
}

//calculate magnitude

void MyVector::calcMagnitude()
{
	magnitude = (float) sqrt(x * x + y * y + z * z);
}

//setters

void MyVector::setX(float x)
{
	this->x = x;
	calcMagnitude();
}

void MyVector::setY(float y)
{
	this->y = y;
	calcMagnitude();
}

void MyVector::setZ(float z)
{
	this->z = z;
	calcMagnitude();
}
		
//for debugging

void MyVector::print()
{
	cout << "[" << x << ", " << y << ", " << z << "]";
}
