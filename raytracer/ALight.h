//This is the header for area lights

#ifndef ALIGHT_H
#define ALIGHT_H

#include "MyVector.h"
#include "MyPoint.h"
#include "stdlib.h"
#include <vector>

class ALight
{
	public:
		//Default constructor
		ALight();
		//Constructor; takes center position, coordinates of direction
		//of the light, coordinates of the up vector for the light, the
		//length of each side of the light, len, and the rgb triple of
		//the light; also the bucket size for the number of samples, 
		//which is taken from user input in main
		ALight(float x, float y, float z,
			   float vx, float vy, float vz,
			   float ux, float uy, float uz, float len,
			   float r, float g, float b, int SHADOW_N);
		//print
		void print();

		//method to generate samples for a specified bucket size
		//generates N^2 samples

		void generateSamples(int N);

		//shuffle samples associated with light

		void shuffle();

		//Setters
		void setPos(float x, float y, float z);
		void setDir(float vx, float vy, float vz);
		void setU(float ux, float uy, float uz);
		void setLen(float len);
		void setColor(float r, float g, float b);
		void clearSamples(){samples.clear();};

		//Getters
		MyPoint getPos(){return pos;};
		MyVector getDir(){return direction;};
		MyVector getU(){return U;};
		MyVector getV(){return V;};
		float getLen(){return length;};
		float getR(){return (rgb.getX());};
		float getG(){return (rgb.getY());};
		float getB(){return (rgb.getZ());};
		MyVector getColor(){return rgb;};
		int getSamplesNum(){return (int) samples.size();};
		vector<MyPoint> getSamples(){return samples;};
		MyPoint getSample(){return samples[0];};

	private:
		MyPoint pos;
		MyVector direction;
		MyVector U; //one axis of the square light
		MyVector V; //the other axis of the square light
		float length;
		MyVector rgb;
		vector<MyPoint> samples;

};

#endif
