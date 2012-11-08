//Describes materials

#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
using namespace std;

class Material
{
	public:
		//Default constructor
		Material();
		//Constructor
		Material(float dr, float dg, float db, 
				 float sr, float sg, float sb, 
				 float ir, float ig, float ib, 
				 float r);
		//print
		void print();
		
		//getters
		float getDR(){return dr;};
		float getDG(){return dg;};
		float getDB(){return db;};

		float getSR(){return sr;};
		float getSG(){return sg;};
		float getSB(){return sb;};

		float getIR(){return ir;}
		float getIG(){return ig;};
		float getIB(){return ib;};
		float getPhong(){return r;};

		bool isMirror();

		//setters
		void setDiffuse(float dred, float dgreen, float dblue);
		void setSpecular(float sred, float sgreen, float sblue);
		void setIdealSpecular(float isred, float isgreen, float isblue);
		void setPhong(float phong){r = phong;};
		

	private:
		//diffuse components
		float dr, dg, db;
		//specular components
		float sr, sg, sb;
		//ideal specular components
		float ir, ig, ib;
		//Phong exponent
		float r;
};
#endif
