//Light header file

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "MyPoint.h"
#include <iostream>

using namespace std;

class PointLight
{
	public:
		//Default constructor
		PointLight();
		//Constructor
		PointLight(const MyPoint & p, float r, float g, float b);

		//print
		void print();

		//getters
		MyPoint getPosition(){return position;};
		float getR(){return red;};
		float getG(){return green;};
		float getB(){return blue;};

		//setters
		void setPosition(const MyPoint & p){position = p;};
		void setR(float r){red = r;};
		void setG(float g){green = g;};
		void setB(float b){blue = b;};

	private:
		MyPoint position;
		float red, green, blue;

};
#endif

