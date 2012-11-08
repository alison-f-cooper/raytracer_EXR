//Material function implementation

#include "Material.h"

//Default constructor

Material::Material()
{
	dr = 0; dg = 0; db = 0;
	sr = 0; sg = 0; sb = 0;
	ir = 0; ig = 0; ib = 0;
	r = 0;
}

//Constructor

Material::Material(float dr, float dg, float db, 
		 		   float sr, float sg, float sb, 
		 		   float ir, float ig, float ib, 
		 		   float r)
{
	(*this).dr = dr; (*this).dg = dg; (*this).db = db;
	(*this).sr = sr; (*this).sg = sg; (*this).sb = sb;
	(*this).ir = ir; (*this).ig = ig; (*this).ib = ib;
	(*this).r = r;
}

//Print

void Material::print()
{
	cout << "Diffuse Components: " << endl;
	cout << "dr: " << (*this).dr << "	dg: " << (*this).dg << "   db: " << (*this).db << endl;

	cout << "Specular Components: " << endl;
	cout << "sr: " << sr << "	sg: " << sg << "   sb: " << sb << endl;

	cout << "Ideal Specular Components: " << endl;
	cout << "ir: " << ir << "	ig: " << ig << "   ib: " << ib << endl;

	cout << "Phong Exponent: " << endl;
	cout << "r: " << r << endl;

}

//returns if ideal specular component is not of length 0

bool Material::isMirror()
{
	return(ir > 0 || ig > 0 || ib > 0);
}		

//setters

void Material::setDiffuse(float dred, float dgreen, float dblue)
{
	dr = dred; dg = dgreen; db = dblue;
}

void Material::setSpecular(float sred, float sgreen, float sblue)
{
	sr = sred; sg = sgreen; sb = sblue;
}

void Material::setIdealSpecular(float isred, float isgreen, float isblue)
{
	ir = isred; ig = isgreen; ib = isblue;	
}
