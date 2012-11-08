//Describes PointLight implementation

#include "PointLight.h"

//Default constructor
PointLight::PointLight()
{
	position = MyPoint(0,0,0);
	red = 0; green = 0; blue = 0;
}

//Constructor

PointLight::PointLight(const MyPoint & p, float r, float g, float b)
{
	position = p;
	red = r; green = g; blue = b;
}

//print

void PointLight::print()
{
	cout << "Position: ";
	position.print();
	cout << "	Color: " << "[" << red << ", " << blue << ", " << green << "]" << endl;
}
