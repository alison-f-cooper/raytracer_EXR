//ALight function implementation

#include "ALight.h"

//Default constructor

ALight::ALight()
{
	pos = MyPoint(0,0,0);
	direction = MyVector(0,0,0);
	U = MyVector(0,0,0);
	V = MyVector(0,0,0);
	length = 0;
	rgb = MyVector(0,0,0);
}

//Constructor

ALight::ALight(float x, float y, float z,
			   float vx, float vy, float vz,
			   float ux, float uy, float uz, float len,
			   float r, float g, float b, int SHADOW_N)
{
	setPos(x, y, z);
	setDir(vx, vy, vz);
	//set U, and V based on U and direction
	setU(ux, uy, uz);
	setLen(len);
	setColor(r, g, b);
	//generateSamples(SHADOW_N);
}

//print

void ALight::print()
{
	cout << "Area Light: " << endl;
	cout << "Position: ";
	pos.print(); cout << endl;
	cout << "Direction: ";
	direction.print(); cout << " U: ";
	U.print();
	cout << " V: "; V.print(); cout << endl;
	cout << "Side Len: " << length;
	cout << " Color: "; rgb.print(); cout << endl;
	cout << "Samples: " << (int) samples.size() << endl;
	//print samples
	cout << "printing initial samples " << endl;
	for(int i = 0; i < (int) samples.size(); i++)
	{
		samples[i].print();
		cout << endl;
	}
}

//generate samples on area light for bucket-size N
//return vector of those points; vector will have
//N^2 samples

void ALight::generateSamples(int N)
{
	for(int p = 0; p < N; p++)
	{
		for(int q = 0; q < N; q++)
		{
			float randX = (float) rand() / RAND_MAX;
			float randY = (float) rand() / RAND_MAX;
			float sampleX = (p + randX)/N - 0.5;
			float sampleY = (q + randY)/N - 0.5;
			MyVector len_times_U = U;
			len_times_U.times(length);
			MyVector len_times_V = V;
			len_times_V.times(length);
			//multiply by the random coefficient calculated
			len_times_U.times(sampleX);
			len_times_V.times(sampleY);
			//add to the center point of the area light
			MyPoint currentSample = pos;
			currentSample.plus(len_times_U);
			currentSample.plus(len_times_V); 
			samples.push_back(currentSample);			
		}
	}
}

//shuffle samples

void ALight::shuffle()
{
	for(int i = 0; i < (int) samples.size(); i++)
	{
		int index_1 = rand() % (int) samples.size();
		int index_2 = rand() % (int) samples.size();
		MyPoint temp = samples[index_1];
		samples[index_1] = samples[index_2];
		samples[index_2] = temp;
	}
}

//Setters

void ALight::setPos(float x, float y, float z)
{
	pos = MyPoint(x,y,z);
}

void ALight::setDir(float vx, float vy, float vz)
{
	direction = MyVector(vx, vy, vz);
	direction.normalize();
}

void ALight::setU(float ux, float uy, float uz)
{
	U = MyVector(ux, uy, uz);
	U.normalize();
	V = U.crossProduct(direction);
	V.normalize();
}

void ALight::setLen(float len)
{
	length = len;
}

void ALight::setColor(float r, float g, float b)
{
	rgb = MyVector(r, g, b);
}
