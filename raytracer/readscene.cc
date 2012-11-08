#define IM_DEBUGGING
#include <vector>
#include "MyPoint.h"
#include "MyVector.h"
#include "MyCamera.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Sphere.h"
#include "Plane.h"
#include "AmbLight.h"
#include "Tri.h"
#include "ALight.h"

extern vector<Surface*> shapes;
extern MyCamera * cam;
extern Sphere * temp;
extern PointLight * point_light;
extern vector<PointLight*> p_lights;
extern Material * temp_material;
extern Plane * plane_temp;
extern Tri * tri_temp;
extern AmbLight * ambient;
extern ALight * area_light;
extern int SHADOW_N;

vector< int > tris;
vector< float > verts;

void read_wavefront_file (const char *file, std::vector< int > &tris, std::vector< float > &verts);

// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float getTokenAsFloat (string inString, int whichToken)
{
    
    float thisFloatVal = 0.;    // the return value
    
    if (whichToken == 0) {
        cerr << "error: the first token on a line is a character!" << endl;
        exit (-1);
    }
    
    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char [inString.size () + 1];
    
    strcpy (cstr, inString.c_str());
    
    char *p = strtok (cstr, " ");
    if (p == 0) {
        cerr << "error: the line has nothing on it!" << endl;
        exit (-1);
    }
    
    for (int i = 0; i < whichToken; i++) {
        p = strtok (0, " ");
        if (p == 0) {
            cerr << "error: the line is not long enough for your token request!" << endl;
            exit (-1);
        }
    }
    
    thisFloatVal = atof (p);
    
    delete[] cstr;
    
    return thisFloatVal;
}


