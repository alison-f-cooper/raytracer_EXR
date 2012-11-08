//Ambient light header file

#ifndef AMBLIGHT_H
#define AMBLIGHT_H

#include <iostream>

using namespace std;

class AmbLight
{
	public:
		//Default constructor
		AmbLight();
		//Constructor
		AmbLight(float r, float g, float b);

		//print
		void print();

		//getters
		float getR(){return red;};
		float getG(){return green;};
		float getB(){return blue;};

		//setters
		void setR(float r){red = r;};
		void setG(float g){green = g;};
		void setB(float b){blue = b;};

	private:
		float red, green, blue;

};
#endif

