//Abstract Surface class header

#ifndef SURFACE_H
#define SURFACE_H

#include "Intersection.h"
#include "MyRay.h"
#include "Material.h"
#include "BoundingBox.h"

extern int BOXES_FLAG;

class Surface
{
	public: 
		virtual bool intersects(MyRay * r, Intersection * i, float r_x, float r_y, float r_z) = 0;
		void setMaterial(Material * m){material = m;};
		Material * getMaterial(){return material;};
		void setBBox(MyPoint & min, MyPoint & max)
		{
			bbox.setMin(min);
			bbox.setMax(max); 
		};

		//same for all subclasses
		bool intersectsBox(MyRay * r, float r_x, float r_y, float r_z, Intersection * i)
		{
			MyVector dir = r->getDirection();
			MyPoint o = r->getOrigin();
			float x_dir = dir.getX();
			float y_dir = dir.getY();
			float z_dir = dir.getZ();
		
			float x_o = o.getX();
			float y_o = o.getY();
			float z_o = o.getZ();
			MyPoint min = bbox.getMin();
			MyPoint max = bbox.getMax();
			float minX = min.getX();
			float maxX = max.getX();
			float minY = min.getY();
			float maxY = max.getY();
			float minZ = min.getZ();
			float maxZ = max.getZ();
			
			//check first for parallel; no intersection those cases
			if(x_dir == 0 && (x_o < minX || x_o > maxX))
				return false;

			if(y_dir == 0 && (y_o < minY || y_o > maxY))
				return false;

			if(z_dir == 0 && (z_o < minZ || z_o > maxZ))
				return false;

			//calculate t intervals for x, y, and z dimensions
			float t_xmin = r_x * (minX - x_o);
			float t_xmax = r_x * (maxX - x_o);
			if(r_x < 0) // swap min and max
			{
				float temp = t_xmin; 
				t_xmin = t_xmax;
				t_xmax = temp;
			}

			float t_ymin = r_y * (minY - y_o);
			float t_ymax = r_y * (maxY - y_o);
			if(r_y < 0) // swap min and max
			{
				float temp = t_ymin; 
				t_ymin = t_ymax;
				t_ymax = temp;
			}

			float t_zmin = r_z * (minZ - z_o);
			float t_zmax = r_z * (maxZ - z_o);
			if(r_z < 0) // swap min and max
			{
				float temp = t_zmin; 
				t_zmin = t_zmax;
				t_zmax = temp;
			}
			
			//create t-interval for intersection with box

			float t_start = t_xmin;
			float t_end = t_xmax;
			
			if(t_ymin > t_start) t_start = t_ymin;
			if(t_ymax < t_end) t_end = t_ymax;	

			if(t_zmin > t_start) t_start = t_zmin;
			if(t_zmax < t_end) t_end = t_zmax;	
			
			//if t_start is greater than end, then we miss the box

			if(t_start > t_end)
				return false;

			//if the location of the camera is greater than the
			//end of the t-interval, then the box is behind the camera

			if(t_end < 0) //since ray parametrization starts at 0
				return false;

			//if we've passed through all this, then there is an intersection
			//return true

			//if flag, populate intersection object

			if(BOXES_FLAG)
			{
				if(t_start < 0) //first intersection behind camera
				{
					i->setTwice(false);
					i->setT1(t_end);
					MyPoint p1 = bbox.findIntersection(t_end, r);
					i->setPoint1(p1);
					
					//figure out what the normal is

					float x_int1 = p1.getX();
					float y_int1 = p1.getY();
					float z_int1 = p1.getZ();

					MyVector norm;

					
					float thresh = 0.001;
					float neg_thresh = (-1) * thresh;
					
					if((neg_thresh <= (x_int1 - minX)) && ((x_int1 - minX) <= thresh))
					{
						//cout << "x_int1 - minX: " << x_int1 << "-" << minX << " = " << (x_int1 - minX) << endl;
						//cout << neg_thresh << "<=" << (x_int1 - minX) << " <= " << thresh << endl;
						norm = MyVector(-1, 0, 0);
					}
					else if((neg_thresh <= (x_int1 - maxX)) && ((x_int1 - maxX) <= thresh))
					{
						//cout << "x_int1 - maxX: " << x_int1 << "-" << maxX << " = " << (x_int1 - maxX) << endl;
						norm = MyVector(1, 0, 0);
					}
					else if((neg_thresh <= (y_int1 - minY)) && ((y_int1 - minY) <= thresh))
						norm = MyVector(0, -1, 0);
					else if((neg_thresh <= (y_int1 - maxY)) && ((y_int1 - maxY) <= thresh))
						norm = MyVector(0, 1, 0);
					else if((neg_thresh <= (z_int1 - minZ)) && ((z_int1 - minZ) <= thresh))
						norm = MyVector(0, 0, -1);
					else if((neg_thresh <= (z_int1 - maxZ)) && ((z_int1 - maxZ) <= thresh))
						norm = MyVector(0, 0, 1);
					
					i->setNorm1(norm);
				}
				else
				{
					i->setTwice(true);
					i->setT1(t_start);
					i->setT2(t_end);
					MyPoint p1 = bbox.findIntersection(t_start, r);
					MyPoint p2 = bbox.findIntersection(t_end, r);
					i->setPoint1(p1);
					i->setPoint2(p2);
				
					//figure out what the normal is for 1st intersection

					float x_int1 = p1.getX();
					float y_int1 = p1.getY();
					float z_int1 = p1.getZ();

					MyVector norm;

					float thresh = 0.001;
					float neg_thresh = (-1) * thresh;
					
					if((neg_thresh <= (x_int1 - minX)) && ((x_int1 - minX) <= thresh))
						norm = MyVector(-1, 0, 0);
					else if((neg_thresh <= (x_int1 - maxX)) && ((x_int1 - maxX) <= thresh))
						norm = MyVector(1, 0, 0);
					else if((neg_thresh <= (y_int1 - minY)) && ((y_int1 - minY) <= thresh))
						norm = MyVector(0, -1, 0);
					else if((neg_thresh <= (y_int1 - maxY)) && ((y_int1 - maxY) <= thresh))
						norm = MyVector(0, 1, 0);
					else if((neg_thresh <= (z_int1 - minZ)) && ((z_int1 - minZ) <= thresh))
						norm = MyVector(0, 0, -1);
					else if((neg_thresh <= (z_int1 - maxZ)) && ((z_int1 - maxZ) <= thresh))
						norm = MyVector(0, 0, 1);

					i->setNorm1(norm);

					//figure out what the normal is for the 2nd intersection

					//figure out what the normal is for 1st intersection

					float x_int2 = p2.getX();
					float y_int2 = p2.getY();
					float z_int2 = p2.getZ();

					MyVector norm2;
					
					if((neg_thresh <= (x_int2 - minX)) && ((x_int2 - minX) <= thresh))
						norm2 = MyVector(-1, 0, 0);
					else if((neg_thresh <= (x_int2 - maxX)) && ((x_int2 - maxX) <= thresh))
						norm2 = MyVector(1, 0, 0);
					else if((neg_thresh <= (y_int2 - minY)) && ((y_int2 - minY) <= thresh))
						norm2 = MyVector(0, -1, 0);
					else if((neg_thresh <= (y_int2 - maxY)) && ((y_int2 - maxY) <= thresh))
						norm2 = MyVector(0, 1, 0);
					else if((neg_thresh <= (z_int2 - minZ)) && ((z_int2 - minZ) <= thresh))
						norm2 = MyVector(0, 0, -1);
					else if((neg_thresh <= (z_int2 - maxZ)) && ((z_int2 - maxZ) <= thresh))
						norm2 = MyVector(0, 0, 1);

					i->setNorm2(norm2);

				}
								
			}

			return true;
		};

	private:
		Material * material;
		BoundingBox bbox;
};

#endif