//
// read the scene file.
//
// You'll need a few globals (or add arguments to this function): for the
// list of surfaces (geometric objects like spheres, triangles, planes) and
// another for the lights. These can be of type std::vector. You'll also
// need a global (or other parameter) for the camera.
//
// This should be pretty self-explanatory: it reads through the lines, and
// using the first character figures out what kind of command it is. It
// then calls the "getTokenAsFloat" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsFloat for an index that is beyond the
// end of the line!
//
// One tricky bit: when a material is read in, we want
// to keep a pointer to it so that for the next geometric object read in ,
// we can add that material to the object. In the code that follows, I use the
// variable "lastSurfaceLoaded" to do that, but the code is commented out since
// I don't know the class names you will be using.
//
// Very minimal error check here. You might improve it slightly, but we'll
// only use "correct" scene files.
//
//
void parseSceneFile (char *filnam)
{
    
    ifstream inFile(filnam);    // open the file
    string line;
    
    if (! inFile.is_open ()) {  // if it's not open, error out.
        cerr << "can't open scene file" << endl;
        exit (-1);
    }
    
    
    // Note: you'll have to keep track of whatever the last material
    // you loaded in was, so you can apply it to any geometry that gets loaded. 
    // So here, you'll have something like:
    //
    // myMaterialClass *lastMaterialLoaded = 0;  // 0 or maybe a default material?
    //
    // and each time you load in a new piece of geometry (sphere, triangle, plane)
    // you will set its material to lastMaterialLoaded.

    
    while (! inFile.eof ()) {   // go through every line in the file until finished
        
        getline (inFile, line); // get the line
        
        switch (line[0])  {     // we'll decide which command based on the first character
            
            //
            // geometry types:
            //
            // NOTE: whichever type of geo you load in, set its material to
            // be "lastMaterialLoaded"
            //
            case 's': {
                // it's a sphere, load in the parameters
                
                float x, y, z, r;
                x = getTokenAsFloat (line, 1); 
                y = getTokenAsFloat (line, 2); 
                z = getTokenAsFloat (line, 3); 
                r = getTokenAsFloat (line, 4); 

				MyPoint origin(x,y,z);
				temp = new Sphere(origin, r);

				temp->setMaterial(temp_material);

				shapes.push_back(temp);

                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                // mySphereClass *ms = new mySphereClass (x, y, z, r);   // make a new instance of your sphere class
                // ms->setMaterial (lastMaterialLoaded)
                // objectsList->push_back (ms);  // objectsList is a global std:vector<surface *> for example.
                
#ifdef IM_DEBUGGING
                // if we're debugging, show what we got:
                cout << "got a sphere with ";
                cout << "parameters: " << x << " " << y << " " << z << " " << r << endl;
#endif
                break;
		}
                
            case 't':   {
			// triangle

				float x1, y1, z1, x2, y2, z2, x3, y3, z3;
                x1 = getTokenAsFloat (line, 1); 
                y1 = getTokenAsFloat (line, 2); 
                z1 = getTokenAsFloat (line, 3); 
                
				x2 = getTokenAsFloat (line, 4); 
                y2 = getTokenAsFloat (line, 5); 
                z2 = getTokenAsFloat (line, 6); 

				x3 = getTokenAsFloat (line, 7); 
                y3 = getTokenAsFloat (line, 8); 
                z3 = getTokenAsFloat (line, 9); 
				
				tri_temp = new Tri(x1, y1, z1, x2, y2, z2, x3, y3, z3);

				tri_temp->setMaterial(temp_material);

				cout << "got a triangle" << endl;
				tri_temp->print();
				cout << endl;

				shapes.push_back(tri_temp);
				break;

			}

			case 'w': { //open OBJ file and get triangles; build triangles
				string newStr = line.substr(2);
				const char * obj_filename = newStr.c_str();
				cout << "Got an obj file: " << obj_filename << endl; 
				read_wavefront_file(obj_filename, tris, verts);
				//make triangles, push them onto surfaces vector

				
				for(int i = 0; i < (int) tris.size(); i+=3)
				{
					//get vertices numbers
					int v1 = tris[i];
					int v2 = tris[i + 1];
					int v3 = tris[i + 2];
					//cout << "Triangle: " << "(" << v1 << "," << v2 << "," << v3 << ")" << endl;
					
					//get components of v1, v2, v3
					float v1_x = verts[v1 * 3];
					float v1_y = verts[v1 * 3 + 1];
					float v1_z = verts[v1 * 3 + 2];

					float v2_x = verts[v2 * 3];
					float v2_y = verts[v2 * 3 + 1];
					float v2_z = verts[v2 * 3 + 2];
				
					float v3_x = verts[v3 * 3];
					float v3_y = verts[v3 * 3 + 1];
					float v3_z = verts[v3 * 3 + 2];
					
					//make triangle pointer

					tri_temp = new Tri(v1_x, v1_y, v1_z, v2_x, v2_y, v2_z,
									   v3_x, v3_y, v3_z);
					
					//cout << "Got a triangle: ";
					//tri_temp->print();
					//cout << endl;
					tri_temp->setMaterial(temp_material);
					shapes.push_back(tri_temp);
				}

				
					
				break;
			}
                
                
            case 'p':   {// plane

			 float nx, ny, nz, d;
                nx = getTokenAsFloat (line, 1); 
                ny = getTokenAsFloat (line, 2); 
                nz = getTokenAsFloat (line, 3); 
                d = getTokenAsFloat (line, 4); 

				plane_temp = new Plane(nx, ny, nz, d);

				plane_temp->setMaterial(temp_material);

				cout << "Got a plane: " << endl;
				plane_temp->print();
				cout << endl;

				shapes.push_back(plane_temp);
			}
                break;
                
            //
            // camera:
            //
            case 'c':  { // camera
                // one trick here: the cameras pixel count (width, height) are integers,
                // so cast them.
			
				float x, y, z, vx, vy, vz, d, iw, ih;
				int pw, ph;
				x = getTokenAsFloat (line, 1);
                y = getTokenAsFloat (line, 2); 
                z = getTokenAsFloat (line, 3); 
                vx = getTokenAsFloat (line, 4); 
                vy = getTokenAsFloat (line, 5);
				vz = getTokenAsFloat (line, 6);  
				d = getTokenAsFloat (line, 7);
				iw = getTokenAsFloat (line, 8); 
				ih = getTokenAsFloat (line, 9);
				pw = (int) getTokenAsFloat (line, 10); 
				ph = (int) getTokenAsFloat (line, 11);
		
				MyPoint e(x, y, z);
				MyVector dir(vx, vy, vz);
				cam = new MyCamera(e, dir, d, iw, ih, pw, ph);  

				cout << "got a camera with ";
                cout << "parameters: " << x << " " << y << " " << z << " " << endl;
				cout << vx << " " << vy << " " << vz << " " << d << " " << endl;
				cout << iw << " " << ih << " " << pw << " " << ph << " " << endl; 

                break;
            }
            //
            // lights:
            //
            case 'l':   // light
            {
                
                // slightly different from the rest, we need to examine the second param,
                // which is at the third position on the line:
                switch (line[2]) {
                    case 'p':
                    {
                    	// point light
                    	float x, y, z, r, g, b;
                    	x = getTokenAsFloat (line, 2);
                    	y = getTokenAsFloat (line, 3);
                    	z = getTokenAsFloat (line, 4);

                    	r = getTokenAsFloat (line, 5);
                    	g = getTokenAsFloat(line, 6);
                    	b = getTokenAsFloat(line, 7);

                    	MyPoint position(x,y,z);
                        point_light = new PointLight(position, r, g, b);

                        cout << "Got a point light ";
                        point_light->print();
						p_lights.push_back(point_light);
                        cout <<endl;

                    }
                        break;
                    case 'd':   // directional light
                        break;
                    case 'a':   
					{
						// ambient light
						float r, g, b;
						r = getTokenAsFloat (line, 2);
                    	g = getTokenAsFloat(line, 3);
                    	b = getTokenAsFloat(line, 4);

						ambient = new AmbLight(r,g,b);
						cout << "Got an ambient light" << endl;
						ambient->print();
						cout << endl;
					}
                        break;
					case 's': // area light
					{
						float x, y, z; //position
						float vx, vy, vz; //direction
						float ux, uy, uz; //up direction
						float len; //length of side
						float r, g, b; //color

						x = getTokenAsFloat(line, 2);
						y = getTokenAsFloat(line, 3);
						z = getTokenAsFloat(line, 4);
						vx = getTokenAsFloat(line, 5);
						vy = getTokenAsFloat(line, 6);
						vz = getTokenAsFloat(line, 7);
						ux = getTokenAsFloat(line, 8);
						uy = getTokenAsFloat(line, 9);
						uz = getTokenAsFloat(line, 10);
						len = getTokenAsFloat(line, 11);
						r= getTokenAsFloat(line, 12);
						g = getTokenAsFloat(line, 13);
						b = getTokenAsFloat(line, 14);
		
						area_light = new ALight(x, y, z, vx, vy, vz, ux, uy, uz, len, r, g, b, SHADOW_N);
						cout << "Got an area light" << endl;
						area_light->print();
						cout << endl;
					}
					break;
                        
                }
                
                break;
            }
            
            //
            // materials:
            //
            case 'm':   // material
            {
                // the trick here: we should keep a pointer to the last material we read in,
                // so we can apply it to any subsequent geometry. Say it's called "lastMaterialLoaded"
                // we migh then do something like this:
                //
                //  1. read in the 10 material parameters: dr, dg, db, sr, sg, sb, r, ir, ig, ib
                //  2. call lastMaterialLoaded->setMaterial(dr, dg, db,...);

            	float dr, dg, db, sr, sg, sb, r, ir, ig, ib;
            	dr = getTokenAsFloat (line, 1);
            	dg = getTokenAsFloat (line, 2);
            	db = getTokenAsFloat (line, 3);

            	sr = getTokenAsFloat (line, 4);
            	sg = getTokenAsFloat(line, 5);
            	sb = getTokenAsFloat(line, 6);

            	r = getTokenAsFloat(line, 7);

            	ir = getTokenAsFloat (line, 8);
            	ig = getTokenAsFloat(line, 9);
            	ib = getTokenAsFloat(line, 10);

            	temp_material = new Material(dr, dg, db, sr, sg, sb, ir, ig, ib, r);
            	cout << "got a material: " << endl;
            	temp_material->print();

                break;
            }

            
            case '/':
                // don't do anything, it's a comment
                break;
                

            //
            // options
            //
            case 'o':   // make your own options if you wish
                break;
        }
        
    }
}

