//Ambient light implementation

#include "AmbLight.h"

//Default constructor
AmbLight::AmbLight()
{
	red = 0.01; blue = 0.01; green = 0.01;
}

//Constructor
AmbLight::AmbLight(float r, float g, float b)
{
	red = r; green = g; blue = b;
}

//print
void AmbLight::print()
{
	cout << "Ambient Light: " "["<< red << " " << green << " " << blue <<"]";
}