// Given the name of a wavefront (OBJ) file that consists JUST of
// vertices, triangles, and comments, read it into the tris and verts
// vectors.
//
// tris is a vector of ints that is 3*n long, where n is the number of
// triangles. The ith triangle has vertex indexes 3*i, 3*i+1, and 3*i+2.
//
// The ith vertex has components verts[3*i], verts[3*i+1], and verts[3*i+2],
// given in counterclockwise order with respect to the surface normal
//
// If you are using the supplied Parser class, you should probably make this
// a method on it: Parser::read_wavefront_file().
//
void read_wavefront_file (
    const char *file,
    std::vector< int > &tris,
    std::vector< float > &verts)
{
    
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();

    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
                
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        } 
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
 
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
         } 
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        } 
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
     }
    
    in.close();    
    std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << std::endl;
}



/*
//
// the main just makes sure that there is an argument passed, which is
// supposed to be the scenefile.
//
int main (int argc, char *argv[])
{
  
    if (argc != 3) {
        cerr << "useage: raytra scenefilename outputfile" << endl;
        return -1;
    }
	else
	{

		cout << "Testing vector class " << endl;
		Vec test(1, 2, 2);
		cout << "Vector: " << test << "	Magnitude: " << test.getMagnitude() << endl;
		cout << "normalizing" << endl;
		Vec temp = test.normalize();
		cout << "norm: " << temp << "	Magnitude: " << temp.getMagnitude() << endl;


		char * sceneFileName = argv[1]; //scene to be parsed
		char * exrFileName = argv[2]; //output exr file
		parseSceneFile(sceneFileName);
		cam->renderScene(shapes);
		//cam->writeImage(exrFileName);
	}
	return 0;
}

*/
